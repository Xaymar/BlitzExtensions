#pragma once
#include "Vector2.h"

void Vector2::set(const float &o)
{
	this->X = o;
	this->Y = o;
}
void Vector2::set(const float &x, const float &y)
{
	this->X = x;
	this->Y = y;
}
void Vector2::set(const Vector2 &o)
{
	if (this != &o) {
		this->X = o.X;
		this->Y = o.Y;
	}
}

void Vector2::add(const float &o)
{
	this->X += o;
	this->Y += o;
}
void Vector2::add(const float &x, const float &y)
{
	this->X += x;
	this->Y += y;
}
void Vector2::add(const Vector2 &o)
{
	this->X += o.X;
	this->Y += o.Y;
}

void Vector2::sub(const float &o)
{
	this->X -= o;
	this->Y -= o;
}
void Vector2::sub(const float &x, const float &y)
{
	this->X -= x;
	this->Y -= y;
}
void Vector2::sub(const Vector2 &o)
{
	this->X -= o.X;
	this->Y -= o.Y;
}

void Vector2::mul(const float &o)
{
	this->X *= o;
	this->Y *= o;
}
void Vector2::mul(const float &x, const float &y)
{
	this->X *= x;
	this->Y *= y;
}
void Vector2::mul(const Vector2 &o)
{
	this->X *= o.X;
	this->Y *= o.Y;
}

void Vector2::div(const float &o)
{
	this->X /= o;
	this->Y /= o;
}
void Vector2::div(const float &x, const float &y)
{
	this->X /= x;
	this->Y /= y;
}
void Vector2::div(const Vector2 &o)
{
	this->X /= o.X;
	this->Y /= o.Y;
}

float Vector2::length()
{
	return (float)sqrt((this->X * this->X) + (this->Y * this->Y));
}
float Vector2::distance(const float &x, const float &y)
{
	float X = this->X - x;
	float Y = this->Y - y;
	return (float)sqrt((X * X) + (Y * Y));
}
float Vector2::distance(const Vector2 &o)
{
	float X = this->X - o.X;
	float Y = this->Y - o.Y;
	return (float)sqrt((X * X) + (Y * Y));
}

float Vector2::dot(const float &x, const float &y)
{
	return (this->X * x) + (this->Y * y);
}
float Vector2::dot(const Vector2 &o)
{
	return (this->X * o.X) + (this->Y * o.Y);
}
void Vector2::normalize()
{
	this->div(this->length());
}

void Vector2::rotate(const float rotation)
{
	float mX = cos(rotation);
	float mY = sin(rotation);

	float X = this->X * mX + this->Y * mY; this->X = X;
	float Y = this->X * mY + this->X * mX; this->Y = Y;
}
void Vector2::rotateAround(const float &x, const float &y, const float &rotation)
{
	this->sub(x, y);
	this->rotate(rotation);
	this->add(x, y);
}
void Vector2::rotateAround(const Vector2 &o, const float &rotation)
{
	this->sub(o);
	this->rotate(rotation);
	this->add(o);
}

float Vector2::deltaRotation() {
	return (float)(atan2(this->Y, this->X) * (180.0 / M_PI));
}
float Vector2::deltaRotation(const float &x, const float &y)
{
	return (float)(atan2(this->Y - y, this->X - x) * (180.0 / M_PI));
}
float Vector2::deltaRotation(const Vector2 &o)
{
	return (float)(atan2(this->Y - o.Y, this->X - o.X) * (180.0 / M_PI));
}

char* Vector2::serialize()
{
	char* data = new char[9];

	memcpy(data, this->Xc, 4);
	memcpy(data + 4, this->Yc, 4);
	data[8] = 0;

	return data;
}
void Vector2::deserialize(char* o)
{
	memcpy(o, this->Xc, 4);
	memcpy(o + 4, this->Yc, 4);
}

/* ------------------------- Exported Functionality ------------------------- */
DLL_EXPORT void Vector2_Set(Vector2* a, float o) {
	a->set(o);
}
DLL_EXPORT void Vector2_SetP(Vector2* a, float x, float y) {
	a->set(x, y);
}
DLL_EXPORT void Vector2_SetV(Vector2* a, Vector2* b) {
	a->set(*b);
}

DLL_EXPORT void Vector2_Add(Vector2* a, float o) {
	a->add(o);
}
DLL_EXPORT void Vector2_AddP(Vector2* a, float x, float y) {
	a->add(x, y);
}
DLL_EXPORT void Vector2_AddV(Vector2* a, Vector2* b) {
	a->add(*b);
}

DLL_EXPORT void Vector2_Sub(Vector2* a, float o) {
	a->sub(o);
}
DLL_EXPORT void Vector2_SubP(Vector2* a, float x, float y) {
	a->sub(x, y);
}
DLL_EXPORT void Vector2_SubV(Vector2* a, Vector2* b) {
	a->sub(*b);
}

DLL_EXPORT void Vector2_Mul(Vector2* a, float o) {
	a->mul(o);
}
DLL_EXPORT void Vector2_MulP(Vector2* a, float x, float y) {
	a->mul(x, y);
}
DLL_EXPORT void Vector2_MulV(Vector2* a, Vector2* b) {
	a->mul(*b);
}

DLL_EXPORT void Vector2_Div(Vector2* a, float o) {
	a->div(o);
}
DLL_EXPORT void Vector2_DivP(Vector2* a, float x, float y) {
	a->div(x, y);
}
DLL_EXPORT void Vector2_DivV(Vector2* a, Vector2* b) {
	a->div(*b);
}

DLL_EXPORT float Vector2_Length(Vector2* a) {
	return (float)a->length();
}
DLL_EXPORT float Vector2_DistanceP(Vector2* a, float x, float y) {
	return (float)a->distance(x, y);
}
DLL_EXPORT float Vector2_DistanceV(Vector2* a, Vector2* b) {
	return (float)a->distance(*b);
}

DLL_EXPORT float Vector2_DotP(Vector2* a, float x, float y) {
	return (float)a->dot(x, y);
}
DLL_EXPORT float Vector2_DotV(Vector2* a, Vector2* b) {
	return (float)a->dot(*b);
}
DLL_EXPORT void Vector2_Normalize(Vector2* a) {
	a->normalize();
}

DLL_EXPORT void Vector2_Rotate(Vector2* a, float rotation) {
	a->rotate(rotation);
}
DLL_EXPORT void Vector2_RotateAroundP(Vector2* a, float x, float y, float rotation) {
	a->rotateAround(x, y, rotation);
}
DLL_EXPORT void Vector2_RotateAroundV(Vector2* a, Vector2* b, float rotation) {
	a->rotateAround(*b, rotation);
}

DLL_EXPORT float Vector2_DeltaRotation(Vector2* a) {
	return (float)a->deltaRotation();
}
DLL_EXPORT float Vector2_DeltaRotationP(Vector2* a, float x, float y) {
	return (float)a->deltaRotation(x, y);
}
DLL_EXPORT float Vector2_DeltaRotationV(Vector2* a, Vector2* b) {
	return (float)a->deltaRotation(*b);
}

DLL_EXPORT char* Vector2_Serialize(Vector2* a) {
	return a->serialize();
}
DLL_EXPORT void Vector2_Deserialize(Vector2* a, char* o) {
	a->deserialize(o);
}
