#include "stdafx.h"
#include "SceneMgr.h"
int CSceneMgr::Win = 0;
int CSceneMgr::Lose = 0;

CSceneMgr::CSceneMgr()
	:m_PlayerCoolTime(0), m_FlyCoolTime(0), m_BombCoolTime(0)
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
	TextureInit();

	m_Sound = new Sound();

	int soundBG = m_Sound->CreateSound("../Sound/Stage1.mp3");

	m_Sound->PlaySound(soundBG, true, 0.2f);

	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		m_Objs[i] = NULL;
	}
	// Player Building
	AddActorObject(-250, -280, TEAM_MY, OBJECT_BUILDING);
	AddActorObject(0, -300, TEAM_MY, OBJECT_KING);
	AddActorObject(250, -280, TEAM_MY, OBJECT_BUILDING);
	// Enemy Building
	AddActorObject(-250, 280, TEAM_YOUR, OBJECT_BUILDING);
	AddActorObject(0, 300, TEAM_YOUR, OBJECT_KING);
	AddActorObject(250, 280, TEAM_YOUR, OBJECT_BUILDING);

}

bool CSceneMgr::AddActorObject(float x, float y, TEAM team, OBJTYPE type)
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
	CreateGroundUnit(elapsedTime);
	CreateFlyUnit(elapsedTime);
	CreateBombUnit(elapsedTime);
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
				CreateFlyArrow(m_Objs[i]);
				
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
			if (m_Objs[i]->GetType() == OBJECT_KING)
			{
				if (m_Objs[i]->GetTeam() == TEAM_MY)
				{
					TextureRender(m_Objs[i], TEX_KING1);
				}
				else if (m_Objs[i]->GetTeam() == TEAM_YOUR)
				{
					TextureRender(m_Objs[i], TEX_KING2);
				}
			}
			else if (m_Objs[i]->GetType() == OBJECT_BUILDING)
			{
				if (m_Objs[i]->GetTeam() == TEAM_MY)
				{
					TextureRender(m_Objs[i], TEX_BUILDING1);
				}
				else if (m_Objs[i]->GetTeam() == TEAM_YOUR)
				{
					TextureRender(m_Objs[i], TEX_BUILDING2);
				}
			}
			else if (m_Objs[i]->GetType() == OBJECT_GROUNDUNIT)
			{
				if (m_Objs[i]->GetTeam() == TEAM_MY)
				{
					AnimationRender(m_Objs[i], TEX_GROUNDUNIT1, 3);
				}
				else if (m_Objs[i]->GetTeam() == TEAM_YOUR)
				{
					AnimationRender(m_Objs[i], TEX_GROUNDUNIT2, 5);
				}
			}
			else if (m_Objs[i]->GetType() == OBJECT_FLYUNIT)
			{
				if (m_Objs[i]->GetTeam() == TEAM_MY)
				{
					TextureRender(m_Objs[i], TEX_FLYUNIT1);
				}
				else if (m_Objs[i]->GetTeam() == TEAM_YOUR)
				{
					TextureRender(m_Objs[i], TEX_FLYUNIT2);
				}
			}
			else if (m_Objs[i]->GetType() == OBJECT_BOMBUNIT)
			{
				if (m_Objs[i]->GetTeam() == TEAM_MY)
				{
					TextureRender(m_Objs[i], TEX_BOMBUNIT1);
				}
				else if (m_Objs[i]->GetTeam() == TEAM_YOUR)
				{
					TextureRender(m_Objs[i], TEX_BOMBUNIT2);
				}
			}
			else if (m_Objs[i]->GetType() == OBJECT_BULLET)
			{
				if (m_Objs[i]->GetTeam() == TEAM_MY)
				{
					ParticleRender(m_Objs[i], -1, TEX_BULLET1);
				}
				else if (m_Objs[i]->GetTeam() == TEAM_YOUR)
				{
					ParticleRender(m_Objs[i], 1, TEX_BULLET2);
				}
			}
			else if (m_Objs[i]->GetType() == OBJECT_ARROW)
			{
				if (m_Objs[i]->GetTeam() == TEAM_MY)
				{
					NomalRender(m_Objs[i]);
				}
				else if (m_Objs[i]->GetTeam() == TEAM_YOUR)
				{
					NomalRender(m_Objs[i]);
				}
			}
		}
	}
	
	m_Renderer->DrawText(-400, 350, GLUT_BITMAP_TIMES_ROMAN_24, 1, 0, 0, "2012180061");

	m_Renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1f, -0.1f, m_texture[TEX_WEATHER], m_particleTime, 0.01f);
}

void CSceneMgr::Release()
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
	{
		delete m_Objs[i];
		m_Objs[i] = NULL;
	}
}

