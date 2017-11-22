#pragma once
#include <iostream>
#include "Renderer.h"
#include "Object.h"

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
	int windowWidth;
	int windowHeight;
	Object *objs[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;
	float charTime = 6.0;

public:
	SceneMgr();
	SceneMgr(int width, int height);
	~SceneMgr();
	int  getIdx();
	Object getObj(int idx);
	void drawAllObjects();
	void collisionChk();
	void updateAllObjects(float time);

	void deleteObject(int idx);


	void initObject();

	void addObject(float objectX, float objectY, float objectType, int idx, int team);


};
