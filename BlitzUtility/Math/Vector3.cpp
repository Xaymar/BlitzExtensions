#pragma once
#include "Vector3.h"

void Vector3::set(const float &o)
{
	this->X = o;
	this->Y = o;
	this->Z = o;
}
void Vector3::set(const float &x, const float &y, const float &z)
{
	this->X = x;
	this->Y = y;
	this->Z = z;
}
void Vector3::set(const Vector3 &o)
{
	if (this != &o) {
		this->X = o.X;
		this->Y = o.Y;
		this->Z = o.Z;
	}
}

void Vector3::add(const float &o)
{
	this->X += o;
	this->Y += o;
	this->Z += o;
}
void Vector3::add(const float &x, const float &y, const float &z)
{
	this->X += x;
	this->Y += y;
	this->Z += z;
}
void Vector3::add(const Vector3 &o)
{
	this->X += o.X;
	this->Y += o.Y;
	this->Z += o.Z;
}

void Vector3::sub(const float &o)
{
	this->X -= o;
	this->Y -= o;
	this->Z -= o;
}
void Vector3::sub(const float &x, const float &y, const float &z)
{
	this->X -= x;
	this->Y -= y;
	this->Z -= z;
}
void Vector3::sub(const Vector3 &o)
{
	this->X -= o.X;
	this->Y -= o.Y;
	this->Z -= o.Z;
}

void Vector3::mul(const float &o)
{
	this->X *= o;
	this->Y *= o;
	this->Z *= o;
}
void Vector3::mul(const float &x, const float &y, const float &z)
{
	this->X *= x;
	this->Y *= y;
	this->Z *= z;
}
void Vector3::mul(const Vector3 &o)
{
	this->X *= o.X;
	this->Y *= o.Y;
	this->Z *= o.Z;
}

void Vector3::div(const float &o)
{
	this->X /= o;
	this->Y /= o;
	this->Z /= o;
}
void Vector3::div(const float &x, const float &y, const float &z)
{
	this->X /= x;
	this->Y /= y;
	this->Z /= z;
}
void Vector3::div(const Vector3 &o)
{
	this->X /= o.X;
	this->Y /= o.Y;
	this->Z /= o.Z;
}

float Vector3::length()
{
	return sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
}
float Vector3::distance(const float &x, const float &y, const float &z)
{
	float X = (this->X - x);
	float Y = (this->Y - y);
	float Z = (this->Z - z);
	return sqrt(X * X + Y * Y + Z * Z);
}
float Vector3::distance(const Vector3 &o)
{
	float X = (this->X - o.X);
	float Y = (this->Y - o.Y);
	float Z = (this->Z - o.Z);
	return sqrt(X * X + Y * Y + Z * Z);
}

float Vector3::dot(const float &x, const float &y, const float &z)
{
	return (this->X * x) + (this->Y * y) + (this->Z * z);
}
float Vector3::dot(const Vector3 &o)
{
	return (this->X * o.X) + (this->Y * o.Y) + (this->Z * o.Z);
}
Vector3 Vector3::cross(const float &x, const float &y, const float &z)
{
	Vector3* data = new Vector3();
	data->X = (this->Y * z) - (this->Z * y);
	data->Y = (this->Z * x) - (this->X * z);
	data->Z = (this->X * y) - (this->Y * x);
	return *data;
}
Vector3 Vector3::cross(const Vector3 &o)
{
	Vector3* data = new Vector3();
	data->X = (this->Y * o.Z) - (this->Z * o.Y);
	data->Y = (this->Z * o.X) - (this->X * o.Z);
	data->Z = (this->X * o.Y) - (this->Y * o.X);
	return *data;
}
void Vector3::normalize()
{
	this->div(this->length());
}

void Vector3::rotate(float &pitch, float &yaw, float &roll)
{
	float** matrix = new float*[3];
	matrix[0] = new float[3];					matrix[1] = new float[3];					matrix[2] = new float[3];
	matrix[0][0] = cos(yaw) * cos(roll);		matrix[0][1] = -sin(roll);					matrix[0][2] = sin(yaw);
	matrix[1][0] = sin(roll);					matrix[1][1] = cos(pitch) * cos(roll);		matrix[1][2] = -sin(pitch);
	matrix[2][0] = -sin(yaw);					matrix[2][1] = sin(pitch);					matrix[2][2] = cos(pitch) * cos(yaw);

	float X = (this->X * matrix[0][0]) + (this->Y * matrix[0][1]) + (this->Z * matrix[0][2]);
	float Y = (this->X * matrix[1][0]) + (this->Y * matrix[1][1]) + (this->Z * matrix[1][2]);
	float Z = (this->X * matrix[2][0]) + (this->Y * matrix[2][1]) + (this->Z * matrix[2][2]);
	this->X = X; this->Y = Y; this->Z = Z;
}
void Vector3::rotateAround(const float &x, const float &y, const float &z, float &pitch, float &yaw, float &roll)
{
	this->sub(x, y, z);
	this->rotate(pitch, yaw, roll);
	this->add(x, y, z);
}
void Vector3::rotateAround(Vector3 &o, float &pitch, float &yaw, float &roll)
{
	this->sub(o);
	this->rotate(pitch, yaw, roll);
	this->add(o);
}
float Vector3::deltaPitch() {
	return (float)(atan(this->X / -this->Y) * (180.0 / M_PI));
}
float Vector3::deltaPitch(const float &x, const float &y, const float &z)
{
	return (float)(atan((this->X - x) / (-(this->Y - y))) * (180.0 / M_PI));
}
float Vector3::deltaPitch(Vector3 &o)
{
	return (float)(atan((this->X - o.X) / (-(this->Y - o.Y))) * (180.0 / M_PI));
}
float Vector3::deltaYaw() {
	return (float)(atan(sqrt((this->X * this->X) + (this->Y * this->Y)) / this->Z) * (180.0 / M_PI));
}
float Vector3::deltaYaw(const float &x, const float &y, const float &z)
{
	float X = (this->X - x);
	float Y = (this->Y - y);
	return (float)(atan(sqrt((X * X) + (Y * Y)) / (this->Z - z)) * (180.0 / M_PI));
}
float Vector3::deltaYaw(Vector3 &o)
{
	float X = (this->X - o.X);
	float Y = (this->Y - o.Y);
	return (float)(atan(sqrt((X * X) + (Y * Y)) / (this->Z - o.Z)) * (180.0 / M_PI));
}

