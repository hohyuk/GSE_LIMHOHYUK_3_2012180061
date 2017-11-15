#include "stdafx.h"
#include "SceneMgr.h"


CSceneMgr::CSceneMgr()
{
	Init();
}


CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Init()
{
	m_Renderer = new Renderer(Width, Height);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	// Obj °´Ã¼ Bullet °´Ã¼ ÃÊ±âÈ­
	obj_count = 0;
	bullet_count = 0;
	bullet_time = 0;
	arrowCount = 0;
	arrowTime = 0;
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		//m_Objs[i] = NULL;			// CHARACTER, BUILDING °´Ã¼µé
		m_Obj[i] = NULL;
		m_Bullet[i] = NULL;
		for (int j = 0; j < MAX_ARROW_COUNT; ++j)
		{
			m_Arrow[i][j] = NULL;
		}
	}
	// Building ÃÊ±âÈ­
	//m_Objs[0]= new CObj(0, 0, OBJECT_BUILDING);
	m_Building = new CObj(0, 0, OBJECT_BUILDING);
}

void CSceneMgr::Update(float elapsedTime)
{
	CharacterCollision();
	CreateBullet(elapsedTime);
	
	BulletCollision();
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		bool isNotNULL = m_Obj[i] != NULL;

		if (isNotNULL)
		{
			arrowTime += elapsedTime / 1000.f;

			if (m_Obj[i] != NULL)
			{
				if ((arrowCount < MAX_ARROW_COUNT) && arrowTime > 0.5)
				{
					m_Arrow[i][arrowCount++] = new CObj(m_Obj[i]->GetXpos(), m_Obj[i]->GetYpos(), OBJECT_ARROW);
					arrowTime = 0.f;
				}
			}
			if (m_Obj[i]->GetLifeTime() < 0)
			{
				for (int j = 0; j < MAX_ARROW_COUNT; ++j)
				{
					if (m_Arrow[i][j] != NULL)
					{
						delete m_Arrow[i][j];
						m_Arrow[i][j] = NULL;
					}
				}
				delete m_Obj[i];
				m_Obj[i] = NULL;
				break;
			}
			else
			{
				m_Obj[i]->Update(elapsedTime);
				for (int j = 0; j < MAX_ARROW_COUNT; ++j)
				{
					if (m_Arrow[i][j] != NULL)
					{
						m_Arrow[i][j]->Update(elapsedTime);
					}
				}
			}
				
			// Building Collision
			if (m_Building != NULL)
				BuildingCollision(m_Obj[i]);
		}

		if (m_Bullet[i] != NULL)
			m_Bullet[i]->Update(elapsedTime);
	}
}

void CSceneMgr::CreateObj(int x, int y)
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		if (m_Obj[i] == NULL)
		{
			float resetX = float(x - Width / 2);
			float resetY = float(-(y - Height / 2));
			m_Obj[i] = new CObj(resetX, resetY, OBJECT_CHARACTER);
			break;
		}
	}
}

void CSceneMgr::Render()
{
	Character_render();
	Building_render();
	Bullet_render();
	Arrow_render();
}

void CSceneMgr::Release()
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		delete m_Obj[i];
		m_Obj[i] = NULL;
		delete m_Bullet[i];
		m_Bullet[i];
	}
	delete m_Building;
	delete m_Renderer;
}

bool CSceneMgr::Collision(float x1, float y1, float x2, float y2, float size1, float size2)
{
	float width = x2 - x1;
	float height = y2 - y1;
	float distance = sqrtf((width * width) + (height * height));
	float sizesum = (size1 / 2) + (size2 / 2);
	if (distance < sizesum)
		return true;

	return false;
}

bool CSceneMgr::Collision1(float x1, float y1, float size1, float x2, float y2, float size2)
{
	float left1 = x1 - size1 / 2.f;
	float bottom1 = y1 - size1 / 2.f;
	float right1 = x1 + size1 / 2.f;
	float top1 = y1 + size1 / 2.f;

	float left2 = x2 - size2 / 2.f;
	float bottom2 = y2 - size2 / 2.f;
	float right2 = x2 + size2 / 2.f;
	float top2 = y2 + size2 / 2.f;

	if (left1 > right2)
		return false;
	if (right1 < left2)
		return false;
	if (bottom1 > top2)
		return false;
	if (top1 < bottom2)
		return false;
	return true;
}

void CSceneMgr::CharacterCollision()
{
	bool collisionCount = false;
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		collisionCount = false;
		if (m_Obj[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJ_COUNT; ++j)
			{
				if (i != j && m_Obj[j] != NULL)
				{
					if (Collision(m_Obj[i]->GetXpos(), m_Obj[i]->GetYpos(), m_Obj[j]->GetXpos(), m_Obj[j]->GetYpos(), m_Obj[i]->GetSize(), m_Obj[j]->GetSize()))
					{
						collisionCount = true;
					}
				}
			}
			if (collisionCount)
				m_Obj[i]->SetColor(0.5, 0, 0);
			else
				m_Obj[i]->SetColor(1, 1, 1);
		}
	}
}

