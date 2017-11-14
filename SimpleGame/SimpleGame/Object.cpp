#pragma once
#include <math.h>
#include "stdafx.h"
#include "Object.h"
#include "SceneMgr.h"


Object::Object(float objectType,float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float blue, float alpha,float objectLife, float vecX, float vecY)
{
	Initialize(objectType, objectSpeed, objectX, objectY, objectZ, objectSize, red, green, blue, alpha, objectLife, vecX, vecY);
}

Object::Object()
{
	Initialize(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,1,1);
}


Object::~Object() {
}

void Object::Initialize(float objectType, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float blue, float alpha, float objectLife, float vecX, float vecY)
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
	b = blue;
	a = alpha;
	life = objectLife;
	arrowTime = 0;
	if (type == OBJECT_CHARACTER)
	{
		vX = 300.f *((float)(rand() / (float)RAND_MAX) - 0.5f);
		vY = 300.f *((float)(rand() / (float)RAND_MAX) - 0.5f);
		lifeTime = 1000;
	}
	else if (type == OBJECT_ARROW)
	{
		vX = 100.f *((float)(rand() / (float)RAND_MAX) - 0.5f);
		vY = 100.f *((float)(rand() / (float)RAND_MAX) - 0.5f);
		lifeTime = 1000;

	}
	else if (type == OBJECT_BULLET)
	{
		vX = 600.f *((float)(rand() / (float)RAND_MAX) - 0.5f);
		vY = 600.f *((float)(rand() / (float)RAND_MAX) - 0.5f);
		lifeTime = 1000;
	}
	else
	{
		vX = 300.f *((float)(rand() / (float)RAND_MAX) - 0.5f);
		vY = 300.f *((float)(rand() / (float)RAND_MAX) - 0.5f);
		lifeTime = 1000;
	}

}

void Object::positionUpdate(float time)
{
	float elapsedTime = time / 1000.f;

	arrowTime += elapsedTime;

	x = x + vX * elapsedTime;
	y = y + vY * elapsedTime;

	if (x > 250)
	{
		vX = -vX;
		if (type == OBJECT_BULLET || type == OBJECT_ARROW)
			life = 0;
	}
	if (x < -250)
	{
		vX = -vX;
		if (type == OBJECT_BULLET || type == OBJECT_ARROW)
			life = 0;
	}
	if (y > 250)
	{
		vY = -vY;
		if (type == OBJECT_BULLET || type == OBJECT_ARROW)
			life = 0;
	}
	if (y < -250)
	{
		vY = -vY;
		if (type == OBJECT_BULLET || type == OBJECT_ARROW)
			life = 0;
	}
}

void Object::lifeTimeUpdate(float time)
{
	float elapsedTime = time / 1000.f;
	lifeTime -= elapsedTime;
}

void Object::setDamage(int  objType)
{
	if (type == OBJECT_BUILDING)
	{
		if (objType == OBJECT_CHARACTER)
			life -= 10;
		if (objType == OBJECT_ARROW)
			life -= 10;
		std::cout << "°Ç¹°HP: "<<  life << std::endl;
	}
	if (type == OBJECT_CHARACTER)
	{
		if (objType == OBJECT_BUILDING)
			life = 0;
		if (objType == OBJECT_BULLET)
			life -= 20;
		if (objType == OBJECT_ARROW)
			life -= 10;
	}
	if (type == OBJECT_BULLET)
	{
		if (objType == OBJECT_BULLET)
			life = 0;
	}
	if (type == OBJECT_ARROW)
	{
		if (objType == OBJECT_ARROW)
			life = 0;

	}


}

void Object::setPosition(float objectX, float objectY, float objectZ)
{
	x = objectX;
	y = objectY;
	z = objectZ;
}

void Object::setCharAddr(int addr)
{
	charNo = addr;
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

void Object::setArrowTime(float t)
{
	arrowTime = t;
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
	else if (input == "arrowTime")
	{
		return arrowTime;
	}
	else if (input == "charNo")
	{
		return charNo;
	}
	else {
		return 0;
	}
}
