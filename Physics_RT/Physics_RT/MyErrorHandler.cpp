#include "MyErrorHandler.h"
#include <exception>

MyErrorHandler::MyErrorHandler(hkErrorReportFunction errorReportFunction, void* errorReportObject) :
	m_errorFunction(errorReportFunction),
	m_errorObject(errorReportObject),
	m_minimumMessageLevel(hkError::MESSAGE_ALL)
{
	
}
void MyErrorHandler::setEnabled(int id, hkBool enabled)
{
	if (enabled)
	{
		m_disabledAssertIds.remove(id);
	}
	else
	{
		m_disabledAssertIds.insert(id, 1);
	}
}
hkBool MyErrorHandler::isEnabled(int id)
{
	return m_disabledAssertIds.getWithDefault(id, 0) == 0;
}
void MyErrorHandler::enableAll()
{
	m_minimumMessageLevel = hkError::MESSAGE_ALL;
	m_disabledAssertIds.clear();
}
void MyErrorHandler::setMinimumMessageLevel(Message msg)
{
	m_minimumMessageLevel = msg;
}
hkError::Message MyErrorHandler::getMinimumMessageLevel()
{
	return m_minimumMessageLevel;
}
void MyErrorHandler::showMessage(char* buffer, int buffer_size, bool printToErrFunction, const char* what, int id, const char* desc, const char* file, int line, hkBool stackTrace)
{
	if ((id == 0) && (file == HK_NULL))
	{
		//Just a simple message
		hkString::snprintf(buffer, buffer_size, "%s", desc);
	}
	else
	{
#if defined(HK_PLATFORM_LINUX)
		static const char format[] = "%s:%d: [0x%08X] %s: %s";
		static const char formatNoId[] = "%s:%d: %s: %s";
#else
		static const char format[] = "%s(%d): [0x%08X] %s: %s";
		static const char formatNoId[] = "%s(%d): %s: %s";
#endif

		if (id != (int)0xffffffff && id != 0)
		{
			hkString::snprintf(buffer, buffer_size, format, file, line, id, what, desc);
		}
		else
		{
			hkString::snprintf(buffer, buffer_size, formatNoId, file, line, what, desc);
		}
	}

	// make sure the string is always terminated properly
	buffer[buffer_size - 1] = 0;

	if(printToErrFunction)
		(*m_errorFunction)(buffer, m_errorObject);

	if (printToErrFunction && stackTrace)
	{
		hkStackTracer tracer;

		hkUlong trace[128];
		int ntrace = tracer.getStackTrace(trace, HK_COUNT_OF(trace));
		if (ntrace > 2)
		{
			(*m_errorFunction)("Stack trace is:\n", m_errorObject);
			// first two frames are in this file.
			tracer.dumpStackTrace(trace + 2, ntrace - 2, m_errorFunction, m_errorObject);
		}
	}
}
int MyErrorHandler::message(hkError::Message msg, int id, const char* description, const char* file, int line)
{
	if (id == -1 && m_sectionIds.getSize())
	{
		id = m_sectionIds.back();
	}

	if (msg < getMinimumMessageLevel())
	{
		return 0;
	}

	if (!isEnabled(id))
	{
		return 0;
	}

	const char* what = "";

	hkBool stackTrace = false;
	switch (msg)
	{
	case MESSAGE_REPORT:
		what = "Report";
		break;
	case MESSAGE_WARNING:
		what = "Warning";
		break;
	case MESSAGE_ASSERT:
		what = "Assert";
		stackTrace = true;
		break;
	case MESSAGE_ERROR:
		what = "Error";
		stackTrace = true;
		break;
	case MESSAGE_NONE:
	default:
		break;
	}

	const int buffer_size = 4 * 2048;
	char buffer[buffer_size];
	showMessage(buffer, buffer_size, msg != MESSAGE_ASSERT, what, id, description, file, line, stackTrace);

	if (msg == MESSAGE_ASSERT)
		throw std::exception(buffer);
		
	return false;
}
void MyErrorHandler::sectionBegin(int id, const char* sectionName)
{
	m_sectionIds.pushBack(id);
}
void MyErrorHandler::sectionEnd()
{
	m_sectionIds.popBack();
}