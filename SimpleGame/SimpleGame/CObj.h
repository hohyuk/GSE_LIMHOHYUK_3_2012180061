#pragma once
class CObj
{
public:
	CObj();
	CObj(float x, float y, OBJTYPE type);
	~CObj();

	float GetXpos() { return xPos; }
	float GetYpos() { return yPos; }
	float GetSize() { return size; }
	float GetcolorR() { return colR; }
	float GetcolorG() { return colG; }
	float GetcolorB() { return colB; }
	float GetLife() { return m_life; }
	float GetLifeTime() { return m_lifeTime; }
	OBJTYPE GetType() { return m_type; }
	void SetColor(float r, float g, float b) { colR = r, colG = g, colB = b; }
	void SetLife(float life) { m_life -= life; }

	void AddActorObject(float xpos, float ypos, OBJTYPE type);
	void Update(float elapsedTime);

private:
	void objmove();
	void lifetime();
private:
	float xPos, yPos, size;
	float colR, colG, colB;
	float speedX, speedY;
	float m_life;
	float m_lifeTime;
	OBJTYPE m_type;
	float ElapsedTime;
};

