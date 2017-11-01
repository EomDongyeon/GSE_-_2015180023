#pragma once
#include <iostream>
#include "Renderer.h"

class Object
{
	float type;
	float state;
	float x, y, z;
	float vX, vY;
	float speed, size;
	float r, g, b, a;
	float life, lifeTime;


public:
	Object(float objectType, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha, float objectLife, float vecX, float vecY);
	Object();
	~Object();

	void Initialize(float objectType, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha, float objectLife, float vecX, float vecY);
	void positionUpdate(float time);
	void lifeTimeUpdate(float time);
	void lifeUpdate(float obj);
	void setPosition(float objectX, float objectY, float objectZ);
	void setState(int s);
	void setRGB(float red, float greed, float blue);
	float getter(char* type);
	
};
