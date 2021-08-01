#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"

enum ePhysicsShapeType : UINT16 {
	BoxShape,
	SphereShape,
	CapsuleShape,
	CylindeShape,
	TriangleShape,
	ConvexVerticesShape,
	ConvexTranslateShape,
	ConvexTransformShape,
	ListShape,
	StaticCompoundShape,
};

struct sPhysicsShape {
	hkpShape* shape;
	ePhysicsShapeType type;
	int* staticCompoundShapeRetIds;
	int staticCompoundShapeRetIdsCount;
};

struct sConvexHullResult {
	float aabb[8]; //min(4) max(4)
	int verticesCount;
	int trianglesCount;
	hkGeometry geometry;
};

sPhysicsShape* CreateBoxShape(spVec3 boxSize, float radius);
sPhysicsShape* CreateSphereShape(float radius);
sPhysicsShape* CreateCapsuleShape(spVec3 start, spVec3 end, float radius);
sPhysicsShape* CreateCylindeShape(spVec3 start, spVec3 end, float radius, float paddingRadius);
sPhysicsShape* CreateTriangleShape(spVec3 v0, spVec3 v1, spVec3 v2);
sPhysicsShape* CreateConvexVerticesShape(float* vertices, int numVertices, float convexRadius);
sPhysicsShape* CreateConvexVerticesShapeByConvexHullResult(sConvexHullResult* result, float convexRadius);

sPhysicsShape* CreateConvexTranslateShape(sPhysicsShape* child, spVec3 translation);
sPhysicsShape* CreateConvexTransformShape(sPhysicsShape* child, spTransform transform);
sPhysicsShape* CreateListShape(sPhysicsShape** childs, int childCount);
sPhysicsShape* CreateStaticCompoundShape(sPhysicsShape** childs, spTransform* transforms, int childCount);

void StaticCompoundShapeSetInstanceEnabled(sPhysicsShape* pStaticCompoundShape, int id, int enabled);
int StaticCompoundShapeIsInstanceEnabled(sPhysicsShape* pStaticCompoundShape, int id);
void StaticCompoundShapeEnableAllInstancesAndShapeKeys(sPhysicsShape* pStaticCompoundShape);

void GetConvexHullResultTriangles(sConvexHullResult* result, int* trianglesBuffer, int count);
void GetConvexHullResultVertices(sConvexHullResult* result, float* pointsBuffer, int numPoints);
sConvexHullResult* Build3DPointsConvexHull(float* points, int numPoints);
sConvexHullResult* Build3DFromPlaneConvexHull(float* panels, int numPanels);

void DestroyShape(sPhysicsShape* s);