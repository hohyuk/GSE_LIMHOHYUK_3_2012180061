#include "stdafx.h"
#include "SceneMgr.h"
int CSceneMgr::Win = 0;
int CSceneMgr::Lose = 0;

CSceneMgr::CSceneMgr()
{
	m_Renderer = new Renderer(Width, Height);
	Init();
}

CSceneMgr::~CSceneMgr()
{
	this->Release();
}

void CSceneMgr::Init()
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		m_Objs[i] = NULL;
	}
	// Player Building
	AddActorObject(-150, -300, OBJECT_PLAYER, OBJECT_BUILDING);
	AddActorObject(0, -300, OBJECT_PLAYER, OBJECT_BUILDING);
	AddActorObject(150, -300, OBJECT_PLAYER, OBJECT_BUILDING);
	// Enemy Building
	AddActorObject(-150, 300, OBJECT_ENEMY, OBJECT_BUILDING);
	AddActorObject(0, 300, OBJECT_ENEMY, OBJECT_BUILDING);
	AddActorObject(150, 300, OBJECT_ENEMY, OBJECT_BUILDING);

	
	m_PlayerCoolTime = 0.f;

	
}

bool CSceneMgr::AddActorObject(float x, float y, OBJTYPE team, OBJTYPE type)
{
	// Objs의 NULL값을 찾고 NULL값에 객체를 저장한다.
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		if (m_Objs[i] == NULL)
		{
			m_Objs[i] = new CObj(x, y, team, type);
			return true;
		}
	}
	cout << "CHARACTER FULL." << endl;
	return false;
}

void CSceneMgr::Update(float elapsedTime)
{
	m_particleTime += elapsedTime / 1000.f;
	CreateCharacter(elapsedTime);
	CollisionCompare();
	for (int i = 0; i < MAX_OBJ_COUNT; i++)
	{
		if (m_Objs[i] != NULL)
		{
			if (m_Objs[i]->GetLife() > 0.f)
			{
				m_Objs[i]->Update(elapsedTime);

				CreateBullet(m_Objs[i]);
				CreateArrow(m_Objs[i]);
			}
			else
			{
				delete m_Objs[i];
				m_Objs[i] = NULL;
			}

		}
		
	}
}

void CSceneMgr::Render()
{
	BackGroundRender();

	for (int i = 0; i < MAX_OBJ_COUNT; i++)
	{
		if (m_Objs[i] != NULL)
		{
			if (m_Objs[i]->GetTeam() == OBJECT_PLAYER)
			{
				if (m_Objs[i]->GetType() == OBJECT_BUILDING)
					TextureRender(m_Objs[i], "../Resource/building1.png");
				if (m_Objs[i]->GetType() == OBJECT_CHARACTER)
					AnimationRender(m_Objs[i], "../Resource/player01.png",3);
				if (m_Objs[i]->GetType() == OBJECT_BULLET)
					ParticleRender(m_Objs[i], -1, "../Resource/particle01.png");
				GaugeRender(m_Objs[i], 0, 0, 1, 1);
			}
			else if (m_Objs[i]->GetTeam() == OBJECT_ENEMY)
			{
				if (m_Objs[i]->GetType() == OBJECT_BUILDING)
					TextureRender(m_Objs[i], "../Resource/building2.png");
				if (m_Objs[i]->GetType() == OBJECT_CHARACTER)
					AnimationRender(m_Objs[i], "../Resource/enemy01.png", 5);
				if (m_Objs[i]->GetType() == OBJECT_BULLET)
					ParticleRender(m_Objs[i], 1, "../Resource/particle03.png");
				GaugeRender(m_Objs[i], 1, 0, 0, 1);
			}
			else
			{
				m_Renderer->DrawSolidRect(
					m_Objs[i]->GetXpos(),
					m_Objs[i]->GetYpos(),
					0,
					m_Objs[i]->GetSize(),
					m_Objs[i]->GetcolorR(),
					m_Objs[i]->GetcolorG(),
					m_Objs[i]->GetcolorB(),
					m_Objs[i]->GetcolorA(),
					m_Objs[i]->GetLevel()
				);
			}
			
		}
	}
}

