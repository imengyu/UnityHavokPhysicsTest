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
	CHECK_PARAM_PTR(vertices, "vertices");

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::ConvexVerticesShape;

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
}
sPhysicsShape* CreateConvexVerticesShapeByConvexHullResult(sConvexHullResult* result, float convexRadius) {
	CHECK_PARAM_PTR(result, "result");

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::ConvexVerticesShape;

	hkpConvexVerticesShape::BuildConfig config;
	config.m_convexRadius = convexRadius;

	s->shape = new hkpConvexVerticesShape(hkStridedVertices(result->geometry.m_vertices), config);
	return s;
}

sPhysicsShape* CreateConvexTranslateShape(sPhysicsShape* child, spVec3 translation) {
	CHECK_PARAM_PTR(child, "child");

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::ConvexTranslateShape;
	s->shape = new hkpConvexTranslateShape((hkpConvexShape*)child->shape, Vec3TohkVec4(translation));
	return s;
}
sPhysicsShape* CreateConvexTransformShape(sPhysicsShape* child, spTransform transform) {
	CHECK_PARAM_PTR(child, "child");

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::ConvexTransformShape;
	s->shape = new hkpConvexTransformShape((hkpConvexShape*)child->shape, TransformTohkQsTransform(transform));
	return s;
}
sPhysicsShape* CreateListShape(sPhysicsShape** childs, int childCount) {
	CHECK_PARAM_PTR(childs, "childs");

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::ListShape;

	hkArray<hkpShape*> shapeArray;
	for (int i = 0; i < childCount; i++)
		shapeArray.pushBack(childs[i]->shape);
	s->shape = new hkpListShape(shapeArray.begin(), shapeArray.getSize());
	return s;
}
sPhysicsShape* CreateStaticCompoundShape(sPhysicsShape** childs, spTransform*transforms, int childCount) {
	CHECK_PARAM_PTR(childs, "childs");
	CHECK_PARAM_PTR(transforms, "transforms");

	sPhysicsShape* s = new sPhysicsShape();
	s->type = ePhysicsShapeType::StaticCompoundShape;

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
}

void StaticCompoundShapeSetInstanceEnabled(sPhysicsShape* pStaticCompoundShape, int id, int enabled) {
	CHECK_PARAM_PTR(pStaticCompoundShape, "pStaticCompoundShape");
	if (pStaticCompoundShape->type != ePhysicsShapeType::StaticCompoundShape) {
		CallbackWithError("input shape is not StaticCompoundShape");
		return;
	}
	((hkpStaticCompoundShape*)pStaticCompoundShape->shape)->setInstanceEnabled(id, enabled);
}
int StaticCompoundShapeIsInstanceEnabled(sPhysicsShape* pStaticCompoundShape, int id) {
	CHECK_PARAM_PTR(pStaticCompoundShape, "pStaticCompoundShape");
	if (pStaticCompoundShape->type != ePhysicsShapeType::StaticCompoundShape) {
		CallbackWithError("input shape is not StaticCompoundShape");
		return 0;
	}
	return ((hkpStaticCompoundShape*)pStaticCompoundShape->shape)->isInstanceEnabled(id);
}
void StaticCompoundShapeEnableAllInstancesAndShapeKeys(sPhysicsShape* pStaticCompoundShape) {
	CHECK_PARAM_PTR(pStaticCompoundShape, "pStaticCompoundShape");
	if (pStaticCompoundShape->type != ePhysicsShapeType::StaticCompoundShape) {
		CallbackWithError("input shape is not StaticCompoundShape");
		return;
	}
	((hkpStaticCompoundShape*)pStaticCompoundShape->shape)->enableAllInstancesAndShapeKeys();
}

void DestroyShape(sPhysicsShape*s) {
	CHECK_PARAM_PTR(s, "s");
	s->shape->removeReference();
	if (s->staticCompoundShapeRetIds) {
		delete[] s->staticCompoundShapeRetIds;
		s->staticCompoundShapeRetIds = nullptr;
	}
	delete s;
}

