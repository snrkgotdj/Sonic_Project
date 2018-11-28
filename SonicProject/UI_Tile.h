#pragma once
#include "UI_Btn.h"
class UI_Tile :
	public UI_Btn
{
private:
	int m_iIdx;
	fPOINT m_ptMouseOffset;

public:
	void SetTileindex(int _iIdx) { m_iIdx = _iIdx; }
	int GetIdx() { return m_iIdx; }

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
	UI_Tile();
	virtual ~UI_Tile();
};

