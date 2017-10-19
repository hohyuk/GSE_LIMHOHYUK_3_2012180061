#include "stdafx.h"
#include "CObj.h"


CObj::CObj()
{
}


CObj::~CObj()
{
}

void CObj::Initialize()
{
	xPos = 0;
	yPos = 0;
	zPos = 0;
	size = 10;
	/*colR = float(rand() % 255) / 255.f;
	colG = float(rand() % 255) / 255.f;
	colB = float(rand() % 255) / 255.f;*/
	colR = 1.f;
	colG = 1.f;
	colB = 1.f;
	speed = 5.f;
	int random = rand() % 4;
	if (random==0)
	{
		moveX = speed;
		moveY = speed;
	}
	else if(random==1)
	{
		moveX = -speed;
		moveY = -speed;
	}
	else if (random == 2)
	{
		moveX = speed;
		moveY = -speed;
	}
	else if (random == 3)
	{
		moveX = -speed;
		moveY = speed;
	}
	
	b_Draw = false;
}

void CObj::Update()
{
	if (xPos > 250)
	{
		moveX = -speed;
	}
	else if (xPos < -250)
	{
		moveX = speed;
	}
	if (yPos > 250)
	{
		moveY = -speed;
	}
	else if (yPos < -250)
	{
		moveY = speed;
	}
		
	xPos += moveX * 0.016f;
	yPos += moveY * 0.016f;
}
