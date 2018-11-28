#pragma once
#include "UI_Btn.h"

class Btn_TC :
	public UI_Btn
{
private:
	

public:
	virtual void init();
	virtual void update();
	virtual void render(HDC _dc);


public:
	virtual void MouseJustOn();
	virtual void MouseOn();
	virtual void MouseOut();

	virtual void MouseLbtnClick();
	virtual void MouseLbtnAway();

public:
	Btn_TC();
	~Btn_TC();
};

