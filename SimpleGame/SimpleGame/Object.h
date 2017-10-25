#pragma once
#include <iostream>
#include "Renderer.h"

class Object
{
	enum  statusType
	{
		building =0, 
		obstacle,
		cannon,
		bullet
	};
	float status;
	float state;
	float x, y, z;
	float vX, vY;
	float speed, size;
	float r, g, b, a;

public:
	Object(float objectStatus,float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha);
	Object();
	~Object();

	void Initialize(float objectStatus, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha);
	void positionUpdate(float time);
	void setPosition(float objectX, float objectY, float objectZ);
	void setState(int s);
	void setRGB(float red, float greed, float blue);
	float getter(char* type);
	
};
