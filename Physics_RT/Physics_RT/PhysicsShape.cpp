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
#include <Common/Internal/GeometryProcessing/ConvexHull/hkgpConvexHull.h>

sPhysicsShape* CreateBoxShape(spVec3 boxSize, float radius) {
	TRY_BEGIN

	sPhysicsShape* s = new sPhysicsShape();
	s->type = BoxShape;
	s->shape = new hkpBoxShape(Vec3TohkVec4(boxSize), radius);
	return s;

	TRY_END(nullptr)
}
sPhysicsShape* CreateSphereShape(float radius) {
	TRY_BEGIN

	sPhysicsShape* s = new sPhysicsShape();
	s->type = SphereShape;
	s->shape = new hkpSphereShape(radius);
	return s;

	TRY_END(nullptr)
}
sPhysicsShape* CreateCapsuleShape(spVec3 start, spVec3 end, float radius) {
	TRY_BEGIN

	sPhysicsShape* s = new sPhysicsShape();
	s->type = CapsuleShape;
	s->shape = new hkpCapsuleShape(Vec3TohkVec4(start), Vec3TohkVec4(end), radius);
	return s;

	TRY_END(nullptr)
}
sPhysicsShape* CreateCylindeShape(spVec3 start, spVec3 end, float radius, float paddingRadius) {
	TRY_BEGIN

	sPhysicsShape* s = new sPhysicsShape();
	s->type = CylindeShape;
	s->shape = new hkpCylinderShape(Vec3TohkVec4(start), Vec3TohkVec4(end), radius, paddingRadius);
	return s;

	TRY_END(nullptr)
}
sPhysicsShape* CreateTriangleShape(spVec3 v0, spVec3 v1, spVec3 v2) {
	TRY_BEGIN

	sPhysicsShape* s = new sPhysicsShape();
	s->type = TriangleShape;
	s->shape = new hkpTriangleShape(Vec3TohkVec4(v0), Vec3TohkVec4(v1), Vec3TohkVec4(v2));
	return s;

	TRY_END(nullptr)
}
sPhysicsShape* CreateConvexVerticesShape(float *vertices, int numVertices, float convexRadius) {
	TRY_BEGIN
	CHECK_PARAM_PTR(vertices);

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ConvexVerticesShape;

	hkpConvexVerticesShape::BuildConfig config;
	config.m_convexRadius = convexRadius;
	
	// generate a convex geometry
	hkArray<hkVector4> hkVertices(numVertices);
	for (int i = 0; i < numVertices; i += 3)
	{
		hkVector4 xyz(
			vertices[i], 
			vertices[i + 1], 
			vertices[i + 2]);		
		hkVertices.pushBack(xyz);
	}

	s->shape = new hkpConvexVerticesShape(hkStridedVertices(hkVertices), config);
	return s;

	TRY_END(nullptr)
}
sPhysicsShape* CreateConvexVerticesShapeByConvexHullResult(sConvexHullResult* result, float convexRadius) {
	TRY_BEGIN
	CHECK_PARAM_PTR(result);

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ConvexVerticesShape;

	hkpConvexVerticesShape::BuildConfig config;
	config.m_convexRadius = convexRadius;

	s->shape = new hkpConvexVerticesShape(hkStridedVertices(result->geometry.m_vertices), config);
	return s;

	TRY_END(nullptr)
}

