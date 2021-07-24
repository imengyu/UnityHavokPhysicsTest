/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKBASE_HKDEBUGUTIL_CHECK_DETERMINISM_UTIL_H
#define HKBASE_HKDEBUGUTIL_CHECK_DETERMINISM_UTIL_H

// Uncomment the next line if you want to check the engine for determinism
//#define HK_WANT_DETERMINISM_CHECKS

#ifdef HK_WANT_DETERMINISM_CHECKS
#define HK_ENABLE_DETERMINISM_CHECKS_ON_CPU
#	ifndef HK_PLATFORM_SPU
#		define HK_ENABLE_DETERMINISM_CHECKS
#	endif
#endif

#if defined (HK_ENABLE_DETERMINISM_CHECKS)
	#include <Common/Base/Thread/Thread/hkThreadLocalData.h>
	#include <Common/Base/System/Io/IStream/hkIStream.h>
	#include <Common/Base/System/Io/OStream/hkOStream.h>
	#define HK_ON_DETERMINISM_CHECKS_ENABLED(code) code
	#define HK_ENABLE_INTERNAL_DATA_RANDOMIZATION // this may be useful when debugging multithreading non-determinism issues
	#define HK_ON_ENABLE_INTERNAL_DATA_RANDOMIZATION(x) x
	//#define HK_DETERMINISM_CHECK_SIZES
	//#define HK_ENABLE_DETERMINISM_CHECKS_FOR_SOLVER
#else
	#	define HK_ON_DETERMINISM_CHECKS_ENABLED(code)
	#	define HK_ON_ENABLE_INTERNAL_DATA_RANDOMIZATION(x)
#endif

#if defined (HK_ENABLE_DETERMINISM_CHECKS_ON_CPU)
	#define HK_ON_CPU_DETERMINISM_CHECKS_ENABLED(code) code
#else
	#define HK_ON_CPU_DETERMINISM_CHECKS_ENABLED(code)
#endif

extern struct hkCheckDeterminismUtil* g_checkDeterminismUtil;


#if defined(HK_DETERMINISM_CHECK_SIZES)
#	include <Common/Base/Container/PointerMap/hkPointerMap.h>
#endif

class hkIstream;
class hkOstream;
class hkCriticalSection;
class hkMemoryTrack;



	/// This is a small helper class allowing to check the determinism of
	/// a system. Basically it works by running an application twice:
	/// First a binary logfile is created and the second time the system
	/// checks against this binary logfile.
	///
	/// Usage quick start:
	///
	/// You activate writing or reading+checking with startWriteMode() or startCheckMode() functions from anywhere in your app.
	/// Similarly you call finish() when you're done with writing or reading+checking.
	///
	/// Then for every single thread that you're intending to use the utility in, you must call workerThreadStartFrame() before
	/// and workerThreadFinishFrame() after any use of the utility.
	///
	/// The workerThreadStartFrame() function takes a parameter isPrimaryWorkerThread. This can be true for only one thread.
	/// That 'marked' thread is allowed to used the utility immediately. This is used when the primary thread performs special
	/// operations besides the jobs taken off of the job queue.
	///
	/// Other threads must register a job first. The primary thread can also register jobs, when it starts working
	/// in parallel to other threads.
	///
	/// Why do we need to register jobs? When multithreading, before the utility is used, you must tell it what that thread
	/// is about to start doing -- you must do that, as the same thread may be given different jobs on each consecutive run.
	/// You do that by calling registerAndStartJob() and finishJob(). Those functions take a job ID which must be unique
	/// across all jobs performed during that one frame.
	///
	/// Soo, only now after starting, and before finishing a job. You can use the hkCheckDeterminismUtil::checkMt() function.
