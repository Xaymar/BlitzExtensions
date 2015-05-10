#pragma once
#include "dllmain.h"
#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
	#include <math.h>
	#undef _USE_MATH_DEFINES
#endif

struct Vector3 {
	union {
		float X;
		char Xc[4];
	};
	union {
		float Y;
		char Yc[4];
	};
	union {
		float Z;
		char Zc[4];
	};

	void set(const float &o);
	void set(const float &x, const float &y, const float &z);
	void set(const Vector3 &o);

	void add(const float &o);
	void add(const float &x, const float &y, const float &z);
	void add(const Vector3 &o);

	void sub(const float &o);
	void sub(const float &x, const float &y, const float &z);
	void sub(const Vector3 &o);

	void mul(const float &o);
	void mul(const float &x, const float &y, const float &z);
	void mul(const Vector3 &o);

	void div(const float &o);
	void div(const float &x, const float &y, const float &z);
	void div(const Vector3 &o);

	float length();
	float distance(const float &x, const float &y, const float &z);
	float distance(const Vector3 &o);

	float dot(const float &x, const float &y, const float &z);
	float dot(const Vector3 &o);
	Vector3 cross(const float &x, const float &y, const float &z);
	Vector3 cross(const Vector3 &o);
	void normalize();

	void rotate(float &pitch, float &yaw, float &roll);
	void rotateAround(const float &x, const float &y, const float &z, float &pitch, float &yaw, float &roll);
	void rotateAround(Vector3 &o, float &pitch, float &yaw, float &roll);
	float deltaPitch();
	float deltaPitch(const float &x, const float &y, const float &z);
	float deltaPitch(Vector3 &o);
	float deltaYaw();
	float deltaYaw(const float &x, const float &y, const float &z);
	float deltaYaw(Vector3 &o);

	char* serialize();
	void deserialize(char* o);
};