void GetConvexHullResultTriangles(sConvexHullResult* result, float* trianglesBuffer, int count) {
	CHECK_PARAM_PTR(result, "result");
	CHECK_PARAM_PTR(trianglesBuffer, "trianglesBuffer");

	int i = 0;
	auto triangles = &result->geometry.m_triangles;
	for (auto it = triangles->begin(); it != triangles->end(); it++, i++) {
		trianglesBuffer[i * 3] = it->m_a;
		trianglesBuffer[i * 3 + 1] = it->m_b;
		trianglesBuffer[i * 3 + 2] = it->m_c;
	}
}
void GetConvexHullResultVertices(sConvexHullResult* result, float* pointsBuffer, int numPoints) {
	CHECK_PARAM_PTR(result, "result");
	CHECK_PARAM_PTR(pointsBuffer, "pointsBuffer");

	int i = 0;
	auto vertices = &result->geometry.m_vertices;
	for (auto it = vertices->begin(); it != vertices->end(); it++, i++) {
		pointsBuffer[i * 3] = it->getComponent<0>();
		pointsBuffer[i * 3 + 1] = it->getComponent<1>();
		pointsBuffer[i * 3 + 2] = it->getComponent<2>();
	}
}
sConvexHullResult* Build3DPointsConvexHull(float* points, int numPoints) {

	CHECK_PARAM_PTR(points, "points");
	if (numPoints >= 8192) {
		CallbackWithError("Build3DPointsConvexHull: Too much points: %d > 8192", numPoints);
		return;
	}

	// generate a convex geometry
	hkArray<hkVector4> hkPoints(numPoints);
	for (int i = 0; i < numPoints; i += 3)
	{
		hkVector4 xyz(
			points[i],
			points[i + 1],
			points[i + 2]);
		hkPoints.pushBack(xyz);
	}

	hkgpConvexHull* convexHull = new hkgpConvexHull();
	convexHull->build(hkPoints.begin(), numPoints);
	convexHull->buildIndices();

	auto aabb = convexHull->getBoundingBox(hkgpConvexHull::Inputs::SOURCE_VERTICES);
	
	sConvexHullResult* result = new sConvexHullResult();
	result->aabb[0] = aabb.m_min.getComponent<0>();
	result->aabb[1] = aabb.m_min.getComponent<1>();
	result->aabb[2] = aabb.m_min.getComponent<2>();
	result->aabb[3] = aabb.m_min.getComponent<3>();
	result->aabb[4] = aabb.m_max.getComponent<0>();
	result->aabb[5] = aabb.m_max.getComponent<1>();
	result->aabb[6] = aabb.m_max.getComponent<2>();
	result->aabb[7] = aabb.m_max.getComponent<3>();

	convexHull->generateGeometry(hkgpConvexHull::Inputs::SOURCE_VERTICES, result->geometry);
	
	result->trianglesCount = result->geometry.m_triangles.getSize();
	result->verticesCount = result->geometry.m_vertices.getSize();
	return result;
}
sConvexHullResult* Build3DFromPlaneConvexHull(float* panels, int numPanels) {

	CHECK_PARAM_PTR(panels, "panels");
	if (numPanels >= 8192) {
		CallbackWithError("Build3DPointsConvexHull: Too much panels: %d > 8192", numPanels);
		return;
	}

	// generate a convex geometry
	hkArray<hkVector4> hkPanels(numPanels * 4);
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

	auto aabb = convexHull->getBoundingBox(hkgpConvexHull::Inputs::SOURCE_VERTICES);

	sConvexHullResult* result = new sConvexHullResult();
	result->aabb[0] = aabb.m_min.getComponent<0>();
	result->aabb[1] = aabb.m_min.getComponent<1>();
	result->aabb[2] = aabb.m_min.getComponent<2>();
	result->aabb[3] = aabb.m_min.getComponent<3>();
	result->aabb[4] = aabb.m_max.getComponent<0>();
	result->aabb[5] = aabb.m_max.getComponent<1>();
	result->aabb[6] = aabb.m_max.getComponent<2>();
	result->aabb[7] = aabb.m_max.getComponent<3>();

	convexHull->generateGeometry(hkgpConvexHull::Inputs::SOURCE_VERTICES, result->geometry);

	result->trianglesCount = result->geometry.m_triangles.getSize();
	result->verticesCount = result->geometry.m_vertices.getSize();
	return result;
}