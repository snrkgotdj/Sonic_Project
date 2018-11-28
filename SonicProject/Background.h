#pragma once

class Texture;
class Animator;
class Box;

class Background
{
private:
	float m_fAccTime;
	float positionY;

public:
	Texture* BackTex;
	Texture* LogoWing;
	Texture * pTex;
	Animator* Charactor;

public:
	void init();
	void render(HDC _dc);
	void update();
	void Clear();
public:
	Background();
	~Background();
};

