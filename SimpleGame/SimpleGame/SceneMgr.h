#pragma once
#include "Renderer.h"
#include "CObj.h"
const int MAX_COUNT = 100;
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
	void Collision();

private:
	Renderer* m_render;
	CObj* m_Obj[MAX_COUNT];
	CObj* m_building;
	CObj* m_Bbullet[MAX_COUNT];
	int m_WinX;
	int m_WinY;
	int colcount;
	int mousecount;
	int time;
	int count;
};

