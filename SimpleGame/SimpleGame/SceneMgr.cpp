#include "stdafx.h"
#include "SceneMgr.h"

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

	// Enemy Character cooltime
	m_characterTime = 5.f;
}

bool CSceneMgr::AddActorObject(float x, float y, OBJTYPE team, OBJTYPE type)
{
	// Objs의 NULL값을 찾고 NULL값에 객체를 저장한다.
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		if (m_Objs[i] == NULL)
		{
			m_Objs[i] = new CObj(x, y, team, type);
			if (m_Objs[i]->GetType() == OBJECT_CHARACTER)
				cout << "x : " << x << " , " << "y : " << y << endl;
			return true;
		}
	}
	cout << "CHARACTER FULL." << endl;
	return false;
}

void CSceneMgr::Update(float elapsedTime)
{
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
	for (int i = 0; i < MAX_OBJ_COUNT; i++)
	{
		if (m_Objs[i] != NULL)
		{
			m_Renderer->DrawSolidRect(
				m_Objs[i]->GetXpos(),
				m_Objs[i]->GetYpos(),
				0,
				m_Objs[i]->GetSize(),
				m_Objs[i]->GetcolorR(),
				m_Objs[i]->GetcolorG(),
				m_Objs[i]->GetcolorB(),
				m_Objs[i]->GetcolorA()
			);
			// Building Obj
			if (m_Objs[i]->GetType() == OBJECT_BUILDING)
			{
				GLint m_texCharacter;

				if (m_Objs[i]->GetTeam() == OBJECT_PLAYER)
					m_texCharacter = m_Renderer->CreatePngTexture("../Resource/building1.png");
				else if (m_Objs[i]->GetTeam() == OBJECT_ENEMY)
					m_texCharacter = m_Renderer->CreatePngTexture("../Resource/building2.png");

				m_Renderer->DrawTexturedRect(
					m_Objs[i]->GetXpos(),
					m_Objs[i]->GetYpos(),
					0,
					m_Objs[i]->GetSize(),
					m_Objs[i]->GetcolorR(),
					m_Objs[i]->GetcolorG(),
					m_Objs[i]->GetcolorB(),
					m_Objs[i]->GetcolorA(),
					m_texCharacter);
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

	// character 구별
	bool isCharacter = Obj_1->GetType() == OBJECT_CHARACTER;
	bool isCompare = Obj_1->GetType() == Obj_2->GetType();
	bool isSame = isCharacter && isCompare;

	// Building and Bullet 충돌
	ObjTypeCollision(Obj_1, Obj_2);
	ObjTypeCollision(Obj_2, Obj_1);

	if (isSame)
		return false;

	return true;
}

bool CSceneMgr::ObjTypeCollision(CObj *& Obj_1, CObj *& Obj_2)
{
	// character 구별
	bool isCharacter1 = Obj_1->GetType() == OBJECT_CHARACTER;
	bool isBuilding1 = Obj_1->GetType() == OBJECT_BUILDING;
	bool isBullet1 = Obj_1->GetType() == OBJECT_BULLET;
	bool isArrow1 = Obj_1->GetType() == OBJECT_BULLET;

	bool isCharacter2 = Obj_2->GetType() == OBJECT_CHARACTER;
	bool isBuilding2 = Obj_2->GetType() == OBJECT_BUILDING;
	bool isBullet2 = Obj_2->GetType() == OBJECT_BULLET;
	bool isArrow2 = Obj_2->GetType() == OBJECT_BULLET;

	if (isCharacter1 && isBuilding2)
	{
		Obj_2->SetDamage(Obj_1->GetLife());
		Obj_1->SetLife(0);
		return true;
	}

	if (isCharacter1 && isBullet2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
		return true;
	}

	if (isCharacter1 && isCharacter2)
	{
		Obj_1->SetDamage(10);
		Obj_2->SetDamage(10);
		cout << "a" << endl;
	}
	return false;
}

void CSceneMgr::CreateBullet(CObj *& Obj)
{
	bool isType = Obj->GetType() == OBJECT_BUILDING;
	bool isTime = Obj->GetBulletTime() > 10.f;		// 10초당 1발씩.
	if (isType && isTime)
	{
		AddActorObject(Obj->GetXpos(), Obj->GetYpos(), Obj->GetTeam(), OBJECT_BULLET);
		Obj->ReSetBulletTime();
	}
}

void CSceneMgr::CreateCharacter(float elapsedTime)
{
	m_characterTime += elapsedTime / 1000.f;
	bool isTime = m_characterTime > 5.f;	// 5초당 1발씩.

	if (isTime)
	{
		float x = float(rand() % 400) - 180.f;
		float y = float(rand() % 350) + 50.f;
		AddActorObject(x, y, OBJECT_ENEMY, OBJECT_CHARACTER);
		m_characterTime = 0.f;
	}
}