struct hkCheckDeterminismUtil
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkCheckDeterminismUtil );

			// Frame-unique ID
			//
			// This id has to be unique for a job in the scope of a single frame.
			// It is made up of the hkpSimulationIslands's unite tag, job type, job task's sequential id, and one another counter (hmm).
			// See hkCheckDeterminismUtil::Fuid hkpDynamicsJob::getFuid().
		struct Fuid
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkCheckDeterminismUtil::Fuid );
				
			static Fuid& getZeroFuid();
			static Fuid& getCanceledFuid();

			bool operator==(const Fuid& f);
			bool operator!=(const Fuid& f);
			void setPackedJobId(const struct hkJob& job);
			hkUint16 getPackedJobId() const { return m_jobPackedId; }

			hkUint32 m_0;
		private:
			hkUint16 m_jobPackedId; // use getJobFuid() to initialize for this value
		public:
			hkUint16 m_2;
			hkUint32 m_3, m_4;
		};

		 hkCheckDeterminismUtil();
		~hkCheckDeterminismUtil();

		static hkCheckDeterminismUtil& getInstance() { HK_ASSERT2(0xad8655d2, g_checkDeterminismUtil, "Instance not created."); return *g_checkDeterminismUtil; }


#if !defined(HK_PLATFORM_SPU)
		static void HK_CALL createInstance() { HK_ASSERT2(0xad8655d3, !g_checkDeterminismUtil, "Instance already created."); g_checkDeterminismUtil = new hkCheckDeterminismUtil(); }

		static void HK_CALL destroyInstance() { delete g_checkDeterminismUtil; g_checkDeterminismUtil = HK_NULL; }
#endif

			/// Sets this utility to write mode. Call at startup of your test.
			/// Make sure to call finish() at the end.
		void startWriteMode(bool stampFilename = false, const char* filename = "hkDeterminismCheckfile.bin");

			/// Sets this utility to check mode. Call at startup of your test.
			/// Make sure to call finish() at the end.
		void startCheckMode(const char* filename = HK_NULL);

			/// Call this function at the end of your write/check run. This closes the open files
		void finish();

		//
		// Registration functions used at the beginning and end of each hkpDynamicsJob.
		//

#	if defined (HK_ENABLE_DETERMINISM_CHECKS)
	public:
		/// check an array, but only check the crc number of the whole array
		template<typename TYPE>
		static HK_ALWAYS_INLINE void HK_CALL checkMtCrc( int id, const TYPE* object, int numObjects = 1 ) 
		{
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				instance.checkCrcImpl( id, object, sizeof(TYPE ) * numObjects );
				wipeStack();
			}
		}

		/// The excluded array excludes specific bytes of the data from checking. It is an array of (offset, sizeBytes) pairs, with -1 as the last element.
		/// Per example, to exclude 2 bytes at offset 12 and 1 byte at offset 15, one would pass: { 12, 2, 15, 1, -1 } as the excluded array.
		template<typename TYPE>
		static HK_FORCE_INLINE void HK_CALL checkMt( int id, const TYPE* object, int numObjects = 1, int* excluded = HK_NULL )
		{
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				checkMt(id, numObjects);
				instance.checkImpl( id, object, sizeof(TYPE ) * numObjects, excluded );
				wipeStack();
			}
		}

		/// check a simple type object
		template<typename TYPE>
		static HK_FORCE_INLINE void HK_CALL checkMt( int id, const TYPE& object ) 
		{
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				instance.checkImpl( id, &object, sizeof(TYPE ));
				wipeStack();
			}
		}

		/// Sets the values used when writing or checking the determinism log.
		/// The user may set the values used when allocating and deallocating,
		/// both when writing and when checking the determinism log. Moreover,
		/// the user can change the value used for wiping the stack memory every time
		/// one of the check functions is called in case of write and check.
		static void HK_CALL setMemoryScrubValues(
			hkUint32 heapAllocWrite, hkUint32 heapFreeWrite,
			hkUint32 heapAllocCheck, hkUint32 heapFreeCheck,
			hkUint32 stackWipeWrite, hkUint32 stackWipeCheck )
		{
			s_heapAllocScrubValueWrite = heapAllocWrite;
			s_heapFreeScrubValueWrite = heapFreeWrite;
			s_heapAllocScrubValueCheck = heapAllocCheck;
			s_heapFreeScrubValueCheck = heapFreeCheck;
			s_stackScrubValueWrite = stackWipeWrite;
			s_stackScrubValueCheck = stackWipeCheck;
		}

		/// Automatically called to wipe the stack (128 4 bytes words, 512 bytes) at the end
		/// of checkMt() and checkMtCrc(). May also be called explicitly.
		static void HK_CALL wipeStack() 
		{
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode == MODE_COMPARE)
			{
				wipeStackImpl( s_stackScrubValueCheck );
			}
			else
			{
				wipeStackImpl( s_stackScrubValueWrite );
			}
		}

		static void HK_CALL initThread()							
		{
			initThreadImpl();
		}
		
		static void HK_CALL quitThread()							
		{
			quitThreadImpl();
		}
		
		static void HK_CALL workerThreadStartFrame(hkBool isPrimaryWorkerThread) 
		{
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				instance.workerThreadStartFrameImpl(isPrimaryWorkerThread);
			}
		}
		
		static void HK_CALL workerThreadFinishFrame()				
		{ 
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				instance.workerThreadFinishFrameImpl();
			}
		}

		static void HK_CALL registerAndStartJob(Fuid& jobFuid)	
		{ 
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				instance.registerAndStartJobImpl(jobFuid); 
			}
		}
		
		static void HK_CALL finishJob(Fuid& jobFuid, hkBool skipCheck)	
		{ 
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				instance.finishJobImpl(jobFuid, skipCheck); 
			}
		}
		
		static void HK_CALL cancelJob(Fuid& jobFuid)				
		{
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				instance.cancelJobImpl(jobFuid); 
			}
		}

	protected:
		static void HK_CALL combineRegisteredJobs()					
		{ 
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				instance.combineRegisteredJobsImpl(); 
			}
		}

		static void HK_CALL extractRegisteredJobs()					
		{ 
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				instance.extractRegisteredJobsImpl();
			}
		}

		static void HK_CALL clearRegisteredJobs()					
		{
			hkCheckDeterminismUtil& instance = getInstance();
			if(instance.m_mode != MODE_IDLE)
			{
				instance.clearRegisteredJobsImpl();
			}
		}

