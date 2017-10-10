#pragma once
#include "stdafx.h"
#include "Object.h"


Object::Object(float objectStatus, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha)
{
	Initialize(objectStatus, objectX, objectY, objectZ, objectSize, red, green, black, alpha);
}

Object::~Object() {
};

void Object::Initialize(float objectStatus, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha)
{
	status = objectStatus;
	x = objectX;
	y = objectY;
	z = objectZ;
	size = objectSize;
	r = red;
	g = green;
	b = black;
	a = alpha;
}

float Object::getter(char* type) 
{
	if (type == "x") {
		return x;
	} 
	else 	if (type == "y") {
		return y;
	}
	else 	if (type == "z") {
		return z;
	}
	else 	if (type == "size") {
		return size;
	}
	else 	if (type == "r") {
		return r;
	}
	else 	if (type == "g") {
		return g;
	}
	else 	if (type == "b") {
		return b;
	}
	else 	if (type == "a") {
		return a;
	}
	else 	if (type == "status") {
		return status;
	}
}