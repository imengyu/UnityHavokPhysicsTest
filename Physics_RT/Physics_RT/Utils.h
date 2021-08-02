#pragma once
#include "stdafx.h"
#include "PhysicsHeader.h"
#include "PhysicsFunctions.h"

struct EulerAngles {
	float roll, pitch, yaw;
};

EulerAngles ToEulerAngles(const hkQuaternion& q);
