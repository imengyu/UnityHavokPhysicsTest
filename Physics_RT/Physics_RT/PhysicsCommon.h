#pragma once
#include "PhysicsHeader.h"
#include <exception>

typedef void(__cdecl* fnErrorCallback)(const char* msg);

struct sInitStruct {
	fnErrorCallback errCallback;
	bool mulithread;
	int smallPoolSize;
};

#define CHECK_PARAM_PTR(param) if(!param) { throw std::exception(#param ## " is nullptr!"); }

void CallbackWithError(char*msg, ...);
void APIErrorReport(const char* msg, void* userArgGivenToInit);
void APICatchHandler(std::exception& e);

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

#define TRY_BEGIN try {
#define TRY_END(ret) } catch (std::exception &e) { APICatchHandler(e); return ret; }
#define TRY_END_NORET } catch (std::exception &e) { APICatchHandler(e); }

#define M_PI       3.1415926535f   // pi