sPhysicsShape* CreateConvexTranslateShape(sPhysicsShape* child, spVec3 translation) {
	TRY_BEGIN
	CHECK_PARAM_PTR(child);

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ConvexTranslateShape;
	s->shape = new hkpConvexTranslateShape((hkpConvexShape*)child->shape, Vec3TohkVec4(translation));
	return s;

	TRY_END(nullptr)
}
sPhysicsShape* CreateConvexTransformShape(sPhysicsShape* child, spTransform transform) {
	TRY_BEGIN
	CHECK_PARAM_PTR(child);

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ConvexTransformShape;
	s->shape = new hkpConvexTransformShape((hkpConvexShape*)child->shape, TransformTohkQsTransform(transform));
	return s;

	TRY_END(nullptr)
}
sPhysicsShape* CreateListShape(sPhysicsShape** childs, int childCount) {
	TRY_BEGIN
	CHECK_PARAM_PTR(childs);

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ListShape;

	hkArray<hkpShape*> shapeArray;
	for (int i = 0; i < childCount; i++)
		shapeArray.pushBack(childs[i]->shape);
	s->shape = new hkpListShape(shapeArray.begin(), shapeArray.getSize());
	return s;

	TRY_END(nullptr)
}
sPhysicsShape* CreateStaticCompoundShape(sPhysicsShape** childs, spTransform*transforms, int childCount) {
	TRY_BEGIN
	CHECK_PARAM_PTR(childs);
	CHECK_PARAM_PTR(transforms);

	sPhysicsShape* s = new sPhysicsShape();
	s->type = StaticCompoundShape;

	hkpStaticCompoundShape* staticCompoundShape = new hkpStaticCompoundShape();

	int* ids = new int[childCount];
	hkArray<hkpShape*> shapeArray;
	for (int i = 0; i < childCount; i++)
		ids[i] = staticCompoundShape->addInstance(childs[i]->shape, TransformTohkQsTransform(transforms[i]));
	staticCompoundShape->bake();

	s->shape = staticCompoundShape;
	s->staticCompoundShapeRetIds = ids;
	s->staticCompoundShapeRetIdsCount = childCount;
	return s;

	TRY_END(nullptr)
}

void StaticCompoundShapeSetInstanceEnabled(sPhysicsShape* pStaticCompoundShape, int id, int enabled) {
	TRY_BEGIN
	CHECK_PARAM_PTR(pStaticCompoundShape);

	if (pStaticCompoundShape->type != StaticCompoundShape)
		throw std::exception("StaticCompoundShapeEnableAllInstancesAndShapeKeys: Input shape is not StaticCompoundShape");

	((hkpStaticCompoundShape*)pStaticCompoundShape->shape)->setInstanceEnabled(id, enabled);

	TRY_END_NORET
}
int StaticCompoundShapeIsInstanceEnabled(sPhysicsShape* pStaticCompoundShape, int id) {
	TRY_BEGIN
	CHECK_PARAM_PTR(pStaticCompoundShape);

	if (pStaticCompoundShape->type != StaticCompoundShape)
		throw std::exception("StaticCompoundShapeEnableAllInstancesAndShapeKeys: Input shape is not StaticCompoundShape");

	return ((hkpStaticCompoundShape*)pStaticCompoundShape->shape)->isInstanceEnabled(id);

	TRY_END(0)
}
void StaticCompoundShapeEnableAllInstancesAndShapeKeys(sPhysicsShape* pStaticCompoundShape) {
	TRY_BEGIN
	CHECK_PARAM_PTR(pStaticCompoundShape);

	if (pStaticCompoundShape->type != StaticCompoundShape)
		throw std::exception("StaticCompoundShapeEnableAllInstancesAndShapeKeys: Input shape is not StaticCompoundShape");

	((hkpStaticCompoundShape*)pStaticCompoundShape->shape)->enableAllInstancesAndShapeKeys();

	TRY_END_NORET
}

void DestroyShape(sPhysicsShape*s) {
	TRY_BEGIN
	CHECK_PARAM_PTR(s);

	s->shape->removeReference();
	if (s->staticCompoundShapeRetIds) {
		delete[] s->staticCompoundShapeRetIds;
		s->staticCompoundShapeRetIds = nullptr;
	}
	delete s;

	TRY_END_NORET
}

