#include "stdafx.h"
#include "Utils.h"
#include <math.h>

EulerAngles ToEulerAngles(const hkQuaternion& q) {
	EulerAngles angles;

	float x = q.getComponent<0>();
	float y = q.getComponent<1>();
	float z = q.getComponent<2>();
	float w = q.getComponent<3>();

	// roll (x-axis rotation)
	float sinr_cosp = 2 * (w * x + y * z);
	float cosr_cosp = 1 - 2 * (x * x + y * y);
	angles.roll = hkMath::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	float sinp = 2 * (w * y - z * x);
	if (hkMath::abs(sinp) >= 1)
		angles.pitch = _copysignf(M_PI / 2.0f, sinp); // use 90 degrees if out of range
	else
		angles.pitch = hkMath::asin(sinp);

	// yaw (z-axis rotation)
	float siny_cosp = 2 * (w * z + x * y);
	float cosy_cosp = 1 - 2 * (y * y + z * z);
	angles.yaw = hkMath::atan2(siny_cosp, cosy_cosp);

	return angles;
}