#pragma once
#include <iostream>
#include "Renderer.h"
#include "Object.h"

#define MAX_OBJECTS_COUNT 50
#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3

class SceneMgr
{
	int idxObjs;
	int windowWidth;
	int windowHeight;
	Object *objs[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;

public:
	SceneMgr();
	SceneMgr(int width, int height);
	~SceneMgr();
	int  getIdx();
	Object getObj(int idx);
	void drawAllObjects();
	void collisionChk();
	bool SquareCollision(float rLeft, float rRight, float rTop, float rBtm, float rLeft2, float rRight2, float rTop2, float rBtm2);
	void addObject(float objectX, float objectY, float  objectType);
	void update(float time);

	void objectLifeUpdate(float time);
	void objectLifeCheck();

	void deleteObject(int idx);

	void initObject();


};
