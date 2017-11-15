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
	float arrowTime, bulletTime;
	float charNo;
	float team;

public:
	Object(float objectType, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float blue, float alpha, float objectLife, float vecX, float vecY, float objectTeam);
	Object();
	~Object();

	void Initialize(float objectType, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float blue, float alpha, float objectLife, float vecX, float vecY, float objectTeam);
	void positionUpdate(float time);
	void lifeTimeUpdate(float time);
	void setDamage(int type);
	void setPosition(float objectX, float objectY, float objectZ);
	void setCharAddr(int addr);
	void setState(int s);
	void setRGB(float red, float greed, float blue);
	void setArrowTime(float t);
	void setBulletTime(float t);
	float getter(char* type);
	
};
