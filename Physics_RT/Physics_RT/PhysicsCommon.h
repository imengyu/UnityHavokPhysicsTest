#pragma once
#include "PhysicsHeader.h"

typedef void(__cdecl* fnErrorCallback)(const char* msg);

struct sInitStruct {
	fnErrorCallback errCallback;
	bool mulithread;
	int smallPoolSize;
};

void CallbackWithError(char*msg, ...);

typedef struct sVec3 {
	float x;
	float y;
	float z;
}sVec3, * spVec3;
typedef struct sVec4 {
	float x;
	float y;
	float z;
	float w;
}sVec4, * spVec4;
typedef struct sTransform {
	float positionX;
	float positionY;
	float positionZ;
	float scaleX;
	float scaleY;
	float scaleZ;
	float rotationX;
	float rotationY;
	float rotationZ;
	float rotationW;
}sTransform, * spTransform;

typedef spVec3(__cdecl* fnCreateVec3)(float x, float y, float z);
typedef spVec4(__cdecl* fnCreateVec4)(float x, float y, float z, float w);
typedef void(__cdecl* fnCommonDelete)(const void* ptr);
typedef spTransform(__cdecl* fnCreateTransform)(float px, float py, float pz, float rx, float ry, float rz, float rw, float sx, float sy, float sz);
typedef void(__cdecl* fnDestroyVec4)(const spVec4 ptr);
typedef void(__cdecl* fnDestroyVec3)(const spVec3 ptr);
typedef void(__cdecl* fnDestroyTransform)(const spTransform ptr);

void DestroyVec4(const spVec4 ptr);
void DestroyVec3(const spVec3 ptr);
void DestroyTransform(const spTransform ptr);
spTransform CreateTransform(float px, float py, float pz, float rx, float ry, float rz, float rw, float sx, float sy, float sz);
spVec3 CreateVec3(float x, float y, float z);
spVec4 CreateVec4(float x, float y, float z, float w);
hkVector4 Vec3TohkVec4(const spVec3 vec3);
hkVector4 Vec4TohkVec4(const spVec4 vec4);
hkQuaternion Vec4TohkQuaternion(const spVec4 vec4);
hkQsTransform TransformTohkQsTransform(const spTransform transform);
void CommonDelete(const void* ptr);