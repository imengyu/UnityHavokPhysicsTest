#include "Commom.h"

// Math and Base
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/System/Io/Reader/hkStreamReader.h>
#include <Common/Base/System/Io/Writer/hkStreamWriter.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Container/String/hkStringBuf.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>

// MultiThreaded
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

// Scene Data
#include <Common/SceneData/Scene/hkxScene.h>
#include <Common/SceneData/VisualDebugger/hkxSceneDataContext.h>
#include <Common/SceneData/Mesh/hkxMeshSectionUtil.h>
#include <Common/SceneData/Skin/hkxSkinUtils.h>
#include <Common/SceneData/Scene/hkxSceneUtils.h>

// Serialize
#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Util/hkSerializeUtil.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>

// Parser
#include <Common/Base/System/Io/OptionParser/hkOptionParser.h>

// Dynamics includes
#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

#include <assert.h>

//=======================================
// Wrap fuctions
//=======================================

WARP_FUNC(hkMemoryRouter, hkMemoryRouterRef)
WARP_FUNC(hkJobQueue, hkJobQueueRef)
WARP_FUNC(hkProcessContext, hkProcessContextRef)
WARP_FUNC(hkObjectResource, hkObjectResourceRef)
WARP_FUNC(hkRootLevelContainer, hkRootLevelContainerRef)
WARP_FUNC(hkxScene, hkxSceneRef)
WARP_FUNC(hkxNode, hkxNodeRef)
WARP_FUNC(hkxMesh, hkxMeshRef)
WARP_FUNC(hkxMeshSection, hkxMeshSectionRef)
WARP_FUNC(hkxVertexDescription, hkxVertexDescriptionRef)
WARP_FUNC(hkxVertexBuffer, hkxVertexBufferRef)
WARP_FUNC(hkxIndexBuffer, hkxIndexBufferRef)
WARP_FUNC(hkxSkinBinding, hkxSkinBindingRef)
WARP_FUNC(hkError, hkErrorRef)

//================================================
// API
//================================================

void HAVOK_C_CALL hkPlatformInit()
{
	// Math\hkMath.cpp(241): [0xDE404A11] Warning: Flushing denormals is required inside Havok code.
	// Please call _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON); before stepping Havok.
	// See the "Using the Math Library" section in the User Guide for more information.
#if ((defined(HK_PLATFORM_LINUX) || defined(HK_PLATFORM_WIN32) || defined(HK_PLATFORM_PS4)) && (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && defined(HK_COMPILER_HAS_INTRINSICS_IA32)) // ALL_SIMD_SSE_PLATFORMS // Source\Common\Base\Math\Quaternion\hkQuaternionUtil.inl
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif

	//PlatformInit();
}

int8_t HAVOK_C_CALL hkMemoryInitUtil_quit()
{
	hkResult _res = hkMemoryInitUtil::quit();
	return _res.m_enum;
}

int8_t HAVOK_C_CALL hkBaseSystem_init(hkMemoryRouterRef memoryRouter, void(HAVOK_C_PTR *errorReport)(char const *msg, void *userArgGivenToInit), void *errorReportObject)
{
	hkResult _res = hkBaseSystem::init(unwrap(memoryRouter), errorReport, errorReportObject);
	return _res.m_enum;
}
int8_t HAVOK_C_CALL hkBaseSystem_quit()
{
	hkResult _res = hkBaseSystem::quit();
	return _res.m_enum;
}

void HAVOK_C_CALL hkThreadNumber_set(int threadNumber)
{
	HK_THREAD_LOCAL_SET(hkThreadNumber, threadNumber);
	return;
}

hkJobQueueRef HAVOK_C_CALL hkJobQueue_new(int numCpuThreads)
{
	hkJobQueueCinfo cinfo;
	cinfo.m_jobQueueHwSetup.m_numCpuThreads = numCpuThreads;
	hkJobQueue *jobQueue = new hkJobQueue(cinfo);
	return wrap(jobQueue);
}
int8_t HAVOK_C_CALL hkJobQueue_processAllJobs(hkJobQueueRef jobQueue)
{
	hkJobQueue::JobStatus _res = unwrap(jobQueue)->processAllJobs();
	return _res;
}
void HAVOK_C_CALL hkJobQueue_delete(hkJobQueueRef jobQueue)
{
	delete unwrap(jobQueue);
	return;
}

