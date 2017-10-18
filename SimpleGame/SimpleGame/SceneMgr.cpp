#pragma once
#include "stdafx.h"
#include "Object.h"
#include "SceneMgr.h"
#define MAX_OBJECTS_COUNT 50


SceneMgr::SceneMgr()
{
	idxObjs = 0;
}

SceneMgr::~SceneMgr() {
}

/*
void SceneMgr::addObject(Object obj)
{
	objs[idxObjs] = new Object(obj);
	idxObjs += 1;
}
*/

int SceneMgr::getIdx()
{
	return idxObjs;
}

Object SceneMgr::getObj(int idx)
{
	return *objs[idx];
}

void SceneMgr::update()
{
	for (int i = 0; i < idxObjs; ++i)
		objs[i]->positionUpdate(10);
}

void SceneMgr::addObject(float objectStatus, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha)
{
	objs[idxObjs] = new Object(Object(objectStatus, objectSpeed, objectX, objectY, objectZ, objectSize, red, green, black, alpha));
	idxObjs++;
}

