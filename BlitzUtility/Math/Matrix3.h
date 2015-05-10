#pragma once
#include <math.h>
#include "dllmain.h"
#include "Vector3.h"

struct Matrix3 {
	Vector3 X, Y, Z;

	void set(Matrix3 &M);
	void set(Vector3 &X, Vector3 &Y, Vector3 &Z);
	void set(float &XX, float &XY, float &XZ, float &YX, float &YY, float &YZ, float &ZX, float &ZY, float &ZZ);
	
	void rotate(float &pitch, float &yaw, float &roll);
	void angles(float &pitch, float &yaw, float &roll);

	void transpose();
};

