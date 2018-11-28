#pragma once
#include "Stage.h"
class Stage_00 :
	public Stage
{
private:
	HDC m_BackDC;
	HDC m_LightDC;

private:
	bool m_bRenderChange;
	float m_fAccRender;

	bool m_bStageFinish;
	
private:
	void LoadMap();

private:
	void RanderChange();
	void SetColPair();
	void CreatePlayer();	
	void KeyCheck();
	void CreateBoss();
	void CreateOBJ();


public:
	virtual void enter();
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();

public:
	Stage_00();
	virtual ~Stage_00();
};

