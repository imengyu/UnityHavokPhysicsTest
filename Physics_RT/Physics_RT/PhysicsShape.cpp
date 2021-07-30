#include "stdafx.h"
#include "PhysicsHeader.h"
#include "PhysicsFunctions.h"
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics2012/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics2012/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include <Physics2012/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Physics2012/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics2012/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>
#include <Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesConnectivity.h>
#include <Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>

sPhysicsShape* CreateBoxShape(spVec3 boxSize, float radius) {
	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::BoxShape;
	s->shape = new hkpBoxShape(Vec3TohkVec4(boxSize), radius);
	return s;
}
sPhysicsShape* CreateSphereShape(float radius) {
	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::SphereShape;
	s->shape = new hkpSphereShape(radius);
	return s;
}
sPhysicsShape* CreateCapsuleShape(spVec3 start, spVec3 end, float radius) {
	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::CapsuleShape;
	s->shape = new hkpCapsuleShape(Vec3TohkVec4(start), Vec3TohkVec4(end), radius);
	return s;
}
sPhysicsShape* CreateCylindeShape(spVec3 start, spVec3 end, float radius, float paddingRadius) {
	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::CylindeShape;
	s->shape = new hkpCylinderShape(Vec3TohkVec4(start), Vec3TohkVec4(end), radius, paddingRadius);
	return s;
}
sPhysicsShape* CreateTriangleShape(spVec3 v0, spVec3 v1, spVec3 v2) {
	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::TriangleShape;
	s->shape = new hkpTriangleShape(Vec3TohkVec4(v0), Vec3TohkVec4(v1), Vec3TohkVec4(v2));
	return s;
}
sPhysicsShape* CreateConvexVerticesShape(float *vertices, int numVertices, float convexRadius) {
	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::ConvexVerticesShape;

	hkpConvexVerticesShape::BuildConfig config;
	config.m_convexRadius = convexRadius;
	
	// generate a convex geometry
	hkArray<hkVector4> hkVertices(numVertices);
	for (int i = 0; i < numVertices; i += 4)
	{
		hkVector4 xyz(
			vertices[i], 
			vertices[i + 1], 
			vertices[i + 2]);		
		hkVertices.pushBack(xyz);
	}

	s->shape = new hkpConvexVerticesShape(hkStridedVertices(hkVertices), config);
	return s;
}

sPhysicsShape* CreateConvexTranslateShape(sPhysicsShape* child, spVec3 translation) {
	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::ConvexTranslateShape;
	s->shape = new hkpConvexTranslateShape((hkpConvexShape*)child->shape, Vec3TohkVec4(translation));
	return s;
}
sPhysicsShape* CreateConvexTransformShape(sPhysicsShape* child, spTransform transform) {
	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::ConvexTransformShape;
	s->shape = new hkpConvexTransformShape((hkpConvexShape*)child->shape, TransformTohkQsTransform(transform));
	return s;
}
sPhysicsShape* CreateListShape(sPhysicsShape** childs, int childCount) {
	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::ListShape;

	hkArray<hkpShape*> shapeArray;
	for (int i = 0; i < childCount; i++)
		shapeArray.pushBack(childs[i]->shape);
	s->shape = new hkpListShape(shapeArray.begin(), shapeArray.getSize());
	return s;
}
sPhysicsShape* CreateStaticCompoundShape(sPhysicsShape** childs, spTransform*transforms, int childCount) {
	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::StaticCompoundShape;

	hkpStaticCompoundShape* staticCompoundShape = new hkpStaticCompoundShape();

	int* ids = new int[childCount];
	hkArray<hkpShape*> shapeArray;
	for (int i = 0; i < childCount; i++)
		staticCompoundShape->addInstance(childs[i]->shape, TransformTohkQsTransform(transforms[i]));
	staticCompoundShape->bake();

	s->shape = staticCompoundShape;
	return s;
}

void StaticCompoundShapeSetInstanceEnabled(sPhysicsShape* pStaticCompoundShape, int id, int enabled) {	
	if (pStaticCompoundShape->type != ePhysicsShapeType::StaticCompoundShape) {
		CallbackWithError("input shape is not StaticCompoundShape");
		return;
	}
	((hkpStaticCompoundShape*)pStaticCompoundShape->shape)->setInstanceEnabled(id, enabled);
}
int StaticCompoundShapeIsInstanceEnabled(sPhysicsShape* pStaticCompoundShape, int id) {
	if (pStaticCompoundShape->type != ePhysicsShapeType::StaticCompoundShape) {
		CallbackWithError("input shape is not StaticCompoundShape");
		return 0;
	}
	return ((hkpStaticCompoundShape*)pStaticCompoundShape->shape)->isInstanceEnabled(id);
}
void StaticCompoundShapeEnableAllInstancesAndShapeKeys(sPhysicsShape* pStaticCompoundShape) {
	if (pStaticCompoundShape->type != ePhysicsShapeType::StaticCompoundShape) {
		CallbackWithError("input shape is not StaticCompoundShape");
		return;
	}
	((hkpStaticCompoundShape*)pStaticCompoundShape->shape)->enableAllInstancesAndShapeKeys();
}

void DestroyShape(sPhysicsShape*s) {
	s->shape->removeReference();
	if (s->staticCompoundShapeRetIds) {
		delete[] s->staticCompoundShapeRetIds;
		s->staticCompoundShapeRetIds = nullptr;
	}
	delete s;
}