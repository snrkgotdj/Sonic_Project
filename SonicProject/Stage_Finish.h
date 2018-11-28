#pragma once
#include "Stage.h"
class Stage_Finish :
	public Stage
{
	HWND m_hVideo;

public:
	virtual void enter();
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();

public:
	Stage_Finish();
	virtual ~Stage_Finish();
};

