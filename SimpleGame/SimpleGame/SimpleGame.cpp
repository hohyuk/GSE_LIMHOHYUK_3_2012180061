/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
//#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "SceneMgr.h"

CSceneMgr* g_SceneMgr = NULL;

// 타임값을 구한다.
DWORD g_prevTime = 0;
float g_coolTime = COOLTIME;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	DWORD curTime = timeGetTime();
	DWORD elapsedTime = curTime - g_prevTime;	// 경과시간 = 현재시간 - 과거시간.
	g_prevTime = curTime;
	g_coolTime += elapsedTime / 1000.f;		// 마우스 버튼 쿨타임
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
	float resetX = float(x - Width / 2);
	float resetY = float(-(y - Height / 2));
	bool Lbutton = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;
	bool LCoolTime = g_coolTime > COOLTIME;
	bool South_IN = resetY < 0 && Lbutton && LCoolTime;		// 0 작아야하고 7초이상 왼쪽버튼 눌렸으면 TRUE. 
	
	if (South_IN)
	{
		g_SceneMgr->AddActorObject(resetX, resetY, TEAM_MY, OBJECT_GROUNDUNIT);
		g_coolTime = 0.f;
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

	// Initialize SceneMgr
	g_SceneMgr = new CSceneMgr();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_prevTime = timeGetTime();		// Loop를 돌기전 마지막 타임을 저장.

	glutMainLoop();

	// 객체 삭제
	g_SceneMgr->Release();
	delete g_SceneMgr;
	g_SceneMgr = NULL;
    return 0;
}

