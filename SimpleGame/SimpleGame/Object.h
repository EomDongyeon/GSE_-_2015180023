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
	float getter(char* type);
	
};
