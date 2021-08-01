#include "stdafx.h"
#include "PhysicsFunctions.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <list>

extern void** apiArray;
extern sInitStruct initStruct;

void CallbackWithError(char* msg, ...)
{
	if (initStruct.errCallback) {
		va_list ap;
		va_start(ap, msg);

		size_t num_of_chars = _vscprintf(msg, ap);
		char* buffer = new char[num_of_chars + 1];
		vsprintf_s(buffer, num_of_chars + 1, msg, ap);
		initStruct.errCallback(buffer);
		delete buffer;

		va_end(ap);
	}
}

bool lastHasException = false;
char lastException[1024];

//Error Report

void APIErrorReport(const char* msg, void* userArgGivenToInit)
{
	if (initStruct.errCallback)
		initStruct.errCallback(msg);

#if defined(HK_PLATFORM_WIN32)
#ifndef HK_PLATFORM_WINRT
	OutputDebugStringA(msg);
#else
	// Unicode only 
	int sLen = hkString::strLen(msg) + 1;
	wchar_t* wideStr = hkAllocateStack<wchar_t>(sLen);
	mbstowcs_s(HK_NULL, wideStr, sLen, msg, sLen - 1);
	OutputDebugString(wideStr);
	hkDeallocateStack<wchar_t>(wideStr, sLen);
#endif
#endif
}

void APICatchHandler(std::exception& e) {
	lastHasException = true;
#ifdef _MSC_VER
		strcpy_s(lastException, e.what());
#else
		strcpy(lastException, e.what());
#endif
}

EXTERN_C_API int checkException(char* errBuffer, size_t size) {
	if (lastHasException) {
#ifdef _MSC_VER
		strcpy_s(errBuffer, size, lastException);
#else
		strcpy(errBuffer, lastException);
#endif
		lastHasException = false;
		return true;
	}
	return false;
}

std::list<spTransform> smallPoolSpTransform;
std::list<spVec3> smallPoolSpVec3;
std::list<spVec4> smallPoolSpVec4;

spTransform CreateTransform(float px, float py, float pz, float rx, float ry, float rz, float rw, float sx, float sy, float sz)
{
	spTransform v = nullptr;
	if (smallPoolSpTransform.size() > 0) {
		v = smallPoolSpTransform.front();
		smallPoolSpTransform.pop_front();
	}
	else {
		v = new sTransform();
	}
	v->positionX = px;
	v->positionY = py;
	v->positionZ = pz;
	v->scaleX = sx;
	v->scaleY = sy;
	v->scaleZ = sz;
	v->rotationX = rx;
	v->rotationY = ry;
	v->rotationZ = rz;
	v->rotationW = rw;
	return v;
}
spVec3 CreateVec3(float x, float y, float z) {
	spVec3 v = nullptr;
	if (smallPoolSpVec3.size() > 0) {
		v = smallPoolSpVec3.front();
		smallPoolSpVec3.pop_front();
	}
	else {
		v = new sVec3();
	}
	v->x = x;
	v->y = y;
	v->z = z;
	return v;
}
spVec4 CreateVec4(float x, float y, float z, float w) {
	spVec4 v = nullptr;
	if (smallPoolSpVec4.size() > 0) {
		v = smallPoolSpVec4.front();
		smallPoolSpVec4.pop_front();
	}
	else {
		v = new sVec4();
	}
	v->x = x;
	v->y = y;
	v->z = z;
	v->z = w;
	return v;
}

void DestroyVec4(const spVec4 ptr)
{
	CHECK_PARAM_PTR(ptr, "ptr");
	if (smallPoolSpVec4.size() < (size_t)initStruct.smallPoolSize) 
		smallPoolSpVec4.push_back(ptr);
	else
		delete ptr;
}
void DestroyVec3(const spVec3 ptr)
{
	CHECK_PARAM_PTR(ptr, "ptr");
	if (smallPoolSpVec3.size() < (size_t)initStruct.smallPoolSize)
		smallPoolSpVec3.push_back(ptr);
	else
		delete ptr;
}
void DestroyTransform(const spTransform ptr)
{
	CHECK_PARAM_PTR(ptr, "ptr");
	if (smallPoolSpTransform.size() < (size_t)initStruct.smallPoolSize)
		smallPoolSpTransform.push_back(ptr);
	else
		delete ptr;
}

