#pragma once
#include "Physics_RT.h"

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct hkMemoryRouter *hkMemoryRouterRef;
	typedef struct hkJobQueue*hkJobQueueRef;
	typedef struct hkProcessContext *hkProcessContextRef;
	typedef struct hkVisualDebugger *hkVisualDebuggerRef;
	typedef struct hkObjectResource *hkObjectResourceRef;
	typedef struct hkRootLevelContainer *hkRootLevelContainerRef;
	typedef struct hkxScene *hkxSceneRef;
	typedef struct hkxNode *hkxNodeRef;
	typedef struct hkxMesh *hkxMeshRef;
	typedef struct hkxMeshSection *hkxMeshSectionRef;
	typedef struct hkxVertexDescription *hkxVertexDescriptionRef;
	typedef struct hkxVertexBuffer *hkxVertexBufferRef;
	typedef struct hkxIndexBuffer *hkxIndexBufferRef;
	typedef struct hkxSkinBinding *hkxSkinBindingRef;
	typedef struct hkxAttributeHolder *hkxAttributeHolderRef;
	typedef struct hkxAttribute *hkxAttributeRef;
	typedef struct hkError *hkErrorRef;
	typedef struct hkpWorld* hkpWorldRef;
	typedef struct hkpCollisionDispatcher* hkpCollisionDispatcherRef;
	typedef struct hkpShape* hkpShapeRef;
	typedef struct hkpConvexShape* hkpConvexShapeRef;
	typedef struct hkpEntity* hkpEntityRef;

	HAVOK_C_API void HAVOK_C_CALL hkPlatformInit();
	HAVOK_C_API int8_t HAVOK_C_CALL hkMemoryInitUtil_quit();
	HAVOK_C_API int8_t HAVOK_C_CALL hkBaseSystem_init(hkMemoryRouterRef memoryRouter, void(HAVOK_C_PTR *errorReport)(char const *msg, void *errorReportObject), void *errorReportObject);
	HAVOK_C_API int8_t HAVOK_C_CALL hkBaseSystem_quit();

	HAVOK_C_API void HAVOK_C_CALL hkThreadNumber_set(int threadNumber);
	HAVOK_C_API hkJobQueueRef HAVOK_C_CALL hkJobQueue_new(int numCpuThreads);
	HAVOK_C_API int8_t HAVOK_C_CALL hkJobQueue_processAllJobs(hkJobQueueRef jobQueue);
	HAVOK_C_API void HAVOK_C_CALL hkJobQueue_delete(hkJobQueueRef jobQueue);

	HAVOK_C_API void HAVOK_C_CALL hkProcessContext_syncTimers(hkProcessContextRef context);
	HAVOK_C_API hkVisualDebuggerRef HAVOK_C_CALL hkVisualDebugger_new(hkProcessContextRef *contexts, int contextCount);
	HAVOK_C_API void HAVOK_C_CALL hkVisualDebugger_serve(hkVisualDebuggerRef vdb);
	HAVOK_C_API void HAVOK_C_CALL hkVisualDebugger_step(hkVisualDebuggerRef vdb);
	HAVOK_C_API void HAVOK_C_CALL hkVisualDebugger_removeReference(hkVisualDebuggerRef vdb);
	HAVOK_C_API void HAVOK_C_CALL hkProcessRegisterUtil_registerAllCommonProcesses();

	HAVOK_C_API hkObjectResourceRef HAVOK_C_CALL hkSerializeUtil_loadOnHeap(void *pStreamReaderRef, int(HAVOK_C_PTR *pFn_StreamReader_read)(void *pStreamReaderRef, void *buf, int nbytes), int(HAVOK_C_PTR *pFn_StreamReader_seek)(void *pStreamReaderRef, int offset, int whence));

	HAVOK_C_API hkRootLevelContainerRef HAVOK_C_CALL hkObjectResource_stealContents_hkOpaqueRootLevelContainer(hkObjectResourceRef res);
	HAVOK_C_API void HAVOK_C_CALL hkObjectResource_removeReference(hkObjectResourceRef res);

	HAVOK_C_API int8_t HAVOK_C_CALL hkSerializeUtil_save(hkRootLevelContainerRef container, void *pStreamWriterRef, int(HAVOK_C_PTR *pFn_StreamWriter_write)(void *pStreamWriterRef, void *buf, int nbytes), int(HAVOK_C_PTR *pFn_StreamWriter_seek)(void *pStreamWriterRef, int offset, int whence), int8_t options);

	HAVOK_C_API hkRootLevelContainerRef HAVOK_C_CALL hkRootLevelContainer_new();
	HAVOK_C_API void HAVOK_C_CALL hkRootLevelContainer_namedVariant_pushObject_hkxSence(hkRootLevelContainerRef container, char const *name, hkxSceneRef scene);
	HAVOK_C_API hkxSceneRef HAVOK_C_CALL hkRootLevelContainer_findObject_hkxScene(hkRootLevelContainerRef container);
	HAVOK_C_API void HAVOK_C_CALL hkRootLevelContainer_delete(hkRootLevelContainerRef container);

	HAVOK_C_API hkxSceneRef HAVOK_C_CALL hkxScene_new();
	HAVOK_C_API void HAVOK_C_CALL hkxScene_modeller_set(hkxSceneRef scene, char const *);
	HAVOK_C_API void HAVOK_C_CALL hkxScene_asset_set(hkxSceneRef scene, char const *);
	HAVOK_C_API hkxNodeRef HAVOK_C_CALL hkxScene_rootNode(hkxSceneRef scene);
	HAVOK_C_API void HAVOK_C_CALL hkxScene_rootNode_set(hkxSceneRef scene, hkxNodeRef);
	HAVOK_C_API uint32_t HAVOK_C_CALL hkxScene_numFrames(hkxSceneRef scene);
	HAVOK_C_API void HAVOK_C_CALL hkxScene_numFrames_set(hkxSceneRef scene, uint32_t);
	HAVOK_C_API float HAVOK_C_CALL hkxScene_sceneLength(hkxSceneRef scene);
	HAVOK_C_API void HAVOK_C_CALL hkxScene_sceneLength_set(hkxSceneRef scene, float);
	HAVOK_C_API void HAVOK_C_CALL hkxScene_meshes_pushBack(hkxSceneRef scene, hkxMeshRef mesh);
	HAVOK_C_API void HAVOK_C_CALL hkxScene_skinBindings_pushBack(hkxSceneRef scene, hkxSkinBindingRef skin);
	HAVOK_C_API void HAVOK_C_CALL hkxScene_removeReference(hkxSceneRef scene);

	HAVOK_C_API hkxNodeRef HAVOK_C_CALL hkxNode_new();
	HAVOK_C_API char const *HAVOK_C_CALL hkxNode_name(hkxNodeRef node);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_name_set(hkxNodeRef node, char const *);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_keyFrames_setSize(hkxNodeRef node, int);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_keyFrames_setValue(hkxNodeRef node, int index, float[4][4]);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_keyFrames_setSizeValue(hkxNodeRef node, int, float[4][4]);
	HAVOK_C_API int HAVOK_C_CALL hkxNode_keyFrames_getSize(hkxNodeRef node);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_keyFrames_getValue(hkxNodeRef node, int index, float[4][4]);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_keyFrames_pushBack(hkxNodeRef node, float[4][4]);
	HAVOK_C_API int HAVOK_C_CALL hkxNode_linearKeyFrameHints_getSize(hkxNodeRef node);
	HAVOK_C_API float *HAVOK_C_CALL hkxNode_linearKeyFrameHints_begin(hkxNodeRef node);
	HAVOK_C_API float *HAVOK_C_CALL hkxNode_linearKeyFrameHints_end(hkxNodeRef node);
	HAVOK_C_API int HAVOK_C_CALL hkxNode_linearKeyFrameHints_indexOf(hkxNodeRef node, float);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_linearKeyFrameHints_pushBack(hkxNodeRef node, float);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_annotations_pushBack(hkxNodeRef node, float, char const *);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_children_pushBack(hkxNodeRef node, hkxNodeRef);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_selected_set(hkxNodeRef node, bool);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_bone_set(hkxNodeRef node, bool);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_selected_userProperties_set(hkxNodeRef node, char const *);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_object_setMesh(hkxNodeRef node, hkxMeshRef mesh);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_object_setSkinBinding(hkxNodeRef node, hkxSkinBindingRef skin);
	HAVOK_C_API void HAVOK_C_CALL hkxNode_removeReference(hkxNodeRef node);

	HAVOK_C_API hkxMeshRef HAVOK_C_CALL hkxMesh_new();
	HAVOK_C_API void HAVOK_C_CALL hkxMesh_sections_setSize(hkxMeshRef mesh, int size);
	HAVOK_C_API void HAVOK_C_CALL hkxMesh_sections_setValue(hkxMeshRef mesh, int index, hkxMeshSectionRef meshsection);
	HAVOK_C_API void HAVOK_C_CALL hkxMesh_removeReference(hkxMeshRef mesh);

	HAVOK_C_API void HAVOK_C_CALL hkxMeshSectionUtil_computeTangents(hkxMeshRef mesh, bool splitVertices, char const *nameHint);

	HAVOK_C_API hkxMeshSectionRef HAVOK_C_CALL hkxMeshSection_new();
	HAVOK_C_API void HAVOK_C_CALL hkxMeshSection_vertexBuffer_set(hkxMeshSectionRef meshsection, hkxVertexBufferRef vb);
	HAVOK_C_API void HAVOK_C_CALL hkxMeshSection_indexBuffers_setSize(hkxMeshSectionRef meshsection, int size);
	HAVOK_C_API void HAVOK_C_CALL hkxMeshSection_indexBuffers_setValue(hkxMeshSectionRef meshsection, int index, hkxIndexBufferRef ib);
	HAVOK_C_API void HAVOK_C_CALL hkxMeshSection_removeReference(hkxMeshSectionRef meshsection);

	HAVOK_C_API hkxVertexDescriptionRef HAVOK_C_CALL hkxVertexDescription_new();
	HAVOK_C_API void HAVOK_C_CALL hkxVertexDescription_decls_pushBack(hkxVertexDescriptionRef format, int16_t dataUsage, int8_t dataType, int8_t numElements);
	HAVOK_C_API void HAVOK_C_CALL hkxVertexDescription_delete(hkxVertexDescriptionRef format);

	HAVOK_C_API void HAVOK_C_CALL hkxSkinUtils_quantizeWeights(float const inputWeights[4], uint8_t quantizedWeights[4]);

	HAVOK_C_API hkxVertexBufferRef HAVOK_C_CALL hkxVertexBuffer_new();
	HAVOK_C_API void HAVOK_C_CALL hkxVertexBuffer_setNumVertices(hkxVertexBufferRef vb, int n, hkxVertexDescriptionRef format);
	HAVOK_C_API uint32_t HAVOK_C_CALL hkxVertexBuffer_getElementDecl_byteStride(hkxVertexBufferRef vb, int16_t dataUsage, int index);
	HAVOK_C_API void *HAVOK_C_CALL hkxVertexBuffer_getElementDecl_VertexDataPtr(hkxVertexBufferRef vb, int16_t dataUsage, int index);
	HAVOK_C_API void HAVOK_C_CALL hkxVertexBuffer_removeReference(hkxVertexBufferRef vb);

	HAVOK_C_API hkxIndexBufferRef HAVOK_C_CALL hkxIndexBuffer_new();
	HAVOK_C_API void HAVOK_C_CALL hkxIndexBuffer_indexType_set(hkxIndexBufferRef ib, int8_t indexType);
	HAVOK_C_API void HAVOK_C_CALL hkxIndexBuffer_indices32_setSize(hkxIndexBufferRef ib, int size);
	HAVOK_C_API uint32_t * HAVOK_C_CALL hkxIndexBuffer_indices32_begin(hkxIndexBufferRef ib);
	HAVOK_C_API void HAVOK_C_CALL hkxIndexBuffer_vertexBaseOffset_set(hkxIndexBufferRef ib, uint32_t vertexBaseOffset);
	HAVOK_C_API void HAVOK_C_CALL hkxIndexBuffer_length_set(hkxIndexBufferRef ib, uint32_t length);
	HAVOK_C_API void HAVOK_C_CALL hkxIndexBuffer_removeReference(hkxIndexBufferRef ib);

	HAVOK_C_API hkxSkinBindingRef HAVOK_C_CALL hkxSkinBinding_new();
	HAVOK_C_API void HAVOK_C_CALL hkxSkinBinding_mesh_set(hkxSkinBindingRef skin, hkxMeshRef mesh);
	HAVOK_C_API void HAVOK_C_CALL hkxSkinBinding_initSkinTransform_set(hkxSkinBindingRef skin, float m[4][4]);
	HAVOK_C_API void HAVOK_C_CALL hkxSkinBinding_bindPose_setSize(hkxSkinBindingRef skin, int size);
	HAVOK_C_API void HAVOK_C_CALL hkxSkinBinding_bindPose_setValue(hkxSkinBindingRef skin, int index, float m[4][4]);
	HAVOK_C_API void HAVOK_C_CALL hkxSkinBinding_nodeNames_setSize(hkxSkinBindingRef skin, int size);
	HAVOK_C_API void HAVOK_C_CALL hkxSkinBinding_nodeNames_setValue(hkxSkinBindingRef skin, int index, char const *nodeName);
	HAVOK_C_API void HAVOK_C_CALL hkxSkinBinding_removeReference(hkxSkinBindingRef skin);

	HAVOK_C_API hkErrorRef HAVOK_C_CALL hkError_getInstance();

	HAVOK_C_API int HAVOK_C_CALL hkError_messageAssert(hkErrorRef error, int id, char const *description, char const *file, int line);
	HAVOK_C_API int HAVOK_C_CALL hkError_messageWarning(hkErrorRef error, int id, char const *description, char const *file, int line);
	HAVOK_C_API int HAVOK_C_CALL hkError_messageError(hkErrorRef error, int id, char const *description, char const *file, int line);

#ifdef __cplusplus
}
#endif

#define WARP_FUNC(source,ref) static inline ref wrap(source *inSource) { return reinterpret_cast<ref>(inSource); }\
static inline source* unwrap(ref inSource) { return reinterpret_cast<source*>(inSource); }
#define WARP wrap(ptr)
#define UNWARP unwrap(ptr)

template <typename T>
static inline T* CopyClassToHeap(T const&src) {
	size_t size = sizeof(T);
	void* memory = malloc(size);
	memcpy_s(memory, size, &src, size);
	return memory;
}

#define TOHEAP(src, type) CopyClassToHeap<type>(src)