hkObjectResourceRef HAVOK_C_CALL hkSerializeUtil_loadOnHeap(
	void *pStreamReaderRef,
	int(HAVOK_C_PTR *pFn_StreamReader_read)(void *pStreamReaderRef, void *buf, int nbytes),
	int(HAVOK_C_PTR *pFn_StreamReader_seek)(void *pStreamReaderRef, int offset, int whence))
{
	class hkCustomSeekableStreamReader : public hkSeekableStreamReader
	{
		void *const m_pStreamReaderRef;
		int(HAVOK_C_PTR *const m_pFn_StreamReader_read)(void *pStreamReaderRef, void *buf, int nbytes);
		int(HAVOK_C_PTR *const m_pFn_StreamReader_seek)(void *pStreamReaderRef, int offset, int whence);
		mutable bool m_isOk;

		hkBool isOk() const override
		{
			return m_isOk;
		}

		int read(void *buf, int nbytes) override
		{
			int _res = m_pFn_StreamReader_read(m_pStreamReaderRef, buf, nbytes);
			if (_res != -1 && _res >= 0)
			{
				assert(m_isOk != false);
				return _res;
			}
			else
			{
				m_isOk = false;
				return 0;
			}
		}

		int skip(int nbytes) override
		{
			int cur = m_pFn_StreamReader_seek(m_pStreamReaderRef, 0, hkSeekableStreamReader::STREAM_CUR);
			int end = m_pFn_StreamReader_seek(m_pStreamReaderRef, 0, hkSeekableStreamReader::STREAM_END);
			if ((cur != -1 && cur >= 0) && (end != -1 && end >= 0))
			{
				int nskipbytes = (((cur + nbytes) <= end) ? (nbytes) : ((cur <= end) ? (end - cur) : 0));
				int _res = m_pFn_StreamReader_seek(m_pStreamReaderRef, cur + nskipbytes, hkSeekableStreamReader::STREAM_SET);
				if (_res != -1 && _res >= 0)
				{
					assert(m_isOk != false);
					return nskipbytes;
				}
				else
				{
					m_isOk = false;
					return 0;
				}
			}
			else
			{
				m_isOk = false;
				return 0;
			}
		}

		int peek(void *buf, int n) override
		{
			int cur = m_pFn_StreamReader_seek(m_pStreamReaderRef, 0, hkSeekableStreamReader::STREAM_CUR);
			int _res_read = m_pFn_StreamReader_read(m_pStreamReaderRef, buf, n);
			int _res_seek = m_pFn_StreamReader_seek(m_pStreamReaderRef, cur, hkSeekableStreamReader::STREAM_SET);
			if ((cur != -1 && cur >= 0) && (_res_read != -1 && _res_read >= 0) && (_res_seek != -1 && _res_seek >= 0))
			{
				assert(m_isOk != false);
				return _res_read;
			}
			else
			{
				m_isOk = false;
				return 0;
			}
		}

		hkSeekableStreamReader *isSeekTellSupported() override
		{
			return this;
		}

		hkResult seek(int offset, SeekWhence whence) override
		{
			int _res_seek = m_pFn_StreamReader_seek(m_pStreamReaderRef, offset, whence);
			if (_res_seek != -1 && _res_seek >= 0)
			{
				assert(m_isOk != false);
				return HK_SUCCESS;
			}
			else
			{
				m_isOk = false;
				return HK_FAILURE;
			}
		}

		int tell() const override
		{
			int _res_seek = m_pFn_StreamReader_seek(m_pStreamReaderRef, 0, hkSeekableStreamReader::STREAM_CUR);
			if (_res_seek != -1 && _res_seek >= 0)
			{
				assert(m_isOk != false);
				return _res_seek;
			}
			else
			{
				m_isOk = false;
				return -1;
			}
		}

	public:
		inline hkCustomSeekableStreamReader(
			void *pStreamReaderRef,
			int(HAVOK_C_PTR *pFn_StreamReader_read)(void *pStreamReaderRef, void *buf, int nbytes),
			int(HAVOK_C_PTR *pFn_StreamReader_seek)(void *pStreamReaderRef, int offset, int whence))
			: m_pStreamReaderRef(pStreamReaderRef),
			  m_pFn_StreamReader_read(pFn_StreamReader_read),
			  m_pFn_StreamReader_seek(pFn_StreamReader_seek),
			  m_isOk(true)
		{
		}
	};

	hkObjectResource *objRes;
	hkSerializeUtil::ErrorDetails errorOut;
	{
		hkCustomSeekableStreamReader _tmp_stream(pStreamReaderRef, pFn_StreamReader_read, pFn_StreamReader_seek);
		objRes = hkSerializeUtil::loadOnHeap(&_tmp_stream, &errorOut, hkSerializeUtil::LOAD_DEFAULT);
	}
	if (errorOut.id == hkSerializeUtil::ErrorDetails::ERRORID_NONE)
	{
		return wrap(objRes);
	}
	else
	{
		HK_ERROR(errorOut.id, errorOut.defaultMessage);
		return NULL;
	}
}

