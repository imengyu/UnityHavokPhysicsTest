#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"

enum class ePhysicsShapeType : UINT16 {
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

typedef sPhysicsShape* (__cdecl* fnCreateBoxShape)(spVec3 boxSize, float radius);
typedef sPhysicsShape* (__cdecl* fnCreateSphereShape)(float radius);
typedef sPhysicsShape* (__cdecl* fnCreateCapsuleShape)(spVec3 start, spVec3 end, float radius);
typedef sPhysicsShape* (__cdecl* fnCreateCylindeShape)(spVec3 start, spVec3 end, float radius, float paddingRadius);
typedef sPhysicsShape* (__cdecl* fnCreateTriangleShape)(spVec3 v0, spVec3 v1, spVec3 v2);
typedef sPhysicsShape* (__cdecl* fnCreateConvexVerticesShape)(float* vertices, int numVertices, float convexRadius);
typedef sPhysicsShape* (__cdecl* fnCreateConvexTranslateShape)(sPhysicsShape* child, spVec3 translation);
typedef sPhysicsShape* (__cdecl* fnCreateConvexTransformShape)(sPhysicsShape* child, spTransform transform);
typedef sPhysicsShape* (__cdecl* fnCreateListShape)(sPhysicsShape** childs, int childCount);
typedef sPhysicsShape* (__cdecl* fnCreateStaticCompoundShape)(sPhysicsShape** childs, spTransform* transforms, int childCount);
typedef void(__cdecl* fnStaticCompoundShapeSetInstanceEnabled)(sPhysicsShape* pStaticCompoundShape, int id, int enabled);
typedef int(__cdecl* fnStaticCompoundShapeIsInstanceEnabled)(sPhysicsShape* pStaticCompoundShape, int id);
typedef void(__cdecl* fnStaticCompoundShapeEnableAllInstancesAndShapeKeys)(sPhysicsShape* pStaticCompoundShape);
typedef void(__cdecl* fnDestroyShape)(sPhysicsShape* s);

sPhysicsShape* CreateBoxShape(spVec3 boxSize, float radius);
sPhysicsShape* CreateSphereShape(float radius);
sPhysicsShape* CreateCapsuleShape(spVec3 start, spVec3 end, float radius);
sPhysicsShape* CreateCylindeShape(spVec3 start, spVec3 end, float radius, float paddingRadius);
sPhysicsShape* CreateTriangleShape(spVec3 v0, spVec3 v1, spVec3 v2);
sPhysicsShape* CreateConvexVerticesShape(float* vertices, int numVertices, float convexRadius);

sPhysicsShape* CreateConvexTranslateShape(sPhysicsShape* child, spVec3 translation);
sPhysicsShape* CreateConvexTransformShape(sPhysicsShape* child, spTransform transform);
sPhysicsShape* CreateListShape(sPhysicsShape** childs, int childCount);
sPhysicsShape* CreateStaticCompoundShape(sPhysicsShape** childs, spTransform* transforms, int childCount);

void StaticCompoundShapeSetInstanceEnabled(sPhysicsShape* pStaticCompoundShape, int id, int enabled);
int StaticCompoundShapeIsInstanceEnabled(sPhysicsShape* pStaticCompoundShape, int id);
void StaticCompoundShapeEnableAllInstancesAndShapeKeys(sPhysicsShape* pStaticCompoundShape);

void DestroyShape(sPhysicsShape* s);