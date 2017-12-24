#pragma once
#include "stdafx.h"
#include "Object.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	idxObjs = 0;
}

SceneMgr::SceneMgr(int width, int height)
{
	idxObjs = 0;
	idxChar = 0;
	idxBullet = 0;
	idxArrow = 0;
	climateTime = 0;
	animeIdx = 0;

	m_renderer = new Renderer(width, height);
	if (!m_renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}
	windowWidth = width;
	windowHeight = height;

	BgTexID = m_renderer->CreatePngTexture("Textures/PNGs/bg.png");
	winBgTexID = m_renderer->CreatePngTexture("Textures/PNGs/winResult.png");
	loseBgTexID = m_renderer->CreatePngTexture("Textures/PNGs/loseResult.png");
	Team1TexID = m_renderer->CreatePngTexture("Textures/PNGs/pic1.png");
	Team2TexID = m_renderer->CreatePngTexture("Textures/PNGs/pic2.png");
	Bullet1TexID = m_renderer->CreatePngTexture("Textures/PNGs/bullet1.png");
	Bullet2TexID = m_renderer->CreatePngTexture("Textures/PNGs/bullet2.png");
	ParticleTexID = m_renderer->CreatePngTexture("Textures/PNGs/particle_effect.png");
	Char1TexID = m_renderer->CreatePngTexture("Textures/PNGs/character-sprite.png");
	Char2TexID = m_renderer->CreatePngTexture("Textures/PNGs/character2-sprite.png");
	FlyChar1TexID = m_renderer->CreatePngTexture("Textures/PNGs/flying_sprite.png");
	FlyChar2TexID = m_renderer->CreatePngTexture("Textures/PNGs/flying_sprite2.png");
	ClimateTexID = m_renderer->CreatePngTexture("Textures/PNGs/snow.png");
	m_sound = new Sound();
	int soundBG = m_sound->CreateSound("Sound/bgm.mp3");

	m_sound->PlaySound(soundBG, true, 0.2f);


}

SceneMgr::~SceneMgr() {
	delete[] objs;
	delete m_renderer;
	delete m_sound;
}


int SceneMgr::getIdx()
{
	return idxObjs;
}

Object SceneMgr::getObj(int idx)
{
	return *objs[idx];
}

