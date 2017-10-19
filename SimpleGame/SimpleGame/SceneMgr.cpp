#include "stdafx.h"
#include "SceneMgr.h"

#include "Renderer.h"
#include "CObj.h"

const int WinX{ 500 };
const int WinY{ 500 };
const int Size{ 50 };
int Count{ 0 };

Renderer *g_Renderer = NULL;
CObj* g_Obj = NULL;
CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Init()
{
	g_Renderer = new Renderer(WinX, WinY);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	g_Obj = new CObj[Size];
}

void CSceneMgr::Render()
{
	for (int i = 0; i < Size; ++i)
	{
		if (g_Obj[i].GetDraw())
			g_Renderer->DrawSolidRect(g_Obj[i].GetXpos(), g_Obj[i].GetYpos(), g_Obj[i].GetZpos(), g_Obj[i].GetSize(), g_Obj[i].GetcolorR(), g_Obj[i].GetcolorG(), g_Obj[i].GetcolorB(), 1);
	}
}

void CSceneMgr::Update()
{
	for (int i = 0; i < Size; ++i)
	{
		if (g_Obj[i].GetDraw())
			g_Obj[i].Update();
	}

	for (int i = 0; i < Size; ++i)
	{
		
		for (int j = 0; j < Size; ++j)
		{
			if (i != j)
			{
				float minX1 = g_Obj[i].GetXpos() - g_Obj[i].GetSize() / 2;
				float minY1 = g_Obj[i].GetYpos() - g_Obj[i].GetSize() / 2;
				float maxX1 = g_Obj[i].GetXpos() + g_Obj[i].GetSize() / 2;
				float maxY1 = g_Obj[i].GetYpos() + g_Obj[i].GetSize() / 2;

				float minX2 = g_Obj[j].GetXpos() - g_Obj[j].GetSize() / 2;
				float minY2 = g_Obj[j].GetYpos() - g_Obj[j].GetSize() / 2;
				float maxX2 = g_Obj[j].GetXpos() + g_Obj[j].GetSize() / 2;
				float maxY2 = g_Obj[j].GetYpos() + g_Obj[j].GetSize() / 2;

				if (BoxBoxCollision(minX1, minY1, maxX1, maxY1, minX2, minY2, maxX2, maxY2))
				{
					g_Obj[i].SetColor(1, 0, 0);
					g_Obj[j].SetColor(1, 0, 0);
				}
			}
		}
	}
}

void CSceneMgr::Mouse(int x,int y)
{
	g_Obj[Count].Initialize();
	g_Obj[Count].SetDraw(true);
	float resetX = float(x - WinX / 2);
	float resetY = float(-(y - WinY / 2));
	g_Obj[Count].SetPos(resetX, resetY);

	std::cout << "" << std::endl;
	std::cout << "Count : " << Count << std::endl;
	std::cout << "x = " << resetX << " , y = " << resetY << std::endl;
	Count++;
	if (Count > Size - 1)
		Count = 0;
}

bool CSceneMgr::BoxBoxCollision(float minX1, float minY1, float maxX1, float maxY1, float minX2, float minY2, float maxX2, float maxY2)
{
	if (minX1 > maxX2)
		return false;
	if (minY1 > maxY2)
		return false;
	if (maxX1 < maxX2)
		return false;
	if (maxY1 < maxY2)
		return false;
	return true;
}

void CSceneMgr::Release()
{
	delete g_Renderer;
	delete[] g_Obj;
}