void CSceneMgr::Release()
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		delete m_Objs[i];
		m_Objs[i] = NULL;
	}
}

bool CSceneMgr::CollisionObjs(CObj *& Obj_1, CObj *& Obj_2)
{
	// Rect & Rect Collision.
	float left_1, right_1, top_1, bottom_1;		// Obj_1
	float left_2, right_2, top_2, bottom_2;		// Obj_2

	// Obj_1
	left_1 = Obj_1->GetXpos() - Obj_1->GetSize() / 2.f;
	right_1 = Obj_1->GetXpos() + Obj_1->GetSize() / 2.f;
	bottom_1 = Obj_1->GetYpos() - Obj_1->GetSize() / 2.f;
	top_1 = Obj_1->GetYpos() + Obj_1->GetSize() / 2.f;

	// Obj_2
	left_2 = Obj_2->GetXpos() - Obj_2->GetSize() / 2.f;
	right_2 = Obj_2->GetXpos() + Obj_2->GetSize() / 2.f;
	bottom_2 = Obj_2->GetYpos() - Obj_2->GetSize() / 2.f;
	top_2 = Obj_2->GetYpos() + Obj_2->GetSize() / 2.f;

	// Not Collision
	if (left_1 > right_2)
		return false;
	if (right_1 < left_2)
		return false;

	if (bottom_1 > top_2)
		return false;
	if (top_1 < bottom_2)
		return false;

	// Collision
	return true;
}

void CSceneMgr::CollisionCompare()
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		for (int j = 0; j < MAX_OBJ_COUNT; ++j)
		{
			bool isNotSame = i != j;
			bool isNotNull = m_Objs[i] != NULL && m_Objs[j] != NULL;
			bool isSatisfy = isNotSame && isNotNull;		// 두 조건을 충족된다면.

			if (isSatisfy)
			{
				if (CollisionObjs(m_Objs[i], m_Objs[j]))
				{
					ObjTypeCompare(m_Objs[i], m_Objs[j]);
				}

			}

		}
	}
}

bool CSceneMgr::ObjTypeCompare(CObj* & Obj_1, CObj* & Obj_2)
{
	// 팀 구별
	if (Obj_1->GetTeam() == Obj_2->GetTeam())
		return false;

	// Building and Bullet 충돌
	ObjTypeCollision(Obj_1, Obj_2);
	ObjTypeCollision(Obj_2, Obj_1);

	return true;
}

void CSceneMgr::ObjTypeCollision(CObj *& Obj_1, CObj *& Obj_2)
{
	// character 구별
	bool isCharacter1 = Obj_1->GetType() == OBJECT_CHARACTER;
	bool isBuilding1 = Obj_1->GetType() == OBJECT_BUILDING;
	bool isBullet1 = Obj_1->GetType() == OBJECT_BULLET;
	bool isArrow1 = Obj_1->GetType() == OBJECT_ARROW;

	bool isCharacter2 = Obj_2->GetType() == OBJECT_CHARACTER;
	bool isBuilding2 = Obj_2->GetType() == OBJECT_BUILDING;
	bool isBullet2 = Obj_2->GetType() == OBJECT_BULLET;
	bool isArrow2 = Obj_2->GetType() == OBJECT_ARROW;

	// CHARACTER와 충돌들.
	if (isCharacter1 && isCharacter2)
	{
		Obj_1->SetDamage(10);
		Obj_2->SetDamage(10);
	}

	if (isCharacter1 && isBuilding2)
	{
		Obj_2->SetDamage(Obj_1->GetLife());
		Obj_1->SetLife(0);
	}

	if (isCharacter1 && isBullet2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
	}

	if (isCharacter1 && isArrow2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
	}
	// 빌딩들과 충돌
	if (isBuilding1 && isBullet2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
	}
	if (isBuilding1 && isArrow2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
	}
}

