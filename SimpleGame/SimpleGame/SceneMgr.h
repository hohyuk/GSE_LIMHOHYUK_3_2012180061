#pragma once
#include "Renderer.h"
#include "CObj.h"

const int MAX_OBJ_COUNT{ 50 };
const int MAX_ARROW_COUNT{ 100 };
class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

	void Init();
	void Update(float elapsedTime);
	void CreateObj(int x, int y);
	void Render();
	void Release();

private:
	bool Collision(float x1, float y1, float x2, float y2, float size1, float size2);
	void CharacterCollision();
	void BuildingCollision(CObj* &obj);
	void CreateBullet(float elapsedTime);
	void CreateArrow(float elapsedTime);
	void BulletCollision();
	void Character_render();
	void Building_render();
	void Bullet_render();
	void Arrow_render();
private:
	Renderer* m_Renderer;

	CObj* m_Obj[MAX_OBJ_COUNT];
	CObj* m_Bullet[MAX_OBJ_COUNT];
	CObj* m_Building;
	CObj* m_Arrow[MAX_OBJ_COUNT][MAX_ARROW_COUNT];
	int obj_count;
	int bullet_count;
	float bullet_time;
	int arrowCount;
	float arrowTime;
};

