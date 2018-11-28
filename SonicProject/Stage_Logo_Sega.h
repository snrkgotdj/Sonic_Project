#pragma once
#include "Stage.h"

class Animator;

class Stage_Logo_Sega :
	public Stage
{
private:
	Animator* pAnim;
	float m_fAccTime;

public:
	virtual void enter();
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();

public:
	Stage_Logo_Sega();
	virtual ~Stage_Logo_Sega();
};

