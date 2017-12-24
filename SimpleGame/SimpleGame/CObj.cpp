#include "stdafx.h"
#include "CObj.h"


CObj::CObj()
{
}

CObj::CObj(float x, float y, TEAM team, OBJTYPE type)
	:xPos(x),yPos(y),m_team(team),m_type(type)
{

	m_bulletTime = 10.f;
	m_arrowTime = 0.f;
	// 객체 속도와 방향을 랜덤값으로 만든다. 교수님 코드 참조. RAND_MAX는 rand()의 MAX값.
	// -0.5를 해주는 이유는 양수와 음수를 만든다. (rand()/RAND_MAX = 0~1사이의 값)

	if (m_type == OBJECT_KING)
	{
		m_size = 150.f;
		m_FullLife = m_life = 2500;
		speedX = 0.f;
		speedY = 0.f;
		m_level = OBJLEVEL_BUILDING;
		m_gauge = 1.f;
	}
	else if (m_type == OBJECT_BUILDING)
	{
		m_size = 100.f;
		m_FullLife = m_life = 1500;
		speedX = 0.f;
		speedY = 0.f;
		m_level = OBJLEVEL_BUILDING;
		m_gauge = 1.f;
	}
	else if (m_type == OBJECT_GROUNDUNIT)
	{
		m_size = 50.f;
		m_FullLife = m_life = 100;
		speedX = 300.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
		if (m_team == TEAM_MY)
		{
			speedY = 100.f * (((float)rand() / (float)RAND_MAX));
		}
		else if (m_team == TEAM_YOUR)
		{
			speedY = -100.f * (((float)rand() / (float)RAND_MAX));
		}
		m_level = OBJLEVEL_CHARACTER;
		m_gauge = 1.f;
		m_anim = 0;
	}
	else if (m_type == OBJECT_FLYUNIT)
	{
		m_size = 50.f;
		m_FullLife = m_life = 150;
		speedX = 100.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
		if (m_team == TEAM_MY)
		{
			speedY = 100.f * (((float)rand() / (float)RAND_MAX));
		}
		else if (m_team == TEAM_YOUR)
		{
			speedY = -100.f * (((float)rand() / (float)RAND_MAX));
		}
		m_level = OBJLEVEL_FLY;
		m_gauge = 1.f;
	}
	else if (m_type == OBJECT_BOMBUNIT)
	{
		m_size = 50.f;
		m_FullLife = m_life = 200;
		speedX = 300.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
		m_level = OBJLEVEL_BOMB;
		m_gauge = 1.f;
		if (m_team == TEAM_MY)
		{
			speedY = 500.f * (((float)rand() / (float)RAND_MAX));
		}
		else if (m_team == TEAM_YOUR)
		{
			speedY = -500.f * (((float)rand() / (float)RAND_MAX));
		}
	}
	else if (m_type == OBJECT_BULLET)
	{
		m_size = 15.f;
		m_life = 15;
		float random = (((float)rand() / (float)RAND_MAX) - 0.5f);
		speedX = 300.f * random;
		m_level = OBJLEVEL_BULLET;
		m_paticleTime = 0.f;
		if (m_team == TEAM_MY)
		{
			speedY = 300.f;
			m_paticleDir = -1.f;
			if (speedX > 0)
				m_paticleDirX = -1.f * random;
			else
				m_paticleDirX = -1.f * random;
		}
		else if (m_team == TEAM_YOUR)
		{
			speedY = -300.f;
			m_paticleDir = 1.f;
			if (speedX > 0)
				m_paticleDirX = -1.f * random;
			else
				m_paticleDirX = -1.f * random;
		}
	}
	else if (m_type == OBJECT_ARROW)
	{
		m_size = 5.f;
		m_life = 10;
		speedX = 600.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
		speedY = 600.f * (float(rand() % 2) - 0.5f);
		m_level = OBJLEVEL_ARROW;
		if (m_team == TEAM_MY)
		{
			colR = colG = colA = 1.f; colB = 0.f;
		}
		else if (m_team == TEAM_YOUR)
		{
			colR = 0.5f, colG = 0.2f, colB = 0.7f, colA = 1.f;
		}
	}
}

CObj::~CObj()
{
}

void CObj::Update(float elapsedTime)
{
	ElapsedTimeSecond = elapsedTime / 1000.f;
	m_bulletTime += ElapsedTimeSecond;
	m_arrowTime += ElapsedTimeSecond;
	m_paticleTime += ElapsedTimeSecond;
	
	// anim
	m_anim = (m_anim + 1) % 5;
	
	moveObjs();
}

void CObj::moveObjs()
{
	if (xPos > Width / 2)
	{
		areaOut();
		speedX = -speedX;
	}
	if (xPos < -Width / 2)
	{
		areaOut();
		speedX = -speedX;
	}
	if (yPos > Height / 2)
	{
		areaOut();
		speedY = -speedY;
	}
	if (yPos < -Height / 2)
	{
		areaOut();
		speedY = -speedY;
	}
	// ElapsedTime / 1000.f -> 0.01sec
	xPos += speedX * ElapsedTimeSecond;
	yPos += speedY * ElapsedTimeSecond;
}

void CObj::areaOut()
{
	if (m_type == OBJECT_BULLET || m_type == OBJECT_ARROW)
		m_life = 0.f;
}
