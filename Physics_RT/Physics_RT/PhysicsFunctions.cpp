#include "PhysicsFunctions.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <list>

extern sApiStruct funStruct;
extern sInitStruct initStruct;

void CallbackWithError(char* msg, ...)
{
	if (initStruct.errCallback) {
		va_list ap;
		va_start(ap, msg);

		size_t num_of_chars = _vscprintf(msg, ap);
		char* buffer = new char[num_of_chars];
		vsprintf_s(buffer, num_of_chars, msg, ap);
		initStruct.errCallback(buffer);
		delete buffer;

		va_end(ap);
	}
}

std::list<spTransform> smallPoolSpTransform;
std::list<spVec3> smallPoolSpVec3;
std::list<spVec4> smallPoolSpVec4;

spTransform CreateTransform(float px, float py, float pz, float rx, float ry, float rz, float rw, float sx, float sy, float sz)
{
	spTransform v = nullptr;
	if (smallPoolSpTransform.size() > 0) {
		spTransform v = smallPoolSpTransform.front();
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
		spVec3 v = smallPoolSpVec3.front();
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
		spVec4 v = smallPoolSpVec4.front();
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
	if (smallPoolSpVec4.size() < initStruct.smallPoolSize) 
		smallPoolSpVec4.push_back(ptr);
	else
		delete ptr;
}
void DestroyVec3(const spVec3 ptr)
{
	if (smallPoolSpVec3.size() < initStruct.smallPoolSize)
		smallPoolSpVec3.push_back(ptr);
	else
		delete ptr;
}
void DestroyTransform(const spTransform ptr)
{
	if (smallPoolSpTransform.size() < initStruct.smallPoolSize)
		smallPoolSpTransform.push_back(ptr);
	else
		delete ptr;
}

void CommonDelete(const void* ptr)
{
	delete ptr;
}
hkVector4 Vec3TohkVec4(const spVec3 vec3) { return hkVector4(vec3->x, vec3->y, vec3->z);  }
hkVector4 Vec4TohkVec4(const spVec4 vec4) { return hkVector4(vec4->x, vec4->y, vec4->z, vec4->w); }
hkQuaternion Vec4TohkQuaternion(const spVec4 vec4) { return hkQuaternion(vec4->x, vec4->y, vec4->z, vec4->w); }
hkQsTransform TransformTohkQsTransform(const spTransform transform) {
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
	funStruct.CommonDelete = CommonDelete;

	funStruct.CreateVec3 = CreateVec3;
	funStruct.CreateTransform = CreateTransform;
	funStruct.CreateVec4 = CreateVec4;
	funStruct.DestroyVec4 = DestroyVec4;
	funStruct.DestroyVec3 = DestroyVec3;
	funStruct.DestroyTransform = DestroyTransform;

	funStruct.CreatePhysicsWorld = CreatePhysicsWorld;
	funStruct.DestroyPhysicsWorld = DestroyPhysicsWorld;
	funStruct.StepPhysicsWorld = StepPhysicsWorld;
	funStruct.SetPhysicsWorldGravity = SetPhysicsWorldGravity;
	funStruct.ReadPhysicsWorldBodys = ReadPhysicsWorldBodys;

	funStruct.CreateRigdBody = CreateRigdBody;
	funStruct.ActiveRigdBody = ActiveRigdBody;
	funStruct.DeactiveRigdBody = DeactiveRigdBody;
	funStruct.SetRigdBodyMass = SetRigdBodyMass;
	funStruct.SetRigdBodyFriction = SetRigdBodyFriction;
	funStruct.SetRigdBodyRestitution = SetRigdBodyRestitution;
	funStruct.SetRigdBodyCenterOfMass = SetRigdBodyCenterOfMass;
	funStruct.SetRigdBodyPosition = SetRigdBodyPosition;
	funStruct.SetRigdBodyPositionAndRotation = SetRigdBodyPositionAndRotation;
	funStruct.SetRigdBodyLinearDampin = SetRigdBodyLinearDampin;
	funStruct.SetRigdBodyAngularDamping = SetRigdBodyAngularDamping;
	funStruct.SetRigdBodyMotionType = SetRigdBodyMotionType;
	funStruct.DestroyRigdBody = DestroyRigdBody;

	funStruct.ComputeShapeVolumeMassProperties = ComputeShapeVolumeMassProperties;
	funStruct.ComputeBoxSurfaceMassProperties = ComputeBoxSurfaceMassProperties;
	funStruct.ComputeBoxVolumeMassProperties = ComputeBoxVolumeMassProperties;
	funStruct.ComputeCapsuleVolumeMassProperties = ComputeCapsuleVolumeMassProperties;
	funStruct.ComputeCylinderVolumeMassProperties = ComputeCylinderVolumeMassProperties;
	funStruct.ComputeSphereVolumeMassProperties = ComputeSphereVolumeMassProperties;
	funStruct.ComputeSphereSurfaceMassProperties = ComputeSphereSurfaceMassProperties;
	funStruct.ComputeTriangleSurfaceMassProperties = ComputeTriangleSurfaceMassProperties;

	funStruct.CreateBoxShape = CreateBoxShape;
	funStruct.CreateSphereShape = CreateSphereShape;
	funStruct.CreateCapsuleShape = CreateCapsuleShape;
	funStruct.CreateCylindeShape = CreateCylindeShape;
	funStruct.CreateTriangleShape = CreateTriangleShape;
	funStruct.CreateConvexVerticesShape = CreateConvexVerticesShape;
	funStruct.CreateConvexTranslateShape = CreateConvexTranslateShape;
	funStruct.CreateConvexTransformShape = CreateConvexTransformShape;
	funStruct.CreateListShape = CreateListShape;
	funStruct.CreateStaticCompoundShape = CreateStaticCompoundShape;
	funStruct.StaticCompoundShapeSetInstanceEnabled = StaticCompoundShapeSetInstanceEnabled;
	funStruct.StaticCompoundShapeIsInstanceEnabled = StaticCompoundShapeIsInstanceEnabled;
	funStruct.StaticCompoundShapeEnableAllInstancesAndShapeKeys = StaticCompoundShapeEnableAllInstancesAndShapeKeys;
	funStruct.DestroyShape = DestroyShape;
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