void GetConvexHullResultTriangles(sConvexHullResult* result, int* trianglesBuffer, int count) {
	TRY_BEGIN
	CHECK_PARAM_PTR(result);
	CHECK_PARAM_PTR(trianglesBuffer);

	int i = 0;
	auto triangles = &result->geometry.m_triangles;
	for (auto it = triangles->begin(); it != triangles->end(); it++, i++) {
		trianglesBuffer[i * 3] = it->m_a;
		trianglesBuffer[i * 3 + 1] = it->m_b;
		trianglesBuffer[i * 3 + 2] = it->m_c;
	}

	TRY_END_NORET
}
void GetConvexHullResultVertices(sConvexHullResult* result, float* pointsBuffer, int numPoints) {
	TRY_BEGIN
	CHECK_PARAM_PTR(result);
	CHECK_PARAM_PTR(pointsBuffer);

	int i = 0;
	auto vertices = &result->geometry.m_vertices;
	for (auto it = vertices->begin(); it != vertices->end(); it++, i++) {
		pointsBuffer[i * 3] = it->getComponent<0>();
		pointsBuffer[i * 3 + 1] = it->getComponent<1>();
		pointsBuffer[i * 3 + 2] = it->getComponent<2>();
	}

	TRY_END_NORET
}
sConvexHullResult* Build3DPointsConvexHull(float* points, int numPoints) {

	TRY_BEGIN
	CHECK_PARAM_PTR(points);

	// generate a convex geometry
	hkArray<hkVector4> hkPoints;
	for (int i = 0; i < numPoints; i++)
	{
		hkVector4 xyz(
			points[i * 3],
			points[i * 3 + 1],
			points[i * 3 + 2]);
		hkPoints.pushBack(xyz);
	}

	hkgpConvexHull* convexHull = new hkgpConvexHull();
	if (convexHull->build(hkPoints.begin(), numPoints) == -1)
		CallbackWithError("ConvexHull failed! ");

	convexHull->buildIndices();

	auto aabb = convexHull->getBoundingBox(hkgpConvexHull::SOURCE_VERTICES);
	
	sConvexHullResult* result = new sConvexHullResult();
	result->aabb[0] = aabb.m_min.getComponent<0>();
	result->aabb[1] = aabb.m_min.getComponent<1>();
	result->aabb[2] = aabb.m_min.getComponent<2>();
	result->aabb[3] = aabb.m_min.getComponent<3>();
	result->aabb[4] = aabb.m_max.getComponent<0>();
	result->aabb[5] = aabb.m_max.getComponent<1>();
	result->aabb[6] = aabb.m_max.getComponent<2>();
	result->aabb[7] = aabb.m_max.getComponent<3>();

	convexHull->generateGeometry(hkgpConvexHull::SOURCE_VERTICES, result->geometry);
	
	result->trianglesCount = result->geometry.m_triangles.getSize();
	result->verticesCount = result->geometry.m_vertices.getSize();
	return result;

	TRY_END(nullptr)
}
sConvexHullResult* Build3DFromPlaneConvexHull(float* panels, int numPanels) {

	TRY_BEGIN
	CHECK_PARAM_PTR(panels);

	// generate a convex geometry
	hkArray<hkVector4> hkPanels;
	for (int i = 0; i < numPanels * 4; i += 3)
	{
		hkVector4 xyz(
			panels[i],
			panels[i + 1],
			panels[i + 2]);
		hkPanels.pushBack(xyz);
	}

	hkgpConvexHull* convexHull = new hkgpConvexHull();
	convexHull->buildFromPlanes(hkPanels.begin(), numPanels);
	convexHull->buildIndices();

	auto aabb = convexHull->getBoundingBox(hkgpConvexHull::SOURCE_VERTICES);

	sConvexHullResult* result = new sConvexHullResult();
	result->aabb[0] = aabb.m_min.getComponent<0>();
	result->aabb[1] = aabb.m_min.getComponent<1>();
	result->aabb[2] = aabb.m_min.getComponent<2>();
	result->aabb[3] = aabb.m_min.getComponent<3>();
	result->aabb[4] = aabb.m_max.getComponent<0>();
	result->aabb[5] = aabb.m_max.getComponent<1>();
	result->aabb[6] = aabb.m_max.getComponent<2>();
	result->aabb[7] = aabb.m_max.getComponent<3>();

	convexHull->generateGeometry(hkgpConvexHull::SOURCE_VERTICES, result->geometry);

	result->trianglesCount = result->geometry.m_triangles.getSize();
	result->verticesCount = result->geometry.m_vertices.getSize();
	return result;

	TRY_END(nullptr)
}