void CSceneMgr::TextureInit()
{
	m_texture[TEX_BACKGROUND] = m_Renderer->CreatePngTexture("../Resource/background.png");
	// MY_TEAM
	m_texture[TEX_KING1] = m_Renderer->CreatePngTexture("../Resource/king1.png");
	m_texture[TEX_BUILDING1] = m_Renderer->CreatePngTexture("../Resource/building1.png");
	m_texture[TEX_GROUNDUNIT1] = m_Renderer->CreatePngTexture("../Resource/player01.png");
	m_texture[TEX_FLYUNIT1] = m_Renderer->CreatePngTexture("../Resource/fly01.png");
	m_texture[TEX_BULLET1] = m_Renderer->CreatePngTexture("../Resource/particle05.png");
	m_texture[TEX_FLYARROW1] = m_Renderer->CreatePngTexture("../Resource/particle05.png");
	m_texture[TEX_BOMBUNIT1] = m_Renderer->CreatePngTexture("../Resource/bomb1.png");


	// YOUR_TEAM
	m_texture[TEX_KING2] = m_Renderer->CreatePngTexture("../Resource/king2.png");
	m_texture[TEX_BUILDING2] = m_Renderer->CreatePngTexture("../Resource/building2.png");
	m_texture[TEX_GROUNDUNIT2] = m_Renderer->CreatePngTexture("../Resource/enemy01.png");
	m_texture[TEX_FLYUNIT2] = m_Renderer->CreatePngTexture("../Resource/fly02.png");
	m_texture[TEX_BULLET2] = m_Renderer->CreatePngTexture("../Resource/particle06.png");
	m_texture[TEX_BOMBUNIT2] = m_Renderer->CreatePngTexture("../Resource/bomb2.png");


	// 날씨 파티클
	m_texture[TEX_WEATHER] = m_Renderer->CreatePngTexture("../Resource/particle04.png");
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
	bool isCharacter1 = Obj_1->GetType() == OBJECT_GROUNDUNIT;
	bool isKing1 = Obj_1->GetType() == OBJECT_KING;
	bool isBuilding1 = Obj_1->GetType() == OBJECT_BUILDING;
	bool isBullet1 = Obj_1->GetType() == OBJECT_BULLET;
	bool isArrow1 = Obj_1->GetType() == OBJECT_ARROW;
	bool isFly1 = Obj_1->GetType() == OBJECT_FLYUNIT;
	bool isBomb1 = Obj_1->GetType() == OBJECT_BOMBUNIT;

	bool isCharacter2 = Obj_2->GetType() == OBJECT_GROUNDUNIT;
	bool isKing2 = Obj_2->GetType() == OBJECT_KING;
	bool isBuilding2 = Obj_2->GetType() == OBJECT_BUILDING;
	bool isBullet2 = Obj_2->GetType() == OBJECT_BULLET;
	bool isArrow2 = Obj_2->GetType() == OBJECT_ARROW;
	bool isFly2 = Obj_2->GetType() == OBJECT_FLYUNIT;
	bool isBomb2 = Obj_2->GetType() == OBJECT_BOMBUNIT;


	// CHARACTER와 충돌들.
	if (isCharacter1 && isCharacter2)
	{
		Obj_1->SetDamage(10);
		Obj_2->SetDamage(10);
	}
	if (isFly1 && isFly2)
	{
		Obj_1->SetDamage(5);
		Obj_2->SetDamage(5);
	}
	if (isCharacter1 && isKing2)
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

	if (isFly1 && isBullet2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
	}

	if (isFly1 && isArrow2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
	}
	if (isBomb1 && isFly2)
	{
		Obj_1->SetDamage(1);
	}
	if (isBomb1 && isBullet2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
	}
	if (isBomb1 && isArrow2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
	}
	// 킹 빌딩들과 충돌
	if (isKing1 && isBullet2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
	}
	if (isKing1 && isArrow2)
	{
		Obj_1->SetDamage(Obj_2->GetLife());
		Obj_2->SetLife(0);
	}
	if (isKing1 && isBomb2)
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
	if (isBuilding1 && isBomb2)
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

	isType = Obj->GetType() == OBJECT_KING;
	isTime = Obj->GetBulletTime() > 3.f;		// 2초당 1발씩.
	if (isType && isTime)
	{
		AddActorObject(Obj->GetXpos(), Obj->GetYpos(), Obj->GetTeam(), OBJECT_BULLET);
		AddActorObject(Obj->GetXpos(), Obj->GetYpos(), Obj->GetTeam(), OBJECT_BULLET);
		Obj->ReSetBulletTime();
	}
}

void CSceneMgr::CreateGroundUnit(float elapsedTime)
{
	m_PlayerCoolTime += elapsedTime / 1000.f;
	bool isTime = m_PlayerCoolTime > 2.f;	// 2초당 1발씩.

	if (isTime)
	{
		float x = float(rand() % 400) - 180.f;
		float y = float(rand() % 350) + 50.f;
		AddActorObject(x, y, TEAM_YOUR, OBJECT_GROUNDUNIT);
		m_PlayerCoolTime = 0.f;
		//m_particleTime = 0.f;
	}
}

