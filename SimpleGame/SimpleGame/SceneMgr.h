#pragma once
#include <iostream>
#include "Renderer.h"
#include "Object.h"
#define MAX_OBJECTS_COUNT 50

class SceneMgr
{
	int idxObjs;
	Object *objs[MAX_OBJECTS_COUNT];

public:
	SceneMgr();
	~SceneMgr();
	int  getIdx();
	Object getObj(int idx);
	void addObject(float objectStatus, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha);

};
