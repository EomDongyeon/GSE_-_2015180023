#pragma once
#include "stdafx.h"
#include "Object.h"
#include "SceneMgr.h"
#define MAX_OBJECTS_COUNT 50


SceneMgr::SceneMgr()
{
	idxObjs = 0;
}

SceneMgr::SceneMgr(int width, int height)
{
	idxObjs = 0;
	m_renderer = new Renderer(width, height);
	if (!m_renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}
	windowWidth = width;
	windowHeight = height;

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
void SceneMgr::drawAllObjects() {
	for (int i = 0; i <  idxObjs; ++i)
		{
		m_renderer->DrawSolidRect(
			objs[i]->getter("x"),
			objs[i]->getter("y"),
			objs[i]->getter("z"),
			objs[i]->getter("size"),
			objs[i]->getter("r"),
			objs[i]->getter("g"),
			objs[i]->getter("b"),
			objs[i]->getter("a")
		);
	}
}

void SceneMgr::collisionChk()
{
	float rLeft, rRight, rTop, rBtm;
	float rLeft2, rRight2, rTop2, rBtm2;
	int collisionCount;

	for (int i = 0; i < idxObjs; ++i)
	{
		collisionCount = 0;
		for (int j = 0; j < idxObjs; ++j)	{
			rLeft = objs[i]->getter("x") - objs[i]->getter("size") / 2.f;
			rBtm = objs[i]->getter("y") - objs[i]->getter("size") / 2.f;
			rRight = objs[i]->getter("x") + objs[i]->getter("size") / 2.f;
			rTop = objs[i]->getter("y") + objs[i]->getter("size") / 2.f;

			rLeft2 = objs[j]->getter("x") - objs[j]->getter("size") / 2.f;
			rBtm2 = objs[j]->getter("y") - objs[j]->getter("size") / 2.f;
			rRight2 = objs[j]->getter("x") + objs[j]->getter("size") / 2.f;
			rTop2 = objs[j]->getter("y") + objs[j]->getter("size") / 2.f;
			if (i == j)
				continue;

			// 충돌여부 체크
			if (SquareCollision(rLeft, rRight, rTop, rBtm, rLeft2, rRight2, rTop2, rBtm2))
			{
				++collisionCount;
			}

			if (collisionCount > 0)
			{
				objs[i]->setRGB(1, 0, 0);
				objs[i]->lifeUpdate();
			}
			else
				objs[i]->setRGB(1, 1, 1);
		}
	}
}

bool SceneMgr::SquareCollision(float rLeft, float rRight, float rTop, float rBtm, float rLeft2, float rRight2, float rTop2, float rBtm2)
{
	if (rLeft > rRight2)
		return false;
	if (rRight < rLeft2)
		return false;
	if (rBtm > rTop2)
		return false;
	if (rTop < rBtm2)
		return false;

	return true;
}

void SceneMgr::update(float time)
{
	float life, lifeTime;
	for (int i = 0; i < idxObjs; ++i)
	{
		life = objs[i]->getter("life");
		lifeTime = objs[i]->getter("lifeTime");
		objs[i]->positionUpdate(time);
		//objs[i]->lifeTimeUpdate(time);
		if (lifeTime <= 0 || life <= 0)
		{
			deleteObject(i);
		}
	}

}

void SceneMgr::objectLifeUpdate(float time)
{

}

void SceneMgr::objectLifeCheck()
{
}

void SceneMgr::deleteObject(int idx)
{
	std::cout << "오브젝트 삭제 - " << idx << std::endl;
}

void SceneMgr::addObject(float objectStatus, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha)
{
	objs[idxObjs] = new Object(Object(objectStatus, objectSpeed, objectX, objectY, objectZ, objectSize, red, green, black, alpha));
	idxObjs++;
}

