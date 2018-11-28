#pragma once
#include "Stage.h"

class UI_Pannel;

class MouseObj;
class Stage_Maptool :
	public Stage
{
private:
	int iXCnt;
	int iYCnt;

	int FirstTileUIIdx;

	MouseObj* pMouse;
	UI_Pannel* pPannelUI;

public:
	void ResetTile(int _ixCnt, int _iYCnt);
	void CreateButton();
	void SetNextTileUI();
	void SetPrevTileUI();
private:
	void KeyCheck();

public:
	MouseObj* GetMouseObj() { return pMouse; }

public:
	virtual void enter();
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();

public:
	Stage_Maptool();
	virtual ~Stage_Maptool();
};