hkRootLevelContainerRef HAVOK_C_CALL hkObjectResource_stealContents_hkOpaqueRootLevelContainer(hkObjectResourceRef res)
{
	hkRootLevelContainer *container = unwrap(res)->stealContents<hkRootLevelContainer>();
	return wrap(container);
}
void HAVOK_C_CALL hkObjectResource_removeReference(hkObjectResourceRef res)
{
	return unwrap(res)->removeReference();
}

int8_t HAVOK_C_CALL hkSerializeUtil_save(
	hkRootLevelContainerRef container,
	void *pStreamWriterRef,
	int(HAVOK_C_PTR *pFn_StreamWriter_write)(void *pStreamWriterRef, void *buf, int nbytes),
	int(HAVOK_C_PTR *pFn_StreamWriter_seek)(void *pStreamWriterRef, int offset, int whence),
	int8_t options)
{
	class hkCustomStreamWriter : public hkStreamWriter
	{
		void *const m_pStreamWriterRef;
		int(HAVOK_C_PTR *const m_pFn_StreamWriter_write)(void *pStreamWriterRef, void *buf, int nbytes);
		int(HAVOK_C_PTR *const m_pFn_StreamWriter_seek)(void *pStreamWriterRef, int offset, int whence);
		mutable bool m_isOk;

		hkBool isOk() const override
		{
			return m_isOk;
		}

		int write(void const *buf, int nbytes) override
		{
			int _res = m_pFn_StreamWriter_write(m_pStreamWriterRef, const_cast<void *>(buf), nbytes);
			if (_res != -1 && _res >= 0)
			{
				assert(m_isOk != false);
				return _res;
			}
			else
			{
				m_isOk = false;
				return 0;
			}
		}

		void flush() override
		{
		}

		hkBool seekTellSupported() const override
		{
			return true;
		}

		hkResult seek(int offset, SeekWhence whence) override
		{
			int _res_seek = m_pFn_StreamWriter_seek(m_pStreamWriterRef, offset, whence);
			if (_res_seek != -1 && _res_seek >= 0)
			{
				assert(m_isOk != false);
				return HK_SUCCESS;
			}
			else
			{
				m_isOk = false;
				return HK_FAILURE;
			}
		}

		int tell() const override
		{
			int _res_seek = m_pFn_StreamWriter_seek(m_pStreamWriterRef, 0, hkSeekableStreamReader::STREAM_CUR);
			if (_res_seek != -1 && _res_seek >= 0)
			{
				assert(m_isOk != false);
				return _res_seek;
			}
			else
			{
				m_isOk = false;
				return -1;
			}
		}
	public:
		inline hkCustomStreamWriter(
			void *pStreamWriterRef,
			int(HAVOK_C_PTR *pFn_StreamWriter_write)(void *pStreamWriterRef, void *buf, int nbytes),
			int(HAVOK_C_PTR *pFn_StreamWriter_seek)(void *pStreamWriterRef, int offset, int whence))
			: m_pStreamWriterRef(pStreamWriterRef),
			  m_pFn_StreamWriter_write(pFn_StreamWriter_write),
			  m_pFn_StreamWriter_seek(pFn_StreamWriter_seek),
			  m_isOk(true)
		{
		}
	};

	hkResult _res;
	{
		hkCustomStreamWriter _tmp_writer(pStreamWriterRef, pFn_StreamWriter_write, pFn_StreamWriter_seek);
		_res = hkSerializeUtil::save(unwrap(container), hkRootLevelContainer::staticClass(), &_tmp_writer, static_cast<hkSerializeUtil::SaveOptionBits>(options));
	}
	return _res.m_enum;
}

