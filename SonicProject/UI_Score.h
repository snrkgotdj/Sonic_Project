#pragma once
#include "UI.h"
class UI_Score :
	public UI
{
public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void init();

public:
	UI_Score();
	virtual ~UI_Score();
};

