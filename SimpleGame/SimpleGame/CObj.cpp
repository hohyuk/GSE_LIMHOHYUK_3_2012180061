#include "stdafx.h"
#include "CObj.h"


CObj::CObj()
{
}

CObj::CObj(float x, float y, OBJTYPE type)
{
	AddActorObject(x, y, type);
}


CObj::~CObj()
{
}

void CObj::AddActorObject(float xpos, float ypos, OBJTYPE type)
{
	xPos = xpos;
	yPos = ypos;
	m_type = type;
	switch (type)
	{
	case OBJECT_CHARACTER:
		size = 10;
		colR = colG = colB = 1.f;
		// ��ü �ӵ��� ������ ���������� �����. ������ �ڵ� ����. RAND_MAX�� rand()�� MAX��.
		// -0.5�� ���ִ� ������ ����� ������ �����. (rand()/RAND_MAX = 0~1������ ��)
		speedX = 300.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
		speedY = 300.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
		m_life = 30;
		m_lifeTime = 6.f;			// ����ð� 6��.
		break;
	case OBJECT_BUILDING:
		size = 50;
		colR = colG = 1.f;
		colB = 0.f;
		speedX = speedY = 0;
		m_life = 50;
		break;
	case OBJECT_BULLET:
		size = 5;
		colR = 1.f;
		colG = colB = 0.f;
		speedX = 300.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
		speedY = 300.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
		m_life = 20;
		break;
	case OBJECT_ARROW:
		size = 5;
		colG = 1.f;
		colR = colB = 0.f;
		speedX = 100.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
		speedY = 100.f * (((float)rand() / (float)RAND_MAX) - 0.5f);
		m_life = 10;
		break;
	}
}

void CObj::Update(float elapsedTime)
{
	ElapsedTime = elapsedTime;
	objmove();
	lifetime();
}

void CObj::objmove()
{
	// ElapsedTime / 1000.f -> 0.01sec
	xPos += speedX * (ElapsedTime / 1000.f);
	yPos += speedY * (ElapsedTime / 1000.f);
	if (m_type == OBJECT_CHARACTER)
	{
		if (xPos > Width / 2)
		{
			speedX = -speedX;
		}
		else if (xPos < -Width / 2)
		{
			speedX = -speedX;
		}
		if (yPos > Height / 2)
		{
			speedY = -speedY;
		}
		else if (yPos < -Height / 2)
		{
			speedY = -speedY;
		}
	}
}

void CObj::lifetime()
{
	if (m_lifeTime > 0.f)
	{
		m_lifeTime -= (ElapsedTime / 1000.f);
	}
}