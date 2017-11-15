#pragma once
#include "stdafx.h"
#include "Object.h"
#include "SceneMgr.h"

int idxChar = 0;
int idxBullet = 0;
int idxArrow = 0;

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
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (objs[i] == NULL)
			continue;
		{
			if (objs[i]->getter("team") == TEAM_1)
			{
				if (objs[i]->getter("type") == OBJECT_BUILDING)
				{


					m_renderer->DrawTexturedRect(
						objs[i]->getter("x"),
						objs[i]->getter("y"),
						objs[i]->getter("z"),
						objs[i]->getter("size"),
						objs[i]->getter("r"),
						objs[i]->getter("g"),
						objs[i]->getter("b"),
						objs[i]->getter("a"), m_renderer->CreatePngTexture("Textures/PNGs/pic1.png")
					);
				}
				else
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
			} else {
				if (objs[i]->getter("type") == OBJECT_BUILDING)
				{


					m_renderer->DrawTexturedRect(
						objs[i]->getter("x"),
						objs[i]->getter("y"),
						objs[i]->getter("z"),
						objs[i]->getter("size"),
						objs[i]->getter("r"),
						objs[i]->getter("g"),
						objs[i]->getter("b"),
						objs[i]->getter("a"), m_renderer->CreatePngTexture("Textures/PNGs/pic2.png")
					);
				}
				else
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
		}
	}
}

void SceneMgr::collisionChk()
{
	float rLeft, rRight, rTop, rBtm;
	float rLeft2, rRight2, rTop2, rBtm2;
	int collisionCount;

	for (int i = 0; i < idxObjs; ++i)
	{
		for (int j = 0; j < idxObjs; ++j) {
			if (objs[i] == NULL || objs[j] == NULL)
				continue;
			if (i == j)
				continue;

			rLeft = objs[i]->getter("x") - objs[i]->getter("size") / 2.f;
			rBtm = objs[i]->getter("y") - objs[i]->getter("size") / 2.f;
			rRight = objs[i]->getter("x") + objs[i]->getter("size") / 2.f;
			rTop = objs[i]->getter("y") + objs[i]->getter("size") / 2.f;

			rLeft2 = objs[j]->getter("x") - objs[j]->getter("size") / 2.f;
			rBtm2 = objs[j]->getter("y") - objs[j]->getter("size") / 2.f;
			rRight2 = objs[j]->getter("x") + objs[j]->getter("size") / 2.f;
			rTop2 = objs[j]->getter("y") + objs[j]->getter("size") / 2.f;


			// 충돌여부 체크
			if (rLeft < rRight2 && rRight > rLeft2 && rBtm < rTop2 && rTop > rBtm2) {
				if (objs[i]->getter("type") == OBJECT_BUILDING &&objs[j]->getter("type") == OBJECT_CHARACTER)
				{
					std::cout << "빌딩-캐릭터 충돌" << std::endl;
					objs[i]->setDamage(OBJECT_BUILDING);
					objs[j]->setDamage(OBJECT_BUILDING);
				}
				else if (objs[i]->getter("type") == OBJECT_CHARACTER &&objs[j]->getter("type") == OBJECT_BULLET)
				{
					std::cout << "총알-캐릭터 충돌" << std::endl;
					objs[i]->setDamage(OBJECT_BULLET);
					objs[j]->setDamage(OBJECT_BULLET);
				}
				else if (objs[i]->getter("type") == OBJECT_CHARACTER &&objs[j]->getter("type") == OBJECT_ARROW)
				{
					if ((float)i != objs[j]->getter("charNo"))
					{
						std::cout << "화살-캐릭터 충돌" << std::endl;
						objs[i]->setDamage(OBJECT_ARROW);
						objs[j]->setDamage(OBJECT_ARROW);
					}
				}
				else if (objs[i]->getter("type") == OBJECT_BUILDING &&objs[j]->getter("type") == OBJECT_ARROW)
				{

					std::cout << "건물-화살 충돌" << std::endl;
					objs[i]->setDamage(OBJECT_ARROW);
					objs[j]->setDamage(OBJECT_ARROW);
				}
			}

		}
	}
}