void CSceneMgr::BuildingCollision(CObj *& obj)
{
	if (Collision1(obj->GetXpos(), obj->GetYpos(), obj->GetXpos(), m_Building->GetXpos(), m_Building->GetYpos(), m_Building->GetSize()))
	{
		m_Building->SetLife(obj->GetLife());
		if (m_Building->GetLife() < 0)
		{
			delete m_Building;
			m_Building = NULL;
		}
		delete obj;
		obj = NULL;
	}
}

void CSceneMgr::CreateBullet(float elapsedTime)
{
	bullet_time += elapsedTime / 1000.f;
	if (m_Building != NULL)
	{
		if ((bullet_count < MAX_OBJ_COUNT) && bullet_time > 0.5)
		{
			m_Bullet[bullet_count++] = new CObj(m_Building->GetXpos(), m_Building->GetYpos(), OBJECT_BULLET);
			bullet_time = 0.f;
		}
	}
}

void CSceneMgr::CreateArrow(float elapsedTime, int count)
{
	arrowTime += elapsedTime / 1000.f;
	
	if (m_Obj[count] != NULL)
	{
		if ((arrowCount < MAX_ARROW_COUNT) && arrowTime > 0.5)
		{
			m_Arrow[count][arrowCount++] = new CObj(m_Obj[count]->GetXpos(), m_Obj[count]->GetYpos(), OBJECT_ARROW);
			arrowTime = 0.f;
		}
	}
	
}

void CSceneMgr::BulletCollision()
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		if (m_Obj[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJ_COUNT; ++j)
			{
				if (m_Bullet[j] != NULL)
				{
					if (Collision(m_Obj[i]->GetXpos(), m_Obj[i]->GetYpos(), m_Bullet[j]->GetXpos(), m_Bullet[j]->GetYpos(), m_Obj[i]->GetSize(), m_Bullet[j]->GetSize()))
					{
						m_Obj[i]->SetLife(m_Bullet[j]->GetLife());

						delete m_Bullet[j];
						m_Bullet[j] = NULL;
						if (m_Obj[i]->GetLife() < 0)
						{
							delete m_Obj[i];
							m_Obj[i] = NULL;
							break;
						}
					}
				}
			}
		}
	}
}

void CSceneMgr::Character_render()
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		if (m_Obj[i] != NULL)
		{
			m_Renderer->DrawSolidRect(m_Obj[i]->GetXpos(), m_Obj[i]->GetYpos(), 0, m_Obj[i]->GetSize()
				, m_Obj[i]->GetcolorR(), m_Obj[i]->GetcolorG(), m_Obj[i]->GetcolorB(), 1);
		}
	}
}

void CSceneMgr::Building_render()
{
	if (m_Building != NULL)
	{
		GLint m_texCharacter = m_Renderer->CreatePngTexture("../Resource/pika.png");
		/*m_Renderer->DrawSolidRect(m_Building->GetXpos(), m_Building->GetYpos(), 0, m_Building->GetSize()
			, m_Building->GetcolorR(), m_Building->GetcolorG(), m_Building->GetcolorB(), 1);*/
		m_Renderer->DrawTexturedRect(m_Building->GetXpos(), m_Building->GetYpos(), 0, m_Building->GetSize()
			, m_Building->GetcolorR(), m_Building->GetcolorG(), m_Building->GetcolorB(), 1, m_texCharacter);
	}
}

void CSceneMgr::Bullet_render()
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		if (m_Bullet[i] != NULL)
		{
			m_Renderer->DrawSolidRect(m_Bullet[i]->GetXpos(), m_Bullet[i]->GetYpos(), 0, m_Bullet[i]->GetSize()
				, m_Bullet[i]->GetcolorR(), m_Bullet[i]->GetcolorG(), m_Bullet[i]->GetcolorB(), 1);
		}
	}
}

void CSceneMgr::Arrow_render()
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		if (m_Obj[i] != NULL)
		{
			for (int j = 0; j < MAX_ARROW_COUNT; ++j)
			{
				if (m_Arrow[i][j] != NULL)
				{
					m_Renderer->DrawSolidRect(m_Arrow[i][j]->GetXpos(), m_Arrow[i][j]->GetYpos(), 0, m_Arrow[i][j]->GetSize()
						, m_Arrow[i][j]->GetcolorR(), m_Arrow[i][j]->GetcolorG(), m_Arrow[i][j]->GetcolorB(), 1);
				}
				
			}
		}
	}
}
