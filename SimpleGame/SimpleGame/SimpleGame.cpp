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

#include "SceneMgr.h"
#include "CObj.h"

const int WinX{ 500 };
const int WinY{ 500 };

CSceneMgr * g_SceneMgr = NULL;

DWORD g_prevTime = 0;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	
	g_SceneMgr->Render();
	glutSwapBuffers();
}

void Idle(void)
{
	/*for (int i = 0; i < Size; ++i)
	{
		if (g_Obj[i].GetDraw())
			g_Obj[i].Update();
	}*/
	DWORD CurrTime = timeGetTime();
	DWORD elapsedTime = CurrTime - g_prevTime;
	g_prevTime = CurrTime;
	g_SceneMgr->Update((float)elapsedTime);
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		/*g_Obj[Count].Initialize();
		g_Obj[Count].SetDraw(true);
		float resetX = float(x - WinX / 2);
		float resetY = float(-(y - WinY / 2));
		g_Obj[Count].SetPos(resetX, resetY);

		std::cout << "" << std::endl;
		std::cout << "Count : " << Count << std::endl;
		std::cout << "x = " << resetX << " , y = " << resetY <<  std::endl;
		Count++;
		if (Count > Size - 1)
			Count = 0;*/
		g_SceneMgr->Mouse(x, y);
	}
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
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinX, WinY);
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

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	g_SceneMgr = new CSceneMgr(WinX, WinY);
	g_prevTime = timeGetTime();

	glutMainLoop();

	g_SceneMgr->Release();
	delete g_SceneMgr;

    return 0;
}

