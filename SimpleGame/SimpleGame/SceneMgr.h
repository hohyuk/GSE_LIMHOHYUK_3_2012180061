#pragma once
class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

	void Init();
	void Render();
	void Update();
	void Mouse(int x,int y);
	bool BoxBoxCollision(float minX1, float minY1, float maxX1, float maxY1, float minX2, float minY2, float maxX2, float maxY2);
	void Release();
};

