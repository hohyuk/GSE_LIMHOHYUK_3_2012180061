#pragma once

// ȭ�� 
const int Width = 500;
const int Height = 800;
// ��ü ����
const int MAX_OBJ_COUNT{ 100 };
const int MAX_ARROW_COUNT{ 100 };

// ���콺 Ŭ�� ��Ÿ��
const float COOLTIME{ 2.f };

enum OBJTYPE
{
	OBJECT_PLAYER,
	OBJECT_ENEMY,
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW
};

#define OBJRANK_BUILDING 0.1f
#define OBJRANK_CHARACTER 0.2f
#define OBJRANK_BULLET 0.3f
#define OBJRANK_ARROW 0.3f