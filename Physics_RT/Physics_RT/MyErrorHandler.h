#pragma once
#include "stdafx.h"
#include "PhysicsHeader.h"

class MyErrorHandler : public hkError
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
	MyErrorHandler(hkErrorReportFunction errorReportFunction, void* errorReportObject = HK_NULL);

	virtual void setEnabled(int id, hkBool enabled) HK_OVERRIDE;
	virtual hkBool isEnabled(int id) HK_OVERRIDE;
	virtual void enableAll() HK_OVERRIDE;
	virtual void setMinimumMessageLevel(Message msg) HK_OVERRIDE;
	virtual Message getMinimumMessageLevel() HK_OVERRIDE;
	virtual int message(hkError::Message msg, int id, const char* description, const char* file, int line) HK_OVERRIDE;
	virtual void sectionBegin(int id, const char* sectionName) HK_OVERRIDE;
	virtual void sectionEnd() HK_OVERRIDE;

protected:
	virtual void showMessage(char* buffer, int buffer_size, bool printToErrFunction, const char* what, int id, const char* desc, const char* file, int line, hkBool stackTrace = true);
private:
	/// This function will be used to report errors.
	hkErrorReportFunction m_errorFunction;
	void* m_errorObject;	
	
	/// A map of the disabled assert IDs.
	hkPointerMap<int, int> m_disabledAssertIds;
	hkArray<int> m_sectionIds;
	hkError::Message m_minimumMessageLevel;
};

