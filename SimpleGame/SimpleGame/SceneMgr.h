#pragma once
#include <iostream>
#include "Renderer.h"
#include "Object.h"

#define MAX_OBJECTS_COUNT 61
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
	float bulletTime = 0;
	float arrowTime = 0;

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

	void addObject(float objectX, float objectY, float objectType, int idx);


};