#	else

	public:
		template<typename TYPE> static HK_ALWAYS_INLINE void HK_CALL checkMtCrc( int id, const TYPE* object, int numObjects = 1 )
		{}
		template<typename TYPE> static HK_ALWAYS_INLINE void HK_CALL checkMt( int id, const TYPE* object, int numObjects = 1, int* excluded = HK_NULL )
		{}
		template<typename TYPE> static HK_ALWAYS_INLINE void HK_CALL checkMt( int id, const TYPE& object )
		{}

		static HK_ALWAYS_INLINE void HK_CALL setMemoryScrubValues(
			hkUint32 heapAllocWrite, hkUint32 heapFreeWrite,
			hkUint32 heapAllocCheck, hkUint32 heapFreeCheck,
			hkUint32 stackWipeWrite, hkUint32 stackWipeCheck )
		{}

		static HK_ALWAYS_INLINE void HK_CALL wipeStack() 
		{} 
		static HK_ALWAYS_INLINE void HK_CALL initThread()
		{}
		static HK_ALWAYS_INLINE void HK_CALL quitThread()
		{}
		static HK_ALWAYS_INLINE void HK_CALL workerThreadStartFrame(hkBool isPrimaryWorkerThread)
		{}
		static HK_ALWAYS_INLINE void HK_CALL workerThreadFinishFrame()
		{}

		static HK_ALWAYS_INLINE void HK_CALL registerAndStartJob(Fuid& jobFuid)
		{}
		static HK_ALWAYS_INLINE void HK_CALL finishJob(Fuid& jobFuid, hkBool skipCheck)
		{}
		static HK_ALWAYS_INLINE void HK_CALL cancelJob(Fuid& jobFuid)
		{}

	protected:
		static HK_ALWAYS_INLINE void HK_CALL combineRegisteredJobs()
		{}
		static HK_ALWAYS_INLINE void HK_CALL extractRegisteredJobs()
		{}
		static HK_ALWAYS_INLINE void HK_CALL clearRegisteredJobs()
		{}

