#pragma once
#include "stdafx.h"
#include "Object.h"


Object::Object(float objectStatus,float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha)
{
	Initialize(objectStatus, objectSpeed, objectX, objectY, objectZ, objectSize, red, green, black, alpha);
}

Object::Object()
{
	Initialize(0, 0, 0, 0, 0, 0, 0, 0, 1, 1);
}

Object::~Object() {
}

void Object::Initialize(float objectStatus, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha)
{
	status = objectStatus;
	state = 0;
	x = objectX;
	y = objectY;
	z = objectZ;
	speed = objectSpeed;
	size = objectSize;
	r = red;
	g = green;
	b = black;
	a = alpha;
	lifeTime = 10000;
	life = 1;
	vX = 1;
	vY = 1;
}

void Object::positionUpdate(float time)
{
	float elapsedTime = (int)time % 3;
	
	x = x + vX * elapsedTime;
	y = y + vY * elapsedTime;

	if (x > 250)
		vX = -vX;

	if (x < -250)
		vX = 1;

	if (y > 250)
		vY = -vY;

	if (y < -250)
		vY = 1;
}

void Object::lifeTimeUpdate(float time)
{
	lifeTime -= time;
}

void Object::lifeUpdate()
{
	life -= 1;
}

void Object::setPosition(float objectX, float objectY, float objectZ)
{
	x = objectX;
	y = objectY;
	z = objectZ;
}

void Object::setState(int s)
{
	state = s;
}

void Object::setRGB(float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;
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
	else 	if (type == "life") {
		return life;
	}
	else 	if (type == "lifeTime") {
		return lifeTime;
	}
	else {
		return 0;
	}
}