void SceneMgr::updateAllObjects(float time)
{
	float life, lifeTime;
	float elapsedTime = time / 1000.f;

	charTime += elapsedTime;

	if (charTime > 1.0f)
	{
		addObject(std::rand() % 200, 20 + std::rand() % 300, OBJECT_CHARACTER, 0, TEAM_1);
		charTime = 0;
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (objs[i] == NULL)
			continue;
		else {
			life = objs[i]->getter("life");
			lifeTime = objs[i]->getter("lifeTime");
			if (objs[i]->getter("type") == OBJECT_BUILDING)
			{
				objs[i]->positionUpdate(time);
				if (objs[i]->getter("bulletTime") > 0.5f)
				{
					addObject(objs[i]->getter("x"), objs[i]->getter("y"), OBJECT_BULLET, i, objs[i]->getter("team"));
					objs[i]->setBulletTime(0);
				}

			}
			else if (objs[i]->getter("type") == OBJECT_CHARACTER)
			{
				objs[i]->positionUpdate(time);
				objs[i]->lifeTimeUpdate(time);
				if (objs[i]->getter("arrowTime") > 1.0f)
				{
					addObject(objs[i]->getter("x"), objs[i]->getter("y"), OBJECT_ARROW, i, objs[i]->getter("team"));
					objs[i]->setArrowTime(0);
				}

			}
			else if (objs[i]->getter("type") == OBJECT_BULLET)
			{
				objs[i]->positionUpdate(time);
				objs[i]->lifeTimeUpdate(time);
			}
			else if (objs[i]->getter("type") == OBJECT_ARROW)
			{
				objs[i]->positionUpdate(time);
				objs[i]->lifeTimeUpdate(time);
			}
			if (life <= 0)
				deleteObject(i);
			if (lifeTime <= 0)
			{
				std::cout << "LifeTime End" << std::endl;
				deleteObject(i);
			}
		}
	}

}

void SceneMgr::deleteObject(int idx)
{
	std::cout << "오브젝트 삭제 - " << idx << std::endl;
	if (objs[idx]->getter("type") == OBJECT_CHARACTER)
		--idxChar;
	else if (objs[idx]->getter("type") == OBJECT_BULLET)
		--idxBullet;
	else if (objs[idx]->getter("type") == OBJECT_ARROW)
		--idxArrow;
	--idxObjs;

	delete objs[idx];
	objs[idx] = NULL;


}

void SceneMgr::initObject()
{
	//team1 building
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, -150, 300, 0, 100, 1, 1, 0, 1, 500, 0, 0, TEAM_1));
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, 0, 300, 0, 100, 1, 1, 0, 1, 500, 0, 0, TEAM_1));
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, 150, 300, 0, 100, 1, 1, 0, 1, 500, 0, 0, TEAM_1));

	//team2 building
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, -150, -300, 0, 100, 1, 1, 0, 1, 500, 0, 0, TEAM_2));
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, 0, -300, 0, 100, 1, 1, 0, 1, 500, 0, 0, TEAM_2));
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, 150, -300, 0, 100, 1, 1, 0, 1, 500, 0, 0, TEAM_2));

}



void SceneMgr::addObject(float objectX, float objectY, float objectType, int idx, int team)
{
	if (objectType == OBJECT_BUILDING)
		objs[idxObjs] = new Object(Object(OBJECT_BUILDING, 0, objectX, objectY, 0, 100, 1, 1, 0, 1, 500, 0, 0, 1));
	else if (objectType == OBJECT_CHARACTER)
	{
		if (idxChar < 20)
		{
			int i = 0;
			while (true)
			{
				if (objs[i] == NULL)
				{
					if (team == TEAM_1)
						objs[i] = new Object(Object(OBJECT_CHARACTER, 300, objectX, objectY, 0, 10, 1, 0, 0, 1, 10, 1, 1, TEAM_1));
					else 
						objs[i] = new Object(Object(OBJECT_CHARACTER, 300, objectX, objectY, 0, 10, 0, 1, 1, 1, 10, 1, 1, TEAM_2));
					++idxObjs;
					++idxChar;
					break;
				}
				++i;
			}
		}
	}
	else if (objectType == OBJECT_BULLET)
	{
		if (idxBullet < 30)
		{
			int i = 0;
			while (true)
			{
				if (objs[i] == NULL)
				{
					if (team == TEAM_1)
						objs[i] = new Object(Object(OBJECT_BULLET, 600, objectX, objectY, 0, 2, 1, 0, 0, 1, 20, rand() % 2, rand() % 2, TEAM_1));
					else
						objs[i] = new Object(Object(OBJECT_BULLET, 600, objectX, objectY, 0, 2, 0, 0,10, 1, 20, rand() % 2, rand() % 2, TEAM_2));

					++idxObjs;
					++idxBullet;
					break;
				}
				++i;
			}
		}
	}
	else if (objectType == OBJECT_ARROW)
	{
		if (idxArrow < 30)
		{
			int i = 0;
			while (true)
			{
				if (objs[i] == NULL)
				{
					if(team == TEAM_1)
						objs[i] = new Object(Object(OBJECT_ARROW, 100, objectX, objectY, 0, 2, 0.5, 0.2, 0.7, 1, 10, rand() % 2, rand() % 2, TEAM_1));
					else
						objs[i] = new Object(Object(OBJECT_ARROW, 100, objectX, objectY, 0, 2, 1, 1, 0, 1, 10, rand() % 2, rand() % 2, TEAM_2));
					objs[i]->setCharAddr(idx);
					++idxObjs;
					++idxArrow;
					break;
				}
				++i;
			}
		}
		/*else
		{
		int i = 0;
		while (true)
		{
		if (objs[i] != NULL)
		{
		if (objs[i]->getter("type") == OBJECT_ARROW)
		{
		deleteObject(i);
		--idxArrow;
		break;
		}
		}
		++i;
		}
		}
		*/
	}
}

