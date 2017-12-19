#pragma once
#include <iostream>
#include "Renderer.h"
#include "Object.h"
#include "Sound.h"

#define MAX_OBJECTS_COUNT 120

#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3

#define TEAM_1 1
#define TEAM_2 2

#define LEVEL_GOD 0
#define LEVEL_SKY 0.1
#define LEVEL_GROUND 0.2
#define LEVEL_UNDERGROUND 0.3



class SceneMgr
{
	int idxObjs;
	int idxChar;
	int idxBullet;
	int idxArrow;
	int animeIdx;
	int windowWidth;
	int windowHeight;
	float climateTime;

	Object *objs[MAX_OBJECTS_COUNT] = { NULL ,};
	Renderer *m_renderer;
	Sound *m_sound;

	GLuint BgTexID;
	GLuint Team1TexID;
	GLuint Team2TexID;
	GLuint Bullet1TexID;
	GLuint Bullet2TexID;
	GLuint ParticleTexID;
	GLuint Char1TexID;
	GLuint Char2TexID;
	GLuint ClimateTexID;

	float charTime = 5.1f;

public:
	SceneMgr();
	SceneMgr(int width, int height);
	~SceneMgr();
	int  getIdx();
	Object getObj(int idx);
	void drawAllObjects(float time);
	void collisionChk();
	void updateAllObjects(float time);

	void deleteObject(int idx);


	void initObject();

	void addObject(float objectX, float objectY, float objectType, int idx, int team);


};




