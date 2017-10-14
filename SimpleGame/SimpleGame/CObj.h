#pragma once
class CObj
{
public:
	CObj();
	~CObj();

	float GetXpos() { return xPos; }
	float GetYpos() { return yPos; }
	float GetZpos() { return zPos; }
	float GetSize() { return size; }
	float GetcolorR() { return colR; }
	float GetcolorG() { return colG; }
	float GetcolorB() { return colB; }
	bool GetDraw() { return b_Draw; }
	void SetDraw(bool draw) { b_Draw = draw; }
	void SetPos(float x, float y) { xPos = x, yPos = y; }
	void Initialize();
	void Update();
private:
	float xPos, yPos, zPos;
	float colR, colG, colB;
	float size;
	float moveX, moveY;
	bool b_Draw;
};

