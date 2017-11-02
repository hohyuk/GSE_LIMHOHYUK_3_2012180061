#pragma once
class CObj
{
public:
	CObj();
	CObj(float x, float y);
	~CObj();

	float GetXpos() { return xPos; }
	float GetYpos() { return yPos; }
	float GetZpos() { return zPos; }
	float GetSize() { return size; }
	float GetcolorR() { return colR; }
	float GetcolorG() { return colG; }
	float GetcolorB() { return colB; }
	float GetLife() { return m_life; }
	float GetLifeTime() { return m_lifeTime; }

	void SetPos(float x, float y) { xPos = x, yPos = y; }
	void SetColor(float r, float g, float b) { colR = r, colG = g, colB = b; }
	void SetLife(float life) { m_life -= life; }
	

	void Initialize();
	void Update(float elapsedTime);
	
	void AddActorObject(float xpos, float ypos, OBJTYPE type);
private:
	void moveobject(float elapsedTime);
	void lifetime(float elapsedTime);

private:
	float xPos, yPos, zPos;
	float colR, colG, colB;
	float size;
	float moveX, moveY;
	float speedX, speedY;
	float m_life;
	float m_lifeTime;
	float attack;
};