hkRootLevelContainerRef HAVOK_C_CALL hkRootLevelContainer_new()
{
	hkRootLevelContainer *container = new hkRootLevelContainer();
	return wrap(container);
}
void HAVOK_C_CALL hkRootLevelContainer_namedVariant_pushObject_hkxSence(hkRootLevelContainerRef container, char const *name, hkxSceneRef scene)
{
	return unwrap(container)->m_namedVariants.pushBack(hkRootLevelContainer::NamedVariant(name, unwrap(scene), &hkxScene::staticClass()));
}
hkxSceneRef HAVOK_C_CALL hkRootLevelContainer_findObject_hkxScene(hkRootLevelContainerRef container)
{
	hkxScene *scene = unwrap(container)->findObject<hkxScene>();
	return wrap(scene);
}
void HAVOK_C_CALL hkRootLevelContainer_delete(hkRootLevelContainerRef container)
{
	delete unwrap(container);
	return;
}

hkxSceneRef HAVOK_C_CALL hkxScene_new()
{
	hkxScene *scene = new hkxScene();
	return wrap(scene);
}
void HAVOK_C_CALL hkxScene_modeller_set(hkxSceneRef scene, char const *s)
{
	return unwrap(scene)->m_modeller.set(s);
}
void HAVOK_C_CALL hkxScene_asset_set(hkxSceneRef scene, char const *s)
{
	return unwrap(scene)->m_asset.set(s);
}
hkxNodeRef HAVOK_C_CALL hkxScene_rootNode(hkxSceneRef scene)
{
	return wrap(unwrap(scene)->m_rootNode);
}
void HAVOK_C_CALL hkxScene_rootNode_set(hkxSceneRef scene, hkxNodeRef rootNode)
{
	unwrap(scene)->m_rootNode = unwrap(rootNode);
	return;
}
uint32_t HAVOK_C_CALL hkxScene_numFrames(hkxSceneRef scene)
{
	return unwrap(scene)->m_numFrames;
}
void HAVOK_C_CALL hkxScene_numFrames_set(hkxSceneRef scene, uint32_t numFrames)
{
	unwrap(scene)->m_numFrames = numFrames;
	return;
}
float HAVOK_C_CALL hkxScene_sceneLength(hkxSceneRef scene)
{
	return unwrap(scene)->m_sceneLength;
}
void HAVOK_C_CALL hkxScene_sceneLength_set(hkxSceneRef scene, float sceneLength)
{
	unwrap(scene)->m_sceneLength = sceneLength;
	return;
}
void HAVOK_C_CALL hkxScene_meshes_pushBack(hkxSceneRef scene, hkxMeshRef mesh)
{
	return unwrap(scene)->m_meshes.pushBack(unwrap(mesh));
}
void HAVOK_C_CALL hkxScene_skinBindings_pushBack(hkxSceneRef scene, hkxSkinBindingRef skin)
{
	return unwrap(scene)->m_skinBindings.pushBack(unwrap(skin));
}
void HAVOK_C_CALL hkxScene_removeReference(hkxSceneRef scene)
{
	return unwrap(scene)->removeReference();
}

