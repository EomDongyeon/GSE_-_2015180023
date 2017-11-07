#pragma once
#include "stdafx.h"
#include "Object.h"
#include "SceneMgr.h"


int idxChar = 0;

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
				++collisionCount;

			if (collisionCount > 0)
			{
				if (objs[i]->getter("type") == OBJECT_BUILDING &&objs[j]->getter("type") == OBJECT_CHARACTER || objs[j]->getter("type")  == OBJECT_BUILDING && objs[i]->getter("type") == OBJECT_CHARACTER)
				{
					std:: cout << "빌딩과 충돌" << std::endl;
					objs[i]->lifeUpdate(objs[j]->getter("type"));
				}
				else if (objs[i]->getter("type") == OBJECT_CHARACTER &&objs[j]->getter("type") == OBJECT_BULLET || objs[j]->getter("type") == OBJECT_BULLET && objs[i]->getter("type") == OBJECT_CHARACTER)
				{
					std::cout << "총알과 충돌" << std::endl;
					objs[i]->setRGB(0, 1, 1);
					objs[i]->lifeUpdate(objs[j]->getter("type"));
				}
			}
			else
			{
				if(objs[i]->getter("type") == OBJECT_BUILDING)
					objs[i]->setRGB(1,1,0);
				else if(objs[i]->getter("type") == OBJECT_CHARACTER)
					objs[i]->setRGB(1,1,1);
				else if (objs[i]->getter("type") == OBJECT_BULLET)
					objs[i]->setRGB(1,0,0);
			}
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
		if (objs[i]->getter("type") != OBJECT_BUILDING)
		{
			life = objs[i]->getter("life");
			lifeTime = objs[i]->getter("lifeTime");
			objs[i]->positionUpdate(time);
			objs[i]->lifeTimeUpdate((int)time % 5);
			if (lifeTime <= 0 || life <= 0)
			{
				deleteObject(i);
			}
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
	objs[idx] = nullptr;
	idxObjs -= 1;
	for (int i = idx; i < idxObjs; ++i)
		objs[idx] = objs[idx + 1];
	objs[idxObjs] = nullptr;
}

void SceneMgr::initObject()
{
	objs[idxObjs] = new Object(Object(OBJECT_BUILDING, 0, 0, 0, 0, 50, 1, 1, 0, 1, 500,0 ,0));
	idxObjs++;
	addObject(0, 0, OBJECT_BULLET);

}



void SceneMgr::addObject(float objectX, float objectY, float objectType)
{
	if(objectType == OBJECT_BUILDING)
		objs[idxObjs] = new Object(Object(OBJECT_BUILDING, 0, objectX, objectY, 0, 50, 1, 1, 0, 1, 500 , 0, 0));
	else if (objectType == OBJECT_CHARACTER)
	{
		if (idxChar < 10)
		{
			objs[idxObjs] = new Object(Object(OBJECT_CHARACTER, 100, objectX, objectY, 0, 10, 1, 1, 1, 1, 10,1, 1));
			idxChar++;
		}
		else		{
		idxObjs--;		idxChar--;
		}
	}
	else if (objectType == OBJECT_BULLET)
		objs[idxObjs] = new Object(Object(OBJECT_BULLET, 300, objectX, objectY, 0, 5, 1, 0, 0, 1, 20, rand() % 2, rand() % 2));
	else if (objectType == OBJECT_ARROW)
		objs[idxObjs] = new Object(Object(OBJECT_ARROW, 100, objectX, objectY, 0, 5, 0, 1, 0, 1, 10, rand() % 2, rand() % 2));

	idxObjs++;
}

