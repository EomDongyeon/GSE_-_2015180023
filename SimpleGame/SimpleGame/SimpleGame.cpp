/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "Object.h"
#include "SceneMgr.h"

using namespace std;

Renderer *g_Renderer = NULL;
SceneMgr *g_SceneMgr = NULL;

int idx = 0;
bool leftButtonDown = false;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	// Renderer Test
	for (int i = 0; i < g_SceneMgr->getIdx(); ++i)
	{
		Object tmp = g_SceneMgr->getObj(i);
		g_Renderer->DrawSolidRect(
			g_SceneMgr->getObj(i).getter("x"),
			g_SceneMgr->getObj(i).getter("y"),
			g_SceneMgr->getObj(i).getter("z"),
			g_SceneMgr->getObj(i).getter("size"),
			g_SceneMgr->getObj(i).getter("r"),
			g_SceneMgr->getObj(i).getter("g"),
			g_SceneMgr->getObj(i).getter("b"),
			g_SceneMgr->getObj(i).getter("a")
		);
	}


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
			g_SceneMgr->addObject(0, 20, x - 250, 250 - y, 0, 40, 1, 1, 1, 1);
			RenderScene();
		}
	}
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

	for (int i = 0; i < g_SceneMgr->getIdx(); ++i)
	{
		cout << g_SceneMgr->getObj(i).getter("y") << endl;
		g_SceneMgr->getObj(i).positionUpdate(10);
	}
	RenderScene();   // 화면 재 출력 
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정 
}

int main(int argc, char **argv)
{
	// Initialize GL things
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
	g_Renderer = new Renderer(500, 500);
	g_SceneMgr = new SceneMgr();
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutTimerFunc(100, TimerFunction, 1);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutMainLoop();

	delete g_Renderer;

	return 0;
}

