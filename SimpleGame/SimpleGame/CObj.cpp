#include "stdafx.h"
#include "CObj.h"

CObj::CObj()
{
}

CObj::CObj(float x, float y)
	:xPos(x),yPos(y)
{
	Initialize();
}

CObj::~CObj()
{
}

void CObj::Initialize()
{
	size = 10;
	colR = colG = colB = 1.f;
	speedX = 300.f* (((float)rand() / (float)RAND_MAX) - 0.5f);
	speedY = 300.f* (((float)rand() / (float)RAND_MAX) - 0.5f);

	m_life = 3;		// ¸ñ¼û 3°³
	m_lifeTime = 10.f;
}

void CObj::Update(float elapsedTime)
{
	moveobject(elapsedTime);
	lifetime(elapsedTime);
}

void CObj::moveobject(float elapsedTime)
{
	if (xPos > 250)
	{
		speedX = -speedX;
	}
	else if (xPos < -250)
	{
		speedX = -speedX;
	}
	if (yPos > 250)
	{
		speedY = -speedY;
	}
	else if (yPos < -250)
	{
		speedY = -speedY;
	}

	xPos += speedX * elapsedTime / 1000.f;
	yPos += speedY * elapsedTime / 1000.f;
}

void CObj::lifetime(float elapsedTime)
{
	m_lifeTime -= elapsedTime / 1000.f;
	//m_life -= attack;
}