#	endif

	public:
		void flushWrite();
		void setCurrentJobFuid(Fuid jobFuid);
		static void setCurrentCheckIndex(hkUint32 checkIndex);
		static void bumpCurrentCheckIndex();
		static hkUint32 getCurrentCheckIndex();
		static Fuid getCurrentJobFuid();

		bool isNearBreakpoint(hkUint64 offset);

	protected:
		static void HK_CALL initThreadImpl();
		static void HK_CALL quitThreadImpl();
		void workerThreadStartFrameImpl(hkBool isPrimaryWorkerThread);
		void workerThreadFinishFrameImpl();

		static HK_NEVER_INLINE void HK_CALL wipeStackImpl( hkUint32 value );

		void  registerAndStartJobImpl(Fuid& jobFuid);
		//There is an MT check in finish job; If the job was defered due to running out of memory, skipCheck must be true
		void  finishJobImpl(Fuid& jobFuid, hkBool skipCheck);
		void  cancelJobImpl(Fuid& jobFuid);	
		void  combineRegisteredJobsImpl();
		void  extractRegisteredJobsImpl();
		void  clearRegisteredJobsImpl();
		void  delayJob(const Fuid& id, bool start) const;


		void checkImpl( int id, const void* object, int size, int* excluded = HK_NULL);
		void checkCrcImpl( int id, const void* object, int size);

		enum Mode
		{
			MODE_IDLE,
			MODE_WRITE,
			MODE_COMPARE
		};
		Mode m_mode;
		hkUint64 m_frame;

		hkBool m_inSingleThreadedCode;

		hkMemoryTrack* m_memoryTrack;	///< This will be created when this utility works in memory ( no file name given in the startXXX() functions)

		hkStringPtr	m_filename;
		hkIstream*	m_sharedInputStream;
		hkOstream*	m_sharedOutputStream;

		hkIstream* m_primaryWorkerThreadInputStream;
		hkOstream* m_primaryWorkerThreadOutputStream;
		int m_primaryWorkerThreadJobInfoIdx;

		hkCriticalSection* m_shared;

		static hkUint32 s_heapAllocScrubValueWrite; // used in write mode
		static hkUint32 s_heapFreeScrubValueWrite; // used in write mode
		static hkUint32 s_heapAllocScrubValueCheck; // used in check mode
		static hkUint32 s_heapFreeScrubValueCheck; // used in check mode
		static hkUint32 s_stackScrubValueWrite; // used in write or idle mode
		static hkUint32 s_stackScrubValueCheck; // used in check mode

		struct JobInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkCheckDeterminismUtil::JobInfo );
			Fuid		m_jobFuid;

			// This is the data. In multi threaded mode, the thread-local m_input/outputStreams connect to the corresponding hkArray.
			// This array is resizable, therefore it has to point to the data array.
			hkMemoryTrack* m_data; // for write

			hkBool			m_isOpen;
		};

		hkArray<JobInfo> m_registeredJobs;
		
		hkBool m_delayJobs;
		hkUint32 m_delayCounter;
		hkArray<unsigned char> m_delayJobSeed;
		

		bool m_enableThreadTracker;
		int m_maxTheadId;
		hkArray<Fuid> m_threadTracker;
		
#if defined(HK_DETERMINISM_CHECK_SIZES)
		hkPointerMap<int,int> m_sizePerId;
#endif
		hkBool m_writingStFromWorker;

		friend class hkNetworkedDeterminismUtil;
};

#	if defined (HK_ENABLE_DETERMINISM_CHECKS)
	extern int hkCheckDeterminismUtil_id;
	extern hkReal* hkCheckDeterminismUtil_reference;
	extern hkReal* hkCheckDeterminismUtil_object;
	extern int hkCheckDeterminismUtil_size;
	extern hkReal* hkCheckDeterminismUtil_crcObject;
#endif

#endif // HKBASE_HKDEBUGUTIL_CHECK_DETERMINISM_UTIL_H

/*
 * Havok SDK - Base file, BUILD(#20131218)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2013
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available from salesteam@havok.com.
 * 
 */
