#pragma once

// È­¸é 
const int Width = 500;
const int Height = 800;
// °´Ã¼ °¹¼ö
const int MAX_OBJ_COUNT{ 100 };
const int MAX_ARROW_COUNT{ 100 };

// ¸¶¿ì½º Å¬¸¯ ÄðÅ¸ÀÓ
const float COOLTIME{ 7.f };
enum OBJTYPE
{
	OBJECT_PLAYER,
	OBJECT_ENEMY,
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW
};