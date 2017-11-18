#pragma once
class CObj
{
public:
	CObj();
	CObj(float x, float y, OBJTYPE team, OBJTYPE type);
	~CObj();

	float GetXpos() { return xPos; }
	float GetYpos() { return yPos; }
	float GetSize() { return m_size; }
	float GetcolorR() { return colR; }
	float GetcolorG() { return colG; }
	float GetcolorB() { return colB; }
	float GetcolorA() { return colA; }

	float GetLife() { return m_life; }
	float GetLifeTime() { return m_lifeTime; }
	OBJTYPE GetTeam() { return m_team; }
	OBJTYPE GetType() { return m_type; }
	void SetColor(float r, float g, float b, float a) { colR = r, colG = g, colB = b, colA = a; }
	void SetLife(float life) { m_life = life; }
	void SetDamage(float damage) { m_life -= damage; }
	// е╦юс
	float GetBulletTime() { return m_bulletTime; }
	void ReSetBulletTime() { m_bulletTime = 0.f; }
	float GetArrowTime() { return m_arrowTime; }
	void ReSetArrowTime() { m_arrowTime = 0.f; }

	void Update(float elapsedTime);
private:
	void moveObjs();
	void areaOut();
private:
	float xPos, yPos, m_size;
	float colR, colG, colB, colA;
	float speedX, speedY;
	float m_life;
	float m_lifeTime;
	OBJTYPE m_team;
	OBJTYPE m_type;
	
	float m_bulletTime;
	float m_arrowTime;
	float ElapsedTimeSecond;
};

