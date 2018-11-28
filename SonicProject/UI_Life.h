#pragma once
#include "UI.h"
class UI_Life :
	public UI
{

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void init();
public:
	UI_Life();
	virtual ~UI_Life();
};

