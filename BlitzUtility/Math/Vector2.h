#pragma once
#include "dllmain.h"
#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
	#include <math.h>
	#undef _USE_MATH_DEFINES
#endif

struct Vector2 {
	union {
		float X;
		char Xc[4];
	};
	union {
		float Y;
		char Yc[4];
	};

	void set(const float &o);
	void set(const float &x, const float &y);
	void set(const Vector2 &o);

	void add(const float &o);
	void add(const float &x, const float &y);
	void add(const Vector2 &o);

	void sub(const float &o);
	void sub(const float &x, const float &y);
	void sub(const Vector2 &o);

	void mul(const float &o);
	void mul(const float &x, const float &y);
	void mul(const Vector2 &o);

	void div(const float &o);
	void div(const float &x, const float &y);
	void div(const Vector2 &o);

	float length();
	float distance(const float &x, const float &y);
	float distance(const Vector2 &o);

	float dot(const float &x, const float &y);
	float dot(const Vector2 &o);
	void normalize();

	void rotate(const float rotation);
	void rotateAround(const float &x, const float &y, const float &rotation);
	void rotateAround(const Vector2 &o, const float &rotation);
	float deltaRotation();
	float deltaRotation(const float &x, const float &y);
	float deltaRotation(const Vector2 &o);

	char* serialize();
	void deserialize(char* o);
};

