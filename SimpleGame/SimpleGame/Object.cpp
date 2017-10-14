#pragma once
#include "stdafx.h"
#include "Object.h"


Object::Object(float objectStatus,float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha)
{
	Initialize(objectStatus, objectSpeed, objectX, objectY, objectZ, objectSize, red, green, black, alpha);
}

Object::~Object() {
};

void Object::Initialize(float objectStatus, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha)
{
	status = objectStatus;
	x = objectX;
	y = objectY;
	z = objectZ;
	speed = objectSpeed;
	size = objectSize;
	r = red;
	g = green;
	b = black;
	a = alpha;
}

void Object::positionUpdate(float time)
{
	x = x + speed * time;
	y = y + speed * time;
	z = z + speed * time;
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
	else 	if (type == "speed") {
		return speed;
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