hkxNodeRef HAVOK_C_CALL hkxNode_new()
{
	hkxNode *node = new hkxNode();
	return wrap(node);
}
char const *HAVOK_C_CALL hkxNode_name(hkxNodeRef node)
{
	return unwrap(node)->m_name.cString();
}
void HAVOK_C_CALL hkxNode_name_set(hkxNodeRef node, char const *s)
{
	return unwrap(node)->m_name.set(s);
}
void HAVOK_C_CALL hkxNode_keyFrames_setSize(hkxNodeRef node, int size)
{
	return unwrap(node)->m_keyFrames.setSize(size);
}
void HAVOK_C_CALL hkxNode_keyFrames_setValue(hkxNodeRef node, int index, float m[4][4])
{
	hkVector4f c0;
	hkVector4f c1;
	hkVector4f c2;
	hkVector4f c3;
	c0.load4(m[0]);
	c1.load4(m[1]);
	c2.load4(m[2]);
	c3.load4(m[3]);
	return unwrap(node)->m_keyFrames[index].setCols(c0, c1, c2, c3);
}
void HAVOK_C_CALL hkxNode_keyFrames_setSizeValue(hkxNodeRef node, int size, float m[4][4])
{
	hkVector4f c0;
	hkVector4f c1;
	hkVector4f c2;
	hkVector4f c3;
	c0.load4(m[0]);
	c1.load4(m[1]);
	c2.load4(m[2]);
	c3.load4(m[3]);
	hkMatrix4 fill;
	fill.setCols(c0, c1, c2, c3);
	return unwrap(node)->m_keyFrames.setSize(size, fill);
}
int HAVOK_C_CALL hkxNode_keyFrames_getSize(hkxNodeRef node)
{
	return unwrap(node)->m_keyFrames.getSize();
}
void HAVOK_C_CALL hkxNode_keyFrames_getValue(hkxNodeRef node, int index, float m[4][4])
{
	hkVector4f c0;
	hkVector4f c1;
	hkVector4f c2;
	hkVector4f c3;
	unwrap(node)->m_keyFrames[index].getCols(c0, c1, c2, c3);
	c0.store4(m[0]);
	c1.store4(m[1]);
	c2.store4(m[2]);
	c3.store4(m[3]);
	return;
}
void HAVOK_C_CALL hkxNode_keyFrames_pushBack(hkxNodeRef node, float m[4][4])
{
	hkVector4f c0;
	hkVector4f c1;
	hkVector4f c2;
	hkVector4f c3;
	c0.load4(m[0]);
	c1.load4(m[1]);
	c2.load4(m[2]);
	c3.load4(m[3]);
	hkMatrix4 e;
	e.setCols(c0, c1, c2, c3);
	return unwrap(node)->m_keyFrames.pushBack(e);
}
int HAVOK_C_CALL hkxNode_linearKeyFrameHints_getSize(hkxNodeRef node)
{
	return unwrap(node)->m_linearKeyFrameHints.getSize();
}
float *HAVOK_C_CALL hkxNode_linearKeyFrameHints_begin(hkxNodeRef node)
{
	return unwrap(node)->m_linearKeyFrameHints.begin();
}
float *HAVOK_C_CALL hkxNode_linearKeyFrameHints_end(hkxNodeRef node)
{
	return unwrap(node)->m_linearKeyFrameHints.end();
}
int HAVOK_C_CALL hkxNode_linearKeyFrameHints_indexOf(hkxNodeRef node, float keyFrame)
{
	return unwrap(node)->m_linearKeyFrameHints.indexOf(keyFrame);
}
void HAVOK_C_CALL hkxNode_linearKeyFrameHints_pushBack(hkxNodeRef node, float keyFrame)
{
	return unwrap(node)->m_linearKeyFrameHints.pushBack(keyFrame);
}
void HAVOK_C_CALL hkxNode_annotations_pushBack(hkxNodeRef node, float time, char const *description)
{
	hkxNode::AnnotationData annotation;
	annotation.m_time = time;
	annotation.m_description = description;
	return unwrap(node)->m_annotations.pushBack(annotation);
}
void HAVOK_C_CALL hkxNode_children_pushBack(hkxNodeRef node, hkxNodeRef childnode)
{
	return unwrap(node)->m_children.pushBack(unwrap(childnode));
}
void HAVOK_C_CALL hkxNode_selected_set(hkxNodeRef node, bool selected)
{
	unwrap(node)->m_selected = selected;
	return;
}
void HAVOK_C_CALL hkxNode_bone_set(hkxNodeRef node, bool bone)
{
	unwrap(node)->m_bone = bone;
	return;
}
void HAVOK_C_CALL hkxNode_selected_userProperties_set(hkxNodeRef node, char const *s)
{
	return unwrap(node)->m_userProperties.set(s);
}
void HAVOK_C_CALL hkxNode_object_setMesh(hkxNodeRef node, hkxMeshRef mesh)
{
	return unwrap(node)->m_object = unwrap(mesh);
}
void HAVOK_C_CALL hkxNode_object_setSkinBinding(hkxNodeRef node, hkxSkinBindingRef skin)
{
	return unwrap(node)->m_object = unwrap(skin);
}
void HAVOK_C_CALL hkxNode_removeReference(hkxNodeRef node)
{
	return unwrap(node)->removeReference();
}

