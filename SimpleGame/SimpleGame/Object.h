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
	float size;
	float r, g, b, a;

public:
	Object(float objectStatus, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha);
	~Object();

	void Initialize(float objectStatus, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha);
	float getter(char* type);
	
};
