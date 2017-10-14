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
Renderer *g_Renderer = NULL;
CObj* g_Obj = NULL;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	if (g_Obj->GetDraw())
		g_Renderer->DrawSolidRect(g_Obj->GetXpos(), g_Obj->GetYpos(), g_Obj->GetZpos(), g_Obj->GetSize(), g_Obj->GetcolorR(), g_Obj->GetcolorG(), g_Obj->GetcolorB(), 1);

	glutSwapBuffers();
}

void Idle(void)
{
	g_Obj->Update();
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_Obj->SetDraw(true);
		float resetX = float(x - WinX / 2);
		float resetY = float(-(y - WinY / 2));
		g_Obj->SetPos(resetX, resetY);

		std::cout << "" << std::endl;
		std::cout << "x = " << resetX << " , y = " << resetY <<  std::endl;

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

	g_Obj = new CObj();
	g_Obj->Initialize();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	delete g_Obj;
    return 0;
}