hkxMeshRef HAVOK_C_CALL hkxMesh_new()
{
	hkxMesh *mesh = new hkxMesh();
	return wrap(mesh);
}
void HAVOK_C_CALL hkxMesh_sections_setSize(hkxMeshRef mesh, int size)
{
	return unwrap(mesh)->m_sections.setSize(size);
}
void HAVOK_C_CALL hkxMesh_sections_setValue(hkxMeshRef mesh, int index, hkxMeshSectionRef meshsection)
{
	return unwrap(mesh)->m_sections[index] = unwrap(meshsection);
}
void HAVOK_C_CALL hkxMesh_removeReference(hkxMeshRef mesh)
{
	return unwrap(mesh)->removeReference();
}
void HAVOK_C_CALL hkxMeshSectionUtil_computeTangents(hkxMeshRef mesh, bool splitVertices, char const *nameHint)
{
	return hkxMeshSectionUtil::computeTangents(unwrap(mesh), splitVertices, nameHint);
}
hkxMeshSectionRef HAVOK_C_CALL hkxMeshSection_new()
{
	hkxMeshSection *meshsection = new hkxMeshSection();
	return wrap(meshsection);
}
void HAVOK_C_CALL hkxMeshSection_vertexBuffer_set(hkxMeshSectionRef meshsection, hkxVertexBufferRef vb)
{
	unwrap(meshsection)->m_vertexBuffer = unwrap(vb);
	return;
}
void HAVOK_C_CALL hkxMeshSection_indexBuffers_setSize(hkxMeshSectionRef meshsection, int size)
{
	return unwrap(meshsection)->m_indexBuffers.setSize(size);
}
void HAVOK_C_CALL hkxMeshSection_indexBuffers_setValue(hkxMeshSectionRef meshsection, int index, hkxIndexBufferRef ib)
{
	return unwrap(meshsection)->m_indexBuffers[index] = unwrap(ib);
}
void HAVOK_C_CALL hkxMeshSection_removeReference(hkxMeshSectionRef meshsection)
{
	return unwrap(meshsection)->removeReference();
}

hkxVertexDescriptionRef HAVOK_C_CALL hkxVertexDescription_new()
{
	hkxVertexDescription *format = new hkxVertexDescription();
	return wrap(format);
}
void HAVOK_C_CALL hkxVertexDescription_decls_pushBack(hkxVertexDescriptionRef format, int16_t dataUsage, int8_t dataType, int8_t numElements)
{
	return unwrap(format)->m_decls.pushBack(hkxVertexDescription::ElementDecl(static_cast<hkxVertexDescription::DataUsage>(dataUsage), static_cast<hkxVertexDescription::DataType>(dataType), (hkUint8)numElements));
}
void HAVOK_C_CALL hkxVertexDescription_delete(hkxVertexDescriptionRef format)
{
	delete unwrap(format);
	return;
}

