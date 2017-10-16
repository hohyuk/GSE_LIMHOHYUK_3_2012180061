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

#include "CObj.h"
const int WinX{ 500 };
const int WinY{ 500 };
const int Size{ 10 };
int Count{ 0 };
Renderer *g_Renderer = NULL;
CObj* g_Obj = NULL;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	for (int i = 0; i < Size; ++i)
	{
		if (g_Obj[i].GetDraw())
			g_Renderer->DrawSolidRect(g_Obj[i].GetXpos(), g_Obj[i].GetYpos(), g_Obj[i].GetZpos(), g_Obj[i].GetSize(), g_Obj[i].GetcolorR(), g_Obj[i].GetcolorG(), g_Obj[i].GetcolorB(), 1);

	}
	glutSwapBuffers();
}

void Idle(void)
{
	for (int i = 0; i < Size; ++i)
	{
		if (g_Obj[i].GetDraw())
			g_Obj[i].Update();
	}
	
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_Obj[Count].Initialize();
		g_Obj[Count].SetDraw(true);
		float resetX = float(x - WinX / 2);
		float resetY = float(-(y - WinY / 2));
		g_Obj[Count].SetPos(resetX, resetY);

		std::cout << "" << std::endl;
		std::cout << "Count : " << Count << std::endl;
		std::cout << "x = " << resetX << " , y = " << resetY <<  std::endl;
		Count++;
		if (Count > Size - 1)
			Count = 0;
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

	// Initialize Renderer
	g_Renderer = new Renderer(WinX, WinY);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	g_Obj = new CObj[Size];

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	delete[] g_Obj;
    return 0;
}

