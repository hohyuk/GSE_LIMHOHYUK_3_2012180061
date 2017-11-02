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
	{
		m_Obj[i] = NULL;
		m_Bbullet[i] = NULL;
	}
		
	colcount = 0;
	mousecount = -1;

	// building
	m_building = new CObj();
	m_building->AddActorObject(0, 0, OBJECT_BUILDING);
	time = 0;
	count = 0;
}

void CSceneMgr::Render()
{
	if (m_building != NULL)
	{
		m_render->DrawSolidRect(m_building->GetXpos(), m_building->GetYpos(), m_building->GetZpos(), m_building->GetSize()
			, m_building->GetcolorR(), m_building->GetcolorG(), m_building->GetcolorB(), 1);
	}
	
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

	for (int i = 0; i < MAX_COUNT; ++i)
	{
		if (m_Bbullet[i] != NULL)
		{
			if (m_Bbullet[i]->GetLife() < 0.f)
			{
				delete m_Bbullet[i];
				m_Bbullet[i] = NULL;
			}
			else
			{
				m_render->DrawSolidRect(m_Bbullet[i]->GetXpos(), m_Bbullet[i]->GetYpos(), m_Bbullet[i]->GetZpos(), m_Bbullet[i]->GetSize()
					, m_Bbullet[i]->GetcolorR(), m_Bbullet[i]->GetcolorG(), m_Bbullet[i]->GetcolorB(), 1);
			}
		}
	}
}

void CSceneMgr::Update(float elapsedTime)
{
	BoxCollision();
	Collision();
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		if (m_Obj[i] != NULL)
		{
			m_Obj[i]->Update(elapsedTime);
		}
	}
	time += elapsedTime;
	if (time > 150)
	{
		time = 0;
		if (count < MAX_COUNT)
		{
			if (m_building != NULL)
			{
				m_Bbullet[count] = new CObj();
				m_Bbullet[count++]->AddActorObject(m_building->GetXpos(), m_building->GetYpos(), OBJECT_BULLET);
			}
		}
	}
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		if (m_Bbullet[i] != NULL)
		{
			
			m_Bbullet[i]->Update(elapsedTime);
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

void CSceneMgr::Collision()
{
	for (int i = 0; i < MAX_COUNT; ++i)
	{
		if (m_Obj[i] != NULL && m_building != NULL)
		{
			float width = m_Obj[i]->GetXpos() - m_building->GetXpos();
			float height = m_Obj[i]->GetYpos() - m_building->GetYpos();
			float distance = sqrtf((width*width) + (height*height));
			if (distance < m_building->GetSize()/2.f)
			{
				m_Obj[i]->SetLife(50);
				m_building->SetLife(5);
				std::cout << m_building->GetLife() << std::endl;
				if (m_Obj[i]->GetLife() < 0)
				{
					delete m_Obj[i];
					m_Obj[i] = NULL;
				}
				if (m_building->GetLife() < 0)
				{
					for (int i = 0; i < MAX_COUNT; ++i)
					{
						delete m_Bbullet[i];
						m_Bbullet[i] = NULL;
					}
					delete m_building;
					m_building = NULL;	
				}
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