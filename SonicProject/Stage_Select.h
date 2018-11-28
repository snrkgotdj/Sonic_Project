#pragma once
#include "Stage.h"
class Stage_Select :
	public Stage
{
private:
	bool m_bRenderChange;
	float m_fAccRender;
	fPOINT Select_Pos;
	Charactor_Mode Select_Charactor;
	

private:
	void RanderChange();
	void CharactorChanage();
	void ChooseCharactor();

public:
	virtual void enter();
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();

public:
	Stage_Select();
	virtual ~Stage_Select();
};