void CSceneMgr::CreateBullet(CObj *& Obj)
{
	bool isType = Obj->GetType() == OBJECT_BUILDING;
	bool isTime = Obj->GetBulletTime() > 2.f;		// 2초당 1발씩.
	if (isType && isTime)
	{
		AddActorObject(Obj->GetXpos(), Obj->GetYpos(), Obj->GetTeam(), OBJECT_BULLET);
		Obj->ReSetBulletTime();
	}
}

void CSceneMgr::CreateArrow(CObj *& Obj)
{
	bool isType = Obj->GetType() == OBJECT_CHARACTER;
	bool isTime = Obj->GetArrowTime() > 1.f;		// 1초당 1발씩.
	if (isType && isTime)
	{
		AddActorObject(Obj->GetXpos(), Obj->GetYpos(), Obj->GetTeam(), OBJECT_ARROW);
		Obj->ReSetArrowTime();
	}
}

void CSceneMgr::CreateCharacter(float elapsedTime)
{
	m_PlayerCoolTime += elapsedTime / 1000.f;
	bool isTime = m_PlayerCoolTime > 1.f;	// 2초당 1발씩.

	if (isTime)
	{
		float x = float(rand() % 400) - 180.f;
		float y = float(rand() % 350) + 50.f;
		AddActorObject(x, y, OBJECT_ENEMY, OBJECT_CHARACTER);
		m_PlayerCoolTime = 0.f;
		//m_particleTime = 0.f;
	}
}

void CSceneMgr::BackGroundRender()
{
	// 배경
	GLint m_texCharacter;

	m_texCharacter = m_Renderer->CreatePngTexture("../Resource/background.png");
	m_Renderer->DrawTexturedRect(0, 0, 0, float(Height), 1, 1, 1, 1, m_texCharacter, OBJLEVEL_BACKGROUND);
}

void CSceneMgr::TextureRender(CObj*& Obj, char* filepath)
{
	GLint m_texCharacter;
	m_texCharacter = m_Renderer->CreatePngTexture(filepath);

	m_Renderer->DrawTexturedRect(Obj->GetXpos(), Obj->GetYpos(), 0,
		Obj->GetSize(),
		1, 1, 1, 1,
		m_texCharacter,
		Obj->GetLevel()
	);
	
}

void CSceneMgr::AnimationRender(CObj *& Obj, char * filepath, int totalX)
{
	GLint m_texCharacter;
	m_texCharacter = m_Renderer->CreatePngTexture(filepath);

	m_Renderer->DrawTexturedRectSeq(Obj->GetXpos(), Obj->GetYpos(), 0,
		Obj->GetSize(),
		1, 1, 1, 1,
		m_texCharacter,
		Obj->GetAnim(), 0, totalX, 1, Obj->GetLevel()
	);
}

void CSceneMgr::ParticleRender(CObj *& Obj, float yDir, char * filepath)
{
	GLint m_texCharacter;
	m_texCharacter = m_Renderer->CreatePngTexture(filepath);

	m_Renderer->DrawParticle(Obj->GetXpos(), Obj->GetYpos(), 0
		, Obj->GetSize(), 1, 1, 1, 1, 0, yDir, m_texCharacter, m_particleTime);
}

void CSceneMgr::GaugeRender(CObj*& Obj, float r, float g, float b, float a)
{
	m_Renderer->DrawSolidRectGauge(
		Obj->GetXpos(),
		Obj->GetYpos() + (Obj->GetSize() / 2.f + 10.f),
		0,
		Obj->GetSize(),
		5,
		r, g, b, a,
		Obj->GetGauge(),
		Obj->GetLevel()
	);
}
