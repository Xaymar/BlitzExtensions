#pragma once
#include "Matrix3.h"


void Matrix3::set(Matrix3 &M)
{
	if (this != &M) {
		this->X.set(M.X);
		this->Y.set(M.Y);
		this->Z.set(M.Z);
	}
}

void Matrix3::set(Vector3 &X, Vector3 &Y, Vector3 &Z)
{
	this->X.set(X);
	this->Y.set(Y);
	this->Z.set(Z);
}

void Matrix3::set(float &XX, float &XY, float &XZ, float &YX, float &YY, float &YZ, float &ZX, float &ZY, float &ZZ)
{
	this->X.set(XX, XY, XZ);
	this->Y.set(YX, YY, YZ);
	this->Z.set(ZX, ZY, ZZ);
}

void Matrix3::rotate(float &pitch, float &yaw, float &roll)
{
	this->X.mul(cos(yaw) * cos(roll), -sin(roll), sin(yaw));
	this->Y.mul(sin(roll), cos(pitch) * cos(roll), -sin(pitch));
	this->Z.mul(-sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
}

void Matrix3::angles(float &pitch, float &yaw, float &roll)
{
	// ToDo
}

void Matrix3::transpose()
{
	Matrix3 temp;

	temp.set(*this);
	this->X.set(temp.X.X, temp.Y.X, temp.Z.X);
	this->Y.set(temp.X.Y, temp.Y.Y, temp.Z.Y);
	this->Z.set(temp.X.Z, temp.Y.Z, temp.Z.Z);
}
