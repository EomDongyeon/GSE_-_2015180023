/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "Object.h"

Renderer *g_Renderer = NULL;
Object *building[10] = { NULL };

int idx = 0;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	for (int i = 0; i < idx; ++i)
		g_Renderer->DrawSolidRect(building[idx]->getter("x"), building[idx]->getter("y"), building[idx]->getter("z"), building[idx]->getter("size"), building[idx]->getter("r"), building[idx]->getter("g"), building[idx]->getter("b"), building[idx]->getter("a"));

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		building[idx] = new Object(0, 20, 110, 0, 0, 40, 1, 0, 0, 1);
		++idx;
		RenderScene();
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

	for(int i = 0; i < idx; ++i)
		building[i]->positionUpdate(1);
	std::cout << "타이머" << std::endl;
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
	delete building;

    return 0;
}

