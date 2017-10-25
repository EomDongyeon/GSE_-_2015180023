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

void SceneMgr::collisionChk()
{
	for (int i = 0; i < idxObjs; ++i)
	{
		int rectX = objs[i]->getter("x");
		int rectY = objs[i]->getter("y");
		for (int j = 0; j < idxObjs; ++j)	{
			if (i != j)
			{
				int rectX2 = objs[j]->getter("x");
				int rectY2 = objs[j]->getter("y");

				// 충돌여부 체크
				if (rectX + 10 >= rectX2 && rectX <= rectX2 + 10 && rectY + 10 >= rectY2 && rectY <= rectY2 + 10)
				{
					objs[j]->setState(1);
					objs[i]->setState(1);
					objs[j]->setRGB(1, 0, 0);
					objs[i]->setRGB(1, 0, 0);
				}
				else {
					//	objs[j]->setState(0);
					//	objs[i]->setState(0);
					//	objs[j]->setRGB(1, 1, 1);
					//	objs[i]->setRGB(1, 1, 1);
				}
			}
		}
	}
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