char* Vector3::serialize()
{
	char* data = new char[13];

	memcpy(data, this->Xc, 4);
	memcpy(data + 4, this->Yc, 4);
	memcpy(data + 8, this->Zc, 4);
	data[12] = 0;

	return data;
}
void Vector3::deserialize(char* o)
{
	memcpy(o, this->Xc, 4);
	memcpy(o + 4, this->Yc, 4);
	memcpy(o + 8, this->Zc, 4);
}

/* ------------------------- Exported Functionality ------------------------- */
DLL_EXPORT void Vector3_Set(Vector3* a, float o) {
	a->set(o);
}
DLL_EXPORT void Vector3_SetP(Vector3* a, float x, float y, float z) {
	a->set(x, y, z);
}
DLL_EXPORT void Vector3_SetV(Vector3* a, Vector3* b) {
	a->set(*b);
}

DLL_EXPORT void Vector3_Add(Vector3* a, float o) {
	a->add(o);
}
DLL_EXPORT void Vector3_AddP(Vector3* a, float x, float y, float z) {
	a->add(x, y, z);
}
DLL_EXPORT void Vector3_AddV(Vector3* a, Vector3* b) {
	a->add(*b);
}

DLL_EXPORT void Vector3_Sub(Vector3* a, float o) {
	a->sub(o);
}
DLL_EXPORT void Vector3_SubP(Vector3* a, float x, float y, float z) {
	a->sub(x, y, z);
}
DLL_EXPORT void Vector3_SubV(Vector3* a, Vector3* b) {
	a->sub(*b);
}

DLL_EXPORT void Vector3_Mul(Vector3* a, float o) {
	a->mul(o);
}
DLL_EXPORT void Vector3_MulP(Vector3* a, float x, float y, float z) {
	a->mul(x, y, z);
}
DLL_EXPORT void Vector3_MulV(Vector3* a, Vector3* b) {
	a->mul(*b);
}

DLL_EXPORT void Vector3_Div(Vector3* a, float o) {
	a->div(o);
}
DLL_EXPORT void Vector3_DivP(Vector3* a, float x, float y, float z) {
	a->div(x, y, z);
}
DLL_EXPORT void Vector3_DivV(Vector3* a, Vector3* b) {
	a->div(*b);
}

DLL_EXPORT float Vector3_Length(Vector3* a) {
	return (float)a->length();
}
DLL_EXPORT float Vector3_DistanceP(Vector3* a, float x, float y, float z) {
	return (float)a->distance(x, y, z);
}
DLL_EXPORT float Vector3_DistanceV(Vector3* a, Vector3* b) {
	return (float)a->distance(*b);
}

DLL_EXPORT float Vector3_DotP(Vector3* a, float x, float y, float z) {
	return (float)a->dot(x, y, z);
}
DLL_EXPORT float Vector3_DotV(Vector3* a, Vector3* b) {
	return (float)a->dot(*b);
}
DLL_EXPORT void Vector3_CrossP(Vector3* a, float x, float y, float z, Vector3* out) {
	Vector3 temp = a->cross(x, y, z);
	*out = temp;
}
DLL_EXPORT void Vector3_CrossV(Vector3* a, Vector3* b, Vector3* out) {
	Vector3 temp = a->cross(*b);
	*out = temp;
}
DLL_EXPORT void Vector3_Normalize(Vector3* a) {
	a->normalize();
}

DLL_EXPORT void Vector3_Rotate(Vector3* a, float pitch, float yaw, float roll) {
	a->rotate(pitch, yaw, roll);
}
DLL_EXPORT void Vector3_RotateAroundP(Vector3* a, float x, float y, float z, float pitch, float yaw, float roll) {
	a->rotateAround(x, y, z, pitch, yaw, roll);
}
DLL_EXPORT void Vector3_RotateAroundV(Vector3* a, Vector3* b, float pitch, float yaw, float roll) {
	a->rotateAround(*b, pitch, yaw, roll);
}

DLL_EXPORT float Vector3_DeltaPitchP(Vector3* a, float x, float y, float z) {
	return (float)a->deltaPitch(x, y, z);
}
DLL_EXPORT float Vector3_DeltaPitchV(Vector3* a, Vector3* b) {
	return (float)a->deltaPitch(*b);
}
DLL_EXPORT float Vector3_DeltaYawP(Vector3* a, float x, float y, float z) {
	return (float)a->deltaYaw(x, y, z);
}
DLL_EXPORT float Vector3_DeltaYawV(Vector3* a, Vector3* b) {
	return (float)a->deltaYaw(*b);
}

DLL_EXPORT char* Vector3_Serialize(Vector3* a) {
	return a->serialize();
}
DLL_EXPORT void Vector3_Deserialize(Vector3* a, char* s) {
	a->deserialize(s);
}