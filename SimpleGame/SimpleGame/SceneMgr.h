#pragma once
#include "Renderer.h"
#include "CObj.h"

class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

	void Init();
	bool AddActorObject(float x, float y, OBJTYPE team, OBJTYPE type);
	void Update(float elapsedTime);
	void Render();
	void Release();

private:
	bool CollisionObjs(CObj* & Obj_1, CObj* & Obj_2);
	void CollisionCompare();
	bool ObjTypeCompare(CObj* & Obj_1, CObj* & Obj_2);
	void ObjTypeCollision(CObj* & Obj_1, CObj* & Obj_2);
	void CreateBullet(CObj*& Obj);
	void CreateArrow(CObj*& Obj);
	void CreateCharacter(float elapsedTime);

	void TextureRender(CObj*& Obj, OBJTYPE type, char* filepath);
	void AnimationRender(CObj*& Obj, OBJTYPE type, char* filepath);
	void ParticleRender(CObj*& Obj,float yDir, char* filepath);
	void GaugeRender(CObj*& Obj, float r, float g, float b, float a);
private:
	Renderer* m_Renderer;
	CObj* m_Objs[MAX_OBJ_COUNT];
	GLfloat m_characterTime;
	GLfloat m_particleTime;
};