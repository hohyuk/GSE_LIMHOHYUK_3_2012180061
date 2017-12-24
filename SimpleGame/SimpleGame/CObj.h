#pragma once
class CObj
{
public:
	CObj();
	CObj(float x, float y, TEAM team, OBJTYPE type);
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
	TEAM GetTeam() { return m_team; }
	OBJTYPE GetType() { return m_type; }
	void SetColor(float r, float g, float b, float a) { colR = r, colG = g, colB = b, colA = a; }
	void SetLife(float life) { m_life = life; }
	void SetDamage(float damage) { m_life -= damage; m_gauge = m_life / m_FullLife; }
	// Ÿ��
	float GetBulletTime() { return m_bulletTime; }
	void ReSetBulletTime() { m_bulletTime = 0.f; }
	float GetArrowTime() { return m_arrowTime; }
	void ReSetArrowTime() { m_arrowTime = 0.f; }

	// �켱���� ������
	float GetLevel() { return m_level; }

	// ������ 
	float GetGauge() { return m_gauge; }
	// �ִϸ��̼�
	int GetAnim() { return m_anim; }
	void Update(float elapsedTime);
	// ��ƼŬ Ÿ��
	float GetPaticleTime() { return m_paticleTime; }
	float GetPaticleDirX() { return m_paticleDirX; }
	float GetPaticleDir() { return m_paticleDir; }
private:
	void moveObjs();
	void areaOut();
private:
	float xPos, yPos, m_size;
	float colR, colG, colB, colA;
	float speedX, speedY;
	float m_FullLife;
	float m_life;
	float m_lifeTime;
	TEAM m_team;
	OBJTYPE m_type;
	float m_level;
	float m_gauge;
	float m_bulletTime;
	float m_arrowTime;
	float ElapsedTimeSecond;
	int m_anim;

	// ��ƼŬ Ÿ��
	float m_paticleTime;
	float m_paticleDir;
	float m_paticleDirX;
};

