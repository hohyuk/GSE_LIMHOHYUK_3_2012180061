#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr()
{
}

CSceneMgr::CSceneMgr(int width_, int height_)
	:m_WinX(width_),m_WinY(height_)
{
	Init();
}

CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Init()
{
	m_render = new Renderer(m_WinX, m_WinY);
	if (!m_render->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_COUNT; ++i)
		m_Obj[i] = NULL;
	colcount = 0;
	mousecount = -1;
}

void CSceneMgr::Render()
{
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		if (m_Obj[i] != NULL)
		{
			if (m_Obj[i]->GetLifeTime() < 0.f || m_Obj[i]->GetLife() < 0.f)
			{
				delete m_Obj[i];
				m_Obj[i] = NULL;
				mousecount = i - 1;
			}
			else
			{
				m_render->DrawSolidRect(m_Obj[i]->GetXpos(), m_Obj[i]->GetYpos(), m_Obj[i]->GetZpos(), m_Obj[i]->GetSize()
					, m_Obj[i]->GetcolorR(), m_Obj[i]->GetcolorG(), m_Obj[i]->GetcolorB(), 1);
			}
		}
	}
}

void CSceneMgr::Update(float elapsedTime)
{
	BoxCollision();
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		if (m_Obj[i] != NULL)
		{
			m_Obj[i]->Update(elapsedTime);
		}
	}
}

void CSceneMgr::Mouse(int x,int y)
{
	if (mousecount < MAX_COUNT)
	{
		++mousecount;
		if (m_Obj[mousecount] == NULL)
		{
			float resetX = float(x - m_WinX / 2);
			float resetY = float(-(y - m_WinY / 2));
			m_Obj[mousecount] = new CObj(resetX, resetY);
		}
	}
}

void CSceneMgr::BoxCollision()
{
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		colcount = 0;
		if (m_Obj[i] != NULL)
		{
			for (int j = 0; j < MAX_COUNT; ++j)
			{
				if (m_Obj[j] != NULL)
				{
					if (i != j)
					{
						float width = m_Obj[i]->GetXpos() - m_Obj[j]->GetXpos();
						float height = m_Obj[i]->GetYpos() - m_Obj[j]->GetYpos();
						float distance = sqrtf((width*width) + (height*height));
						if (distance < m_Obj[i]->GetSize())
						{
							colcount++;
						}
					}
				}
			}
			if (colcount > 0)
			{
				m_Obj[i]->SetColor(1, 0, 0);
			}
			else
			{
				m_Obj[i]->SetColor(1, 1, 1);
			}
		}
	}
}

void CSceneMgr::Release()
{
	delete m_render;
	for (int i = 0; i < MAX_COUNT; ++i)
		delete m_Obj[i];
}