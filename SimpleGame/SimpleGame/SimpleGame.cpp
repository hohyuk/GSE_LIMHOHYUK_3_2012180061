/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
//#include <iostream>
#include "SceneMgr.h"


#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"



DWORD prevTime = timeGetTime();

CSceneMgr *g_SceneMgr = NULL;

void RenderScene(void)
{
	DWORD curTime = timeGetTime();
	DWORD elapsedTime = curTime - prevTime;		// 경과시간 = 현재시간 - 과거시간.
	prevTime = curTime;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	g_SceneMgr->Update(float(elapsedTime));
	g_SceneMgr->Render();
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	bool Lbutton = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;

	// 마우스 클릭 오브젝트 생성.
	if (Lbutton)
		g_SceneMgr->CreateObj(x, y);

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
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

	// SceneMgr 객체 생성
	g_SceneMgr = new CSceneMgr();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);


	glutMainLoop();

	// 객체 삭제
	g_SceneMgr->Release();
	delete g_SceneMgr;

	return 0;
}

