#pragma once
#include "Stage.h"
class Stage_01 :
	public Stage
{
private:
	HDC m_BackDC;
	HDC m_CoverDC;

private:
	void LoadMap();
	

private:
	void SetColPair();
	void CreatePlayer();
	void CreateSpring();
	void KeyCheck();

public:
	virtual void enter();
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();

public:
	Stage_01();
	virtual ~Stage_01();
};

