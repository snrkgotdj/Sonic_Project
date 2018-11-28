#pragma once
#include "Stage.h"
class Stage_ICE :
	public Stage
{


public:
	virtual void enter();
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();


public:
	Stage_ICE();
	virtual ~Stage_ICE();
};

