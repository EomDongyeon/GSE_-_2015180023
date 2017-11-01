/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "stdlib.h"
#include "ctime"
#include "windows.h"
#include <iostream>
#include <vector>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "Object.h"
#include "SceneMgr.h"

using namespace std;

SceneMgr *g_SceneMgr = NULL;
DWORD g_prevTime = 0;

int idx = 0;
bool leftButtonDown = false;
bool first = true;

void RenderScene(void)
{
	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	// Renderer Test

	if (first)
	{
		g_SceneMgr->initObject();
		first = false;
	}

	g_SceneMgr->drawAllObjects();

	if (g_SceneMgr->getIdx() > 1)
		g_SceneMgr->collisionChk();

	g_SceneMgr->update((float)currTime);

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	// 클릭 & 드래그 사용 
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		leftButtonDown = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (leftButtonDown)
		{
			cout << x << " : " << y << endl;
			g_SceneMgr->addObject(x - 250, 250 - y, OBJECT_CHARACTER);
		}
	}
//	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

void TimerFunction(int value) {
	glutPostRedisplay(); // 화면 재 출력
	g_SceneMgr->addObject(0, 0, OBJECT_BULLET);
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}



int main(int argc, char **argv)
{
	// Initialize GL things
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_SceneMgr = new SceneMgr(500, 500);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();

	delete g_SceneMgr;

	return 0;
}