void HAVOK_C_CALL hkxSkinUtils_quantizeWeights(float const inputWeights[4], uint8_t quantizedWeights[4])
{
	return hkxSkinUtils::quantizeWeights(inputWeights, quantizedWeights);
}

hkxVertexBufferRef HAVOK_C_CALL hkxVertexBuffer_new()
{
	hkxVertexBuffer *vb = new hkxVertexBuffer();
	return wrap(vb);
}
void HAVOK_C_CALL hkxVertexBuffer_setNumVertices(hkxVertexBufferRef vb, int n, hkxVertexDescriptionRef format)
{
	return unwrap(vb)->setNumVertices(n, *unwrap(format));
}
uint32_t HAVOK_C_CALL hkxVertexBuffer_getElementDecl_byteStride(hkxVertexBufferRef vb, int16_t dataUsage, int index)
{
	hkxVertexDescription const *format = &unwrap(vb)->getVertexDesc();
	hkxVertexDescription::ElementDecl const *decl = format->getElementDecl(static_cast<hkxVertexDescription::DataUsage>(dataUsage), index);
	return (decl != NULL) ? decl->m_byteStride : 0;
}
void *HAVOK_C_CALL hkxVertexBuffer_getElementDecl_VertexDataPtr(hkxVertexBufferRef vb, int16_t dataUsage, int index)
{
	hkxVertexDescription const *format = &unwrap(vb)->getVertexDesc();
	hkxVertexDescription::ElementDecl const *decl = format->getElementDecl(static_cast<hkxVertexDescription::DataUsage>(dataUsage), index);
	return (decl != NULL) ? unwrap(vb)->getVertexDataPtr(*decl) : NULL;
}
void HAVOK_C_CALL hkxVertexBuffer_removeReference(hkxVertexBufferRef vb)
{
	return unwrap(vb)->removeReference();
}

hkxIndexBufferRef HAVOK_C_CALL hkxIndexBuffer_new()
{
	hkxIndexBuffer *ib = new hkxIndexBuffer();
	return wrap(ib);
}
void HAVOK_C_CALL hkxIndexBuffer_indexType_set(hkxIndexBufferRef ib, int8_t indexType)
{
	return unwrap(ib)->m_indexType = static_cast<hkxIndexBuffer::IndexType>(indexType);
}
void HAVOK_C_CALL hkxIndexBuffer_indices32_setSize(hkxIndexBufferRef ib, int size)
{
	return unwrap(ib)->m_indices32.setSize(size);
}
uint32_t *HAVOK_C_CALL hkxIndexBuffer_indices32_begin(hkxIndexBufferRef ib)
{
	return unwrap(ib)->m_indices32.begin();
}
void HAVOK_C_CALL hkxIndexBuffer_vertexBaseOffset_set(hkxIndexBufferRef ib, uint32_t vertexBaseOffset)
{
	unwrap(ib)->m_vertexBaseOffset = vertexBaseOffset;
	return;
}
void HAVOK_C_CALL hkxIndexBuffer_length_set(hkxIndexBufferRef ib, uint32_t length)
{
	unwrap(ib)->m_length = length;
	return;
}
void HAVOK_C_CALL hkxIndexBuffer_removeReference(hkxIndexBufferRef ib)
{
	return unwrap(ib)->removeReference();
}