void CSceneMgr::CreateFlyUnit(float elapsedTime)
{
	m_FlyCoolTime += elapsedTime / 1000.f;
	bool isTime = m_FlyCoolTime > 5.f;	// 2초당 1발씩.

	if (isTime)
	{
		{
			float x = float(rand() % 400) - 180.f;
			float y = float(rand() % 350) + 50.f;
			AddActorObject(x, y, TEAM_YOUR, OBJECT_FLYUNIT);
		}
		{
			float x = float(rand() % 400) - 180.f;
			float y = float(rand() % 350) - 400.f;
			AddActorObject(x, y, TEAM_MY, OBJECT_FLYUNIT);
		}
		
		m_FlyCoolTime = 0.f;
		//m_particleTime = 0.f;
	}
}

void CSceneMgr::CreateBombUnit(float elapsedTime)
{
	m_BombCoolTime += elapsedTime / 1000.f;
	bool isTime = m_BombCoolTime > 5.f;	// 2초당 1발씩.

	if (isTime)
	{
		{
			float x = float(rand() % 400) - 180.f;
			float y = float(rand() % 350) + 50.f;
			AddActorObject(x, y, TEAM_YOUR, OBJECT_BOMBUNIT);
		}
		{
			float x = float(rand() % 400) - 180.f;
			float y = float(rand() % 350) - 400.f;
			AddActorObject(x, y, TEAM_MY, OBJECT_BOMBUNIT);
		}

		m_BombCoolTime = 0.f;
	}
}

void CSceneMgr::CreateArrow(CObj *& Obj)
{
	bool isType = Obj->GetType() == OBJECT_GROUNDUNIT;
	bool isTime = Obj->GetArrowTime() > 1.f;		// 1초당 1발씩.
	if (isType && isTime)
	{
		AddActorObject(Obj->GetXpos(), Obj->GetYpos(), Obj->GetTeam(), OBJECT_ARROW);
		Obj->ReSetArrowTime();
	}
}

void CSceneMgr::CreateFlyArrow(CObj *& Obj)
{
	bool isType = Obj->GetType() == OBJECT_FLYUNIT;
	bool isTime = Obj->GetArrowTime() > 2.f;		// 1초당 1발씩.
	if (isType && isTime)
	{
		AddActorObject(Obj->GetXpos(), Obj->GetYpos(), Obj->GetTeam(), OBJECT_ARROW);
		AddActorObject(Obj->GetXpos(), Obj->GetYpos(), Obj->GetTeam(), OBJECT_ARROW);
		AddActorObject(Obj->GetXpos(), Obj->GetYpos(), Obj->GetTeam(), OBJECT_ARROW);
		Obj->ReSetArrowTime();
	}
}

void CSceneMgr::BackGroundRender()
{
	m_Renderer->DrawTexturedRect(0, 0, 0, float(Height), 1, 1, 1, 1, m_texture[TEX_BACKGROUND], OBJLEVEL_BACKGROUND);
}

void CSceneMgr::TextureRender(CObj*& Obj, GLuint num)
{
	m_Renderer->DrawTexturedRect(Obj->GetXpos(), Obj->GetYpos(), 0,
		Obj->GetSize(),
		1, 1, 1, 1,
		m_texture[num],
		Obj->GetLevel()
	);
	GaugeRender(Obj, 1, 0, 0, 1);
}

void CSceneMgr::AnimationRender(CObj *& Obj, GLuint num, int totalX)
{
	m_Renderer->DrawTexturedRectSeq(Obj->GetXpos(), Obj->GetYpos(), 0,
		Obj->GetSize(),
		1, 1, 1, 1,
		m_texture[num],
		Obj->GetAnim(), 0, totalX, 1, Obj->GetLevel()
	);
	GaugeRender(Obj, 1, 0, 0, 1);
}

void CSceneMgr::ParticleRender(CObj *& Obj, float yDir, GLuint num)
{
	m_Renderer->DrawParticle(Obj->GetXpos(), Obj->GetYpos(), 0
		, Obj->GetSize(), 1, 1, 1, 1, (Obj->GetPaticleDirX() * Obj->GetPaticleTime()), (Obj->GetPaticleDir() * Obj->GetPaticleTime()), m_texture[num], Obj->GetPaticleTime(),0.9f);
}

void CSceneMgr::NomalRender(CObj *& Obj)
{
	m_Renderer->DrawSolidRect(
		Obj->GetXpos(), Obj->GetYpos(),
		0, Obj->GetSize(),
		Obj->GetcolorR(),
		Obj->GetcolorG(),
		Obj->GetcolorB(),
		Obj->GetcolorA(),
		Obj->GetLevel());
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
