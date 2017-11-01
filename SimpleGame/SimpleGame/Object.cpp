#pragma once
#include "stdafx.h"
#include "Object.h"
#include "SceneMgr.h"


Object::Object(float objectType,float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha,float objectLife, float vecX, float vecY)
{
	Initialize(objectType, objectSpeed, objectX, objectY, objectZ, objectSize, red, green, black, alpha, objectLife, vecX, vecY);
}

Object::Object()
{
	Initialize(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,1,1);
}


Object::~Object() {
}

void Object::Initialize(float objectType, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha, float objectLife, float vecX, float vecY)
{
	type = objectType;
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
	life = objectLife;
	vX = vecX;
	vY = vecY;
	if (vecX == 0)
		vX = -1;
	if (vecY == 0)
		vY = -1;
}

void Object::positionUpdate(float time)
{
	float elapsedTime = (int)time % 3;
	
	x = x + vX * elapsedTime;
	y = y + vY * elapsedTime;

	if (type == OBJECT_CHARACTER)
	{
		if (x > 250)
			vX = -vX;

		if (x < -250)
			vX = 1;

		if (y > 250)
			vY = -vY;

		if (y < -250)
			vY = 1;
	}
	if (x > 250 || x < -250 || y > 250 || y < -250)
		life = 0;
}

void Object::lifeTimeUpdate(float time)
{
	lifeTime -= time;
}

void Object::lifeUpdate(float obj)
{
	if(obj == OBJECT_BUILDING)
		life -= 10;
	if (obj == OBJECT_CHARACTER)
		life -= 10;
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

float Object::getter(char* input) 
{
	if (input == "x") {
		return x;
	} 
	else 	if (input == "y") {
		return y;
	}
	else 	if (input == "z") {
		return z;
	}
	else 	if (input == "speed") {
		return speed;
	}
	else 	if (input == "size") {
		return size;
	}
	else 	if (input == "r") {
		return r;
	}
	else 	if (input == "g") {
		return g;
	}
	else 	if (input == "b") {
		return b;
	}
	else 	if (input == "a") {
		return a;
	}
	else 	if (input == "type") {
		return type;
	}
	else 	if (input == "life") {
		return life;
	}
	else 	if (input == "lifeTime") {
		return lifeTime;
	}
	else {
		return 0;
	}
}