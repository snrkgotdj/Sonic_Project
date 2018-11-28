#pragma once
#include "UI.h"
class UI_Pannel :
	public UI
{
private:
	Texture* m_pPannelTex;
	fPOINT m_ptMouseOffset;


public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void init();

public:
	virtual void MouseOn();
	virtual void MouseLbtnClick();
	virtual void MouseLbtnAway();

public:
	void SetPannelTex();

public:
	UI_Pannel();
	~UI_Pannel();
};

