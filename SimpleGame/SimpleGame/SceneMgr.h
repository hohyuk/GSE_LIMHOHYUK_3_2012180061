#pragma once
#include "Renderer.h"
#include "CObj.h"
const int MAX_COUNT = 10;
class CSceneMgr
{
public:
	CSceneMgr();
	CSceneMgr(int width_,int height_);
	~CSceneMgr();

	void Init();
	void Render();
	void Update(float elapsedTime);
	void Mouse(int x,int y);
	void Release();

private:
	void BoxCollision();
private:
	Renderer* m_render;
	CObj* m_Obj[MAX_COUNT];
	int m_WinX;
	int m_WinY;
	int colcount;
	int mousecount;
};