void CommonDelete(const void* ptr)
{
	CHECK_PARAM_PTR(ptr, "ptr");
	delete ptr;
}
hkVector4 Vec3TohkVec4(const spVec3 vec3) {
	CHECK_PARAM_PTR_RET(vec3, "vec3", hkVector4());
	return hkVector4(vec3->x, vec3->y, vec3->z);  
}
hkVector4 Vec4TohkVec4(const spVec4 vec4) {
	CHECK_PARAM_PTR_RET(vec4, "vec4", hkVector4());
	return hkVector4(vec4->x, vec4->y, vec4->z, vec4->w); 
}
hkQuaternion Vec4TohkQuaternion(const spVec4 vec4) { 
	CHECK_PARAM_PTR_RET(vec4, "vec4", hkQuaternion());
	return hkQuaternion(vec4->x, vec4->y, vec4->z, vec4->w); 
}
hkQsTransform TransformTohkQsTransform(const spTransform transform) {
	CHECK_PARAM_PTR_RET(transform, "transform", hkQsTransform());
	return hkQsTransform(
		hkVector4(transform->positionX, transform->positionY, transform->positionZ),
		hkQuaternion(transform->rotationX, transform->rotationY, transform->rotationZ, transform->rotationW),
		hkVector4(transform->scaleX, transform->scaleY, transform->scaleZ)
	); 
}

void InitSmallPool() {
	for (int i = 0; i < initStruct.smallPoolSize && i < 512; i++) {
		smallPoolSpTransform.push_back(new sTransform());
		smallPoolSpVec3.push_back(new sVec3());
		smallPoolSpVec4.push_back(new sVec4());
	}
}
void InitFunctions()
{
	int i = 0;
	apiArray = new void*[256];
	apiArray[i++] = CommonDelete;
	apiArray[i++] = CreateVec3;
	apiArray[i++] = CreateTransform;
	apiArray[i++] = CreateVec4;
	apiArray[i++] = DestroyVec4;
	apiArray[i++] = DestroyVec3;
	apiArray[i++] = DestroyTransform;
	apiArray[i++] = CreatePhysicsWorld;
	apiArray[i++] = DestroyPhysicsWorld;
	apiArray[i++] = StepPhysicsWorld;
	apiArray[i++] = SetPhysicsWorldGravity;
	apiArray[i++] = ReadPhysicsWorldBodys;
	apiArray[i++] = CreateRigdBody;
	apiArray[i++] = ActiveRigdBody;
	apiArray[i++] = DeactiveRigdBody;
	apiArray[i++] = SetRigdBodyMass;
	apiArray[i++] = SetRigdBodyFriction;
	apiArray[i++] = SetRigdBodyRestitution;
	apiArray[i++] = SetRigdBodyCenterOfMass;
	apiArray[i++] = SetRigdBodyPosition;
	apiArray[i++] = SetRigdBodyPositionAndRotation;
	apiArray[i++] = SetRigdBodyAngularDamping;
	apiArray[i++] = SetRigdBodyLinearDampin;
	apiArray[i++] = SetRigdBodyMotionType;
	apiArray[i++] = SetRigdBodyGravityFactor;
	apiArray[i++] = GetConvexHullResultTriangles;
	apiArray[i++] = GetConvexHullResultVertices;
	apiArray[i++] = Build3DPointsConvexHull;
	apiArray[i++] = Build3DFromPlaneConvexHull;
	apiArray[i++] = DestroyRigdBody;
	apiArray[i++] = ComputeShapeVolumeMassProperties;
	apiArray[i++] = ComputeBoxSurfaceMassProperties;
	apiArray[i++] = ComputeBoxVolumeMassProperties;
	apiArray[i++] = ComputeCapsuleVolumeMassProperties;
	apiArray[i++] = ComputeCylinderVolumeMassProperties;
	apiArray[i++] = ComputeSphereVolumeMassProperties;
	apiArray[i++] = ComputeSphereSurfaceMassProperties;
	apiArray[i++] = ComputeTriangleSurfaceMassProperties;
	apiArray[i++] = CreateBoxShape;
	apiArray[i++] = CreateSphereShape;
	apiArray[i++] = CreateCapsuleShape;
	apiArray[i++] = CreateCylindeShape;
	apiArray[i++] = CreateTriangleShape;
	apiArray[i++] = CreateConvexVerticesShape;
	apiArray[i++] = CreateConvexVerticesShapeByConvexHullResult;
	apiArray[i++] = CreateConvexTranslateShape;
	apiArray[i++] = CreateConvexTransformShape;
	apiArray[i++] = CreateListShape;
	apiArray[i++] = CreateStaticCompoundShape;
	apiArray[i++] = StaticCompoundShapeSetInstanceEnabled;
	apiArray[i++] = StaticCompoundShapeIsInstanceEnabled;
	apiArray[i++] = StaticCompoundShapeEnableAllInstancesAndShapeKeys;
	apiArray[i++] = DestroyShape;
	apiArray[i++] = TestAssert;
}

void DestroyFunctions() {
	if (apiArray) {
		delete[] apiArray;
		apiArray = nullptr;
	}
}
void DestroySmallPool() {
	for (auto it = smallPoolSpTransform.begin(); it != smallPoolSpTransform.end(); it++) 
		delete* it;
	for (auto it = smallPoolSpVec3.begin(); it != smallPoolSpVec3.end(); it++)
		delete* it;
	for (auto it = smallPoolSpVec4.begin(); it != smallPoolSpVec4.end(); it++)
		delete* it;
	smallPoolSpTransform.clear();
	smallPoolSpVec4.clear();
	smallPoolSpVec3.clear();
}
