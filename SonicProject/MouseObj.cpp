#include "stdafx.h"
#include "MouseObj.h"
#include "ResManager.h"
#include "Camera.h"
#include "Texture.h"
#include "KeyManager.h"

MouseObj::MouseObj()
	:m_idxTile(-1)
	, m_ptOffset(fPOINT{0,0})
{
}


MouseObj::~MouseObj()
{
}


void MouseObj::render(HDC _dc)
{
	if (m_idxTile == -1)
		return;

	//Rectangle(_dc, ptCamPos.x, ptCamPos.y, ptCamPos.x +TileSizeX , ptCamPos.y +TileSizeY);

	int iXCnt = (int)m_pTex->GetWidth() / TileSizeX;
	int iLow = m_idxTile / iXCnt;
	int iCol = m_idxTile % iXCnt;

	/*fPOINT FinalPos = */

	TransparentBlt(_dc
		, (int)pos.x + (int)m_ptOffset.x
		, (int)pos.y + (int)m_ptOffset.y
		, TileSizeX
		, TileSizeY
		, m_pTex->GetTexDC()
		, iCol * TileSizeX
		, iLow * TileSizeY
		, TileSizeX
		, TileSizeY
		, (UINT)RGB(255, 0, 255));
}

void MouseObj::update()
{
	pos = KeyManager::Manager().GetMouseCur();

}

void MouseObj::init()
{
	m_pTex = ResManager::Manager().LoadTexture(L"\\Map\\Tile.Bmp", L"Map_Tile");
	pos = KeyManager::Manager().GetMouseCur();
}

