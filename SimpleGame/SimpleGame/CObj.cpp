#include "stdafx.h"
#include "CObj.h"


CObj::CObj()
{
}

CObj::CObj(float x, float y, OBJTYPE team, OBJTYPE type)
	:xPos(x),yPos(y),m_team(team),m_type(type)
{

	m_bulletTime = 10.f;
	m_arrowTime = 0.f;
	// 객체 속도와 방향을 랜덤값으로 만든다. 교수님 코드 참조. RAND_MAX는 rand()의 MAX값.
	// -0.5를 해주는 이유는 양수와 음수를 만든다. (rand()/RAND_MAX = 0~1사이의 값)
	if (team == OBJECT_PLAYER)
	{
		switch (type)
		{
		case OBJECT_CHARACTER:
			colR = colG = 0.f; colB = colA = 1.f;
			m_size = 10.f;
			m_life = 10;
			speedX = 300.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
			speedY = 300.f * (((float)rand() / (float)RAND_MAX));
			break;
		case OBJECT_BUILDING:
			m_size = 100.f;
			m_life = 500;
			speedX = 0.f;
			speedY = 0.f;
			break;
		case OBJECT_BULLET:
			colR = colG = 0.f; colB = colA = 1.f;
			m_size = 5.f;
			m_life = 20;
			speedX = 600.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
			speedY = 600.f;
			break;
		case OBJECT_ARROW:
			colR = colG = colA = 1.f; colB = 0.f;
			m_size = 5.f;
			m_life = 10;
			speedX = 600.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
			speedY = 600.f * (float(rand() % 2) - 0.5f);
			break;
		}
	}
	else if (team == OBJECT_ENEMY)
	{
		switch (type)
		{
		case OBJECT_CHARACTER: 
			colR = colA = 1.f; colG = colB = 0.f;
			m_size = 10.f;
			m_life = 10;
			speedX = 300.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
			speedY = 300.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
			break;
		case OBJECT_BUILDING:
			m_size = 100.f;
			m_life = 500;
			speedX = 0.f;
			speedY = 0.f;
			break;
		case OBJECT_BULLET:
			colR = colA = 1.f; colG = colB = 0.f;
			m_size = 5.f;
			m_life = 20;
			speedX = 600.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
			speedY = -600.f; 
			break;
		case OBJECT_ARROW:
			colR = 0.5f, colG = 0.2f, colB = 0.7f, colA = 1.f;
			m_size = 5.f;
			m_life = 10;
			speedX = 600.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
			speedY = 600.f * (float(rand() % 2) - 0.5f); 
			break;
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
