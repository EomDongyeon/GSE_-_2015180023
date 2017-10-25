#pragma once
#include <iostream>
#include "Renderer.h"
#include "Object.h"
#define MAX_OBJECTS_COUNT 50

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
	void addObject(float objectStatus, float objectSpeed, float objectX, float objectY, float objectZ, float objectSize, float red, float green, float black, float alpha);
	void update(float time);

	void objectLifeUpdate(float time);
	void objectLifeCheck();

	void deleteObject(int idx);


};