void SceneMgr::drawAllObjects(float time) {
	float elapsedTime = time / 1000.f;
	char buf[200];
	int mainIdx = 0;
	//배경 그리기 
	
	m_renderer->DrawTexturedRect(
		0,
		0,
		0,
		800,
		1,
		1,
		1,
		1,
		m_renderer->CreatePngTexture("Textures/PNGs/bg.png"),
		0.4
	);
	climateTime += elapsedTime;

	// 오브젝트 그리기
	if (animeIdx++ > 10)
		animeIdx = 0;

	m_renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, ParticleTexID, climateTime, LEVEL_GOD);

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (objs[i] == nullptr)
			continue;
		else {
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
						objs[i]->getter("a"), 
						Team1TexID,
						LEVEL_SKY
					);
					m_renderer->DrawSolidRectGauge(
						objs[i]->getter("x"),
						objs[i]->getter("y") + 60,
						objs[i]->getter("z"),
						100,
						10,
						1,
						0,
						0,
						1,
						objs[i]->getter("life") / 500,
						LEVEL_SKY
					);					
					itoa((int)objs[i]->getter("life"), buf, 10);
					m_renderer->DrawTextW(
						objs[i]->getter("x") + 60,
						objs[i]->getter("y") + 55,
						GLUT_BITMAP_HELVETICA_18,
						0, 0, 0, buf
					);
				}
				else 	if (objs[i]->getter("type") == OBJECT_CHARACTER)
				{
					int charType = objs[i]->getter("charType");
					int maxIdx = 0;
					if (charType == 0)
						maxIdx = 9;
					else
						maxIdx = 3;

					int idx = objs[i]->getter("animeIdx");
					if (idx > maxIdx)
						idx = 0;

				//	if (mainIdx % 2 == 0)
					//	idx++;

					if (charType == 0)
					{
						m_renderer->DrawTexturedRectSeq(
							objs[i]->getter("x"),
							objs[i]->getter("y"),
							objs[i]->getter("z"),
							80,
							objs[i]->getter("r"),
							objs[i]->getter("g"),
							objs[i]->getter("b"),
							objs[i]->getter("a"),
							Char1TexID,
							idx++,
							0,
							10,
							1,
							LEVEL_GROUND
						);
						objs[i]->setAnimeIdx(idx);

						m_renderer->DrawSolidRectGauge(
							objs[i]->getter("x"),
							objs[i]->getter("y") + 35,
							objs[i]->getter("z"),
							50,
							5,
							1,
							0,
							0,
							1,
							objs[i]->getter("life") / 100,
							LEVEL_GROUND
						);

						itoa((int)objs[i]->getter("life"), buf, 10);
						m_renderer->DrawTextW(
							objs[i]->getter("x") + 30,
							objs[i]->getter("y") + 35,
							GLUT_BITMAP_HELVETICA_12,
							0, 0, 0, buf
						);
					}
					else if (charType == 1) {
						m_renderer->DrawTexturedRectSeq(
							objs[i]->getter("x"),
							objs[i]->getter("y"),
							objs[i]->getter("z"),
							80,
							objs[i]->getter("r"),
							objs[i]->getter("g"),
							objs[i]->getter("b"),
							objs[i]->getter("a"),
							FlyChar1TexID,
							idx++,
							0,
							4,
							1,
							LEVEL_SKY
						);
						objs[i]->setAnimeIdx(idx);

						m_renderer->DrawSolidRectGauge(
							objs[i]->getter("x"),
							objs[i]->getter("y") + 35,
							objs[i]->getter("z"),
							50,
							5,
							1,
							0,
							0,
							1,
							objs[i]->getter("life") / 100,
							LEVEL_SKY
						);

						itoa((int)objs[i]->getter("life"), buf, 10);
						m_renderer->DrawTextW(
							objs[i]->getter("x") + 30,
							objs[i]->getter("y") + 35,
							GLUT_BITMAP_HELVETICA_12,
							0, 0, 0, buf
						);
					}
					mainIdx++;
				}

				else if(objs[i]->getter("type") == OBJECT_BULLET)
				{
					m_renderer->DrawParticle(
						objs[i]->getter("x"),
						objs[i]->getter("y"),
						objs[i]->getter("z"),
						5,
						1,
						1,
						1,
						1,
						(objs[i]->getter("vX")* -1),
						(objs[i]->getter("vY") * -1),
						ParticleTexID,
						objs[i]->getter("particleTime"), LEVEL_GROUND
					);

					m_renderer->DrawTexturedRect(
						objs[i]->getter("x"),
						objs[i]->getter("y"),
						objs[i]->getter("z"),
						20,
						1,
						1,
						1,
						1,
						Bullet1TexID,
						LEVEL_UNDERGROUND
					);
				}
				else	{
					m_renderer->DrawSolidRect(
						objs[i]->getter("x"),
						objs[i]->getter("y"),
						objs[i]->getter("z"),
						objs[i]->getter("size"),
						objs[i]->getter("r"),
						objs[i]->getter("g"),
						objs[i]->getter("b"),
						objs[i]->getter("a"),
						LEVEL_UNDERGROUND
					);

				}

			} 
			else {
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
						objs[i]->getter("a"), 
						Team2TexID,
						LEVEL_SKY
					);
					m_renderer->DrawSolidRectGauge(
						objs[i]->getter("x"),
						objs[i]->getter("y") + 60,
						objs[i]->getter("z"),
						100,
						10,
						0,
						0,
						1,
						1,
						objs[i]->getter("life") / 500,
						LEVEL_SKY
					);
					itoa((int)objs[i]->getter("life"), buf, 10);
					m_renderer->DrawTextW(
						objs[i]->getter("x") + 60,
						objs[i]->getter("y") + 55,
						GLUT_BITMAP_HELVETICA_18,
						0, 0, 0, buf
					);
				}
				else 	if (objs[i]->getter("type") == OBJECT_CHARACTER)
				{
					int charType = objs[i]->getter("charType");
					int maxIdx = 0;
					if (charType == 0)
						maxIdx = 9;
					else
						maxIdx = 3;

					int idx = objs[i]->getter("animeIdx");
					if (idx > maxIdx)
						idx = 0;

					if (charType == 0)
					{
						m_renderer->DrawTexturedRectSeq(
							objs[i]->getter("x"),
							objs[i]->getter("y"),
							objs[i]->getter("z"),
							80,
							objs[i]->getter("r"),
							objs[i]->getter("g"),
							objs[i]->getter("b"),
							objs[i]->getter("a"),
							Char2TexID,
							idx++,
							0,
							10,
							1,
							LEVEL_GROUND
						);
						objs[i]->setAnimeIdx(idx);

						m_renderer->DrawSolidRectGauge(
							objs[i]->getter("x"),
							objs[i]->getter("y") + 35,
							objs[i]->getter("z"),
							50,
							5,
							0,
							0,
							1,
							1,
							objs[i]->getter("life") / 100,
							LEVEL_GROUND
						);

						itoa((int)objs[i]->getter("life"), buf, 10);
						m_renderer->DrawTextW(
							objs[i]->getter("x") + 30,
							objs[i]->getter("y") + 35,
							GLUT_BITMAP_HELVETICA_12,
							0, 0, 0, buf
						);
					}
					else if (charType == 1) {   // flying Character
						m_renderer->DrawTexturedRectSeq(
							objs[i]->getter("x"),
							objs[i]->getter("y"),
							objs[i]->getter("z"),
							80,
							objs[i]->getter("r"),
							objs[i]->getter("g"),
							objs[i]->getter("b"),
							objs[i]->getter("a"),
							FlyChar2TexID,
							idx++,
							0,
							4,
							1,
							LEVEL_SKY
						);
						objs[i]->setAnimeIdx(idx);

						m_renderer->DrawSolidRectGauge(
							objs[i]->getter("x"),
							objs[i]->getter("y") + 35,
							objs[i]->getter("z"),
							50,
							5,
							0,
							0,
							1,
							1,
							objs[i]->getter("life") / 100,
							LEVEL_SKY
						);

						itoa((int)objs[i]->getter("life"), buf, 10);
						m_renderer->DrawTextW(
							objs[i]->getter("x") + 30,
							objs[i]->getter("y") + 35,
							GLUT_BITMAP_HELVETICA_12,
							0, 0, 0, buf
						);
					}

				} 	
				else if (objs[i]->getter("type") == OBJECT_BULLET)	{
					m_renderer->DrawParticle(
						objs[i]->getter("x"),
						objs[i]->getter("y"),
						objs[i]->getter("z"),
						7,
						1,
						1,
						1,
						1,
						(objs[i]->getter("vX")* -1),
						(objs[i]->getter("vY") * -1),
						ParticleTexID,
						objs[i]->getter("particleTime"), LEVEL_GROUND
					);

					m_renderer->DrawTexturedRect(
						objs[i]->getter("x"),
						objs[i]->getter("y"),
						objs[i]->getter("z"),
						20,
						1,
						1,
						1,
						1,
						Bullet2TexID,
						LEVEL_UNDERGROUND
					);
				}	else	{
					m_renderer->DrawSolidRect(
						objs[i]->getter("x"),
						objs[i]->getter("y"),
						objs[i]->getter("z"),
						objs[i]->getter("size"),
						objs[i]->getter("r"),
						objs[i]->getter("g"),
						objs[i]->getter("b"),
						objs[i]->getter("a"),
						LEVEL_UNDERGROUND
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

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < MAX_OBJECTS_COUNT; ++j) {
			if (objs[i] == nullptr || objs[j] == nullptr)
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
					if (objs[i]->getter("team") != objs[j]->getter("team"))
					{
						std::cout << "빌딩-캐릭터 충돌" << std::endl;
						objs[i]->setDamage(OBJECT_BUILDING);
						objs[j]->setDamage(OBJECT_BUILDING);
					}
				}
				else if (objs[i]->getter("type") == OBJECT_CHARACTER &&objs[j]->getter("type") == OBJECT_CHARACTER)
				{
					if (objs[i]->getter("team") != objs[j]->getter("team"))
					{
						std::cout << "캐릭터-캐릭터 충돌" << std::endl;
						objs[i]->setDamage(OBJECT_CHARACTER);
						objs[j]->setDamage(OBJECT_CHARACTER);
					}
				}
				else if (objs[i]->getter("type") == OBJECT_CHARACTER &&objs[j]->getter("type") == OBJECT_BULLET)
				{
					if (objs[i]->getter("team") != objs[j]->getter("team"))
					{
						std::cout << "총알-캐릭터 충돌" << std::endl;
						objs[i]->setDamage(OBJECT_BULLET);
						objs[j]->setDamage(OBJECT_BULLET);
					}
				}
				else if (objs[i]->getter("type") == OBJECT_CHARACTER &&objs[j]->getter("type") == OBJECT_ARROW)
				{
					if (objs[i]->getter("team") != objs[j]->getter("team"))
					{
						std::cout << "화살-캐릭터 충돌" << std::endl;
						objs[i]->setDamage(OBJECT_ARROW);
						objs[j]->setDamage(OBJECT_ARROW);
					}
				}
				else if (objs[i]->getter("type") == OBJECT_BUILDING &&objs[j]->getter("type") == OBJECT_ARROW)
				{
					if (objs[i]->getter("team") != objs[j]->getter("team"))
					{
						std::cout << "건물-화살 충돌" << std::endl;
						objs[i]->setDamage(OBJECT_ARROW);
						objs[j]->setDamage(OBJECT_ARROW);
					}
				}
				else if (objs[i]->getter("type") == OBJECT_BUILDING &&objs[j]->getter("type") == OBJECT_BULLET)
				{
					if (objs[i]->getter("team") != objs[j]->getter("team"))
					{
						std::cout << "건물-총알 충돌" << std::endl;
						objs[i]->setDamage(OBJECT_BULLET);
						objs[j]->setDamage(OBJECT_BULLET);
					}
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

	if (charTime > 5.0f)
	{
		addObject(std::rand() % 200, 20 + std::rand() % 300, OBJECT_CHARACTER, 0, TEAM_1);
		charTime = 0;
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (objs[i] != NULL) {
			life = objs[i]->getter("life");
			lifeTime = objs[i]->getter("lifeTime");
			if (objs[i]->getter("type") == OBJECT_BUILDING)
			{
				objs[i]->positionUpdate(time);
				if (objs[i]->getter("bulletTime") > 5.0f)
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

	ResultChk();

}

void SceneMgr::resultScene()
{
	if (sceneMode == WIN)
	{
		m_renderer->DrawTexturedRect(
			0,
			0,
			0,
			800,
			1,
			1,
			1,
			1,
			winBgTexID,
			0.1
		);
	}
	else if (sceneMode == LOSE)
	{
		m_renderer->DrawTexturedRect(
			0,
			0,
			0,
			800,
			1,
			1,
			1,
			1,
			loseBgTexID,
			0.1
		);
	}
}

void SceneMgr::ResultChk()
{
	int team1lose = 0;
	int team2lose = 0;
	for (int i = 0; i < 6; ++i)
	{
		if (objs[i] == NULL)
			continue;
		if (i >= 3)
		{
			if (objs[i]->getter("type") != OBJECT_BUILDING)
				++team1lose;
		}
		else
		{
			if (objs[i]->getter("type") != OBJECT_BUILDING)
				++team2lose;
		}

	}
	if (team1lose >= 3)
		sceneMode = LOSE;
	else if (team2lose >= 3)
		sceneMode = WIN;
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
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, -150, 300, 0, 100, 1, 1, 1, 1, 500, 0, 0, TEAM_1));
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, 0, 270, 0, 100, 1, 1, 1, 1, 500, 0, 0, TEAM_1));
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, 150, 300, 0, 100, 1, 1, 1, 1, 500, 0, 0, TEAM_1));

	//team2 building
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, -150, -300, 0, 100, 1, 1, 1, 1, 500, 0, 0, TEAM_2));
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, 0, -270, 0, 100, 1, 1, 1, 1, 500, 0, 0, TEAM_2));
	objs[idxObjs++] = new Object(Object(OBJECT_BUILDING, 0, 150, -300, 0, 100, 1, 1, 1, 1, 500, 0, 0, TEAM_2));

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
						objs[i] = new Object(Object(OBJECT_CHARACTER, 200, objectX, objectY, 0, 30, 1, 0, 0, 1, 100, 1, 1, TEAM_1));
					else 
						objs[i] = new Object(Object(OBJECT_CHARACTER, 200, objectX, objectY, 0, 30, 1, 1, 1, 1, 100, 1, 1, TEAM_2));
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
						objs[i] = new Object(Object(OBJECT_BULLET, 400, objectX, objectY, 0, 4, 1, 0, 0, 4, 15, rand() % 2, rand() % 2, TEAM_1));
					else
						objs[i] = new Object(Object(OBJECT_BULLET, 400, objectX, objectY, 0, 4, 0, 0,10, 4, 15, rand() % 2, rand() % 2, TEAM_2));

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
		if (idxArrow < 50)
		{
			int i = 0;
			while (true)
			{
				if (objs[i] == NULL)
				{
					if(team == TEAM_1)
						objs[i] = new Object(Object(OBJECT_ARROW, 150, objectX, objectY, 0, 4, 0.5, 0.2, 0.7, 1, 10, rand() % 2, rand() % 2, TEAM_1));
					else
						objs[i] = new Object(Object(OBJECT_ARROW, 150, objectX, objectY, 0, 4, 1, 1, 0, 1, 10, rand() % 2, rand() % 2, TEAM_2));
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

