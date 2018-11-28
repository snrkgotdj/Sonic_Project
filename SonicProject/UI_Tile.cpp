#include "stdafx.h"
#include "UI_Tile.h"
#include "ResManager.h"
#include "Texture.h"
#include "KeyManager.h"
#include "Camera.h"
#include "StageManager.h"
#include "Stage.h"
#include "Stage_Maptool.h"
#include "MouseObj.h"

UI_Tile::UI_Tile()
	:m_ptMouseOffset{}
{
}


UI_Tile::~UI_Tile()
{
}



void UI_Tile::init()
{
	Texture* pTex = ResManager::Manager().FindTexture(L"Map_Tile");

	vecBtnTex.push_back(pTex);
}

void UI_Tile::update()
{
	UI_Btn::update();
	child_update();
}

void UI_Tile::render(HDC _dc)
{
	
	int iXCnt = (int)vecBtnTex[0]->GetWidth() / TileSizeX;
	int iLow = m_iIdx / iXCnt;
	int iCol = m_iIdx % iXCnt;

	TransparentBlt(_dc
		, (int)m_FinalPos.x
		, (int)m_FinalPos.y
		, TileSizeX
		, TileSizeY
		, vecBtnTex[0]->GetTexDC()
		, iCol * TileSizeX
		, iLow * TileSizeY
		, TileSizeX
		, TileSizeY
		, RGB(255, 0, 255));

	child_render(_dc);
}

void UI_Tile::MouseJustOn()
{
}

void UI_Tile::MouseOn()
{
	if (m_bLbtnClicked == false)
		return;

}

void UI_Tile::MouseOut()
{
}

void UI_Tile::MouseLbtnClick()
{
	m_bLbtnClicked = true;

	fPOINT ptMouse = KeyManager::Manager().GetMouseCur();
	m_ptMouseOffset = m_FinalPos - ptMouse;

	Stage_Maptool* maptool = (Stage_Maptool*)StageManager::Manager().GetCurStage();
	MouseObj* mouse = maptool->GetMouseObj();

	mouse->SetTileIdx(m_iIdx);
	mouse->SetOffset(m_ptMouseOffset);


}

void UI_Tile::MouseLbtnAway()
{
}