hkxSkinBindingRef HAVOK_C_CALL hkxSkinBinding_new()
{
	hkxSkinBinding *skin = new hkxSkinBinding();
	return wrap(skin);
}
void HAVOK_C_CALL hkxSkinBinding_mesh_set(hkxSkinBindingRef skin, hkxMeshRef mesh)
{
	return unwrap(skin)->m_mesh = unwrap(mesh);
}
void HAVOK_C_CALL hkxSkinBinding_initSkinTransform_set(hkxSkinBindingRef skin, float m[4][4])
{
	hkVector4f c0;
	hkVector4f c1;
	hkVector4f c2;
	hkVector4f c3;
	c0.load4(m[0]);
	c1.load4(m[1]);
	c2.load4(m[2]);
	c3.load4(m[3]);
	return unwrap(skin)->m_initSkinTransform.setCols(c0, c1, c2, c3);
}
void HAVOK_C_CALL hkxSkinBinding_bindPose_setSize(hkxSkinBindingRef skin, int size)
{
	return unwrap(skin)->m_bindPose.setSize(size);
}
void HAVOK_C_CALL hkxSkinBinding_bindPose_setValue(hkxSkinBindingRef skin, int index, float m[4][4])
{
	hkVector4f c0;
	hkVector4f c1;
	hkVector4f c2;
	hkVector4f c3;
	c0.load4(m[0]);
	c1.load4(m[1]);
	c2.load4(m[2]);
	c3.load4(m[3]);
	return unwrap(skin)->m_bindPose[index].setCols(c0, c1, c2, c3);
}
void HAVOK_C_CALL hkxSkinBinding_nodeNames_setSize(hkxSkinBindingRef skin, int size)
{
	return unwrap(skin)->m_nodeNames.setSize(size);
}
void HAVOK_C_CALL hkxSkinBinding_nodeNames_setValue(hkxSkinBindingRef skin, int index, char const *nodeName)
{
	return unwrap(skin)->m_nodeNames[index].set(nodeName);
}
void HAVOK_C_CALL hkxSkinBinding_removeReference(hkxSkinBindingRef skin)
{
	return unwrap(skin)->removeReference();
}

hkErrorRef HAVOK_C_CALL hkError_getInstance()
{
	hkError &error = hkError::getInstance();
	return wrap(&error);
}

int HAVOK_C_CALL hkError_messageAssert(hkErrorRef error, int id, char const *description, char const *file, int line)
{
	return unwrap(error)->message(hkError::MESSAGE_ASSERT, id, description, file, line);
}
int HAVOK_C_CALL hkError_messageWarning(hkErrorRef error, int id, char const *description, char const *file, int line)
{
	return unwrap(error)->message(hkError::MESSAGE_WARNING, id, description, file, line);
}
int HAVOK_C_CALL hkError_messageError(hkErrorRef error, int id, char const *description, char const *file, int line)
{
	return unwrap(error)->message(hkError::MESSAGE_ERROR, id, description, file, line);
}

//"hkProductFeatures::initialize" referenced in function "hkBaseSystem::init"
#include <Common/Base/keycode.cxx>
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_DESTRUCTION_2012
#undef HK_FEATURE_PRODUCT_SCRIPT
#undef HK_FEATURE_PRODUCT_SIMULATION
#include <Common/Base/Config/hkProductFeaturesNoPatchesOrCompat.h>
//#define HK_EXCLUDE_FEATURE_MemoryTracker
//#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
//#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
//#define HK_EXCLUDE_FEATURE_RegisterReflectedClasses
//#define HK_CLASSES_FILE <Havok-C/hkEmptyClasses.h>
//#define HK_EXCLUDE_LIBRARY_hkSceneData
//#define HK_EXCLUDE_LIBRARY_hkGeometryUtilities
//#define HK_EXCLUDE_LIBRARY_hkCompat
//#define HK_EXCLUDE_LIBRARY_hkgpConvexDecomposition
//#define HK_EXCLUDE_LIBRARY_hkpVehicle
//#define HK_EXCLUDE_FEATURE_ConvexDecomposition
#include <Common/Base/Config/hkProductFeatures.cxx>

// Platform specific initialization required before initializing Havok's memory system.
// This file is meant to be used in stand-alone demos as the demo framework's platform
// initialization functions sometimes depend on the graphics system (e.g Wii, see
// PlatformInitWii.cpp and hkgSystemGCN.cpp)
//#include <Common/Base/System/Init/PlatformInit.cxx>

//hkPatch.cxx
int GetEngineOffset(char const *)
{
	return 717031412;
}