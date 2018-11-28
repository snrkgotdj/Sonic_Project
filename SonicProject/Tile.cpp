#include "stdafx.h"
#include "Tile.h"
#include "Camera.h"
#include "Texture.h"
#include "ResManager.h"
#include "KeyManager.h"
#include "StageManager.h"
#include "Stage.h"
#include "Stage_Maptool.h"
#include "MouseObj.h"
#include "func.h"

Tile::Tile()
	:idxTile(0)
{

}


Tile::~Tile()
{
}


void Tile::Save(FILE * _pFile)
{
	fwrite(&pos, sizeof(fPOINT), 1, _pFile);

	fwrite(&size, sizeof(fPOINT), 1, _pFile);

	const wstring & texPath = pTex->GetPath();

	SaveWstring(pTex->GetPath(), _pFile);

	SaveWstring(pTex->GetKey(), _pFile);

	fwrite(&idxTile, sizeof(int), 1, _pFile);
	
}

void Tile::Load(FILE * _pFile)
{
	// Position
	fread(&pos, sizeof(fPOINT), 1, _pFile);

	// Size
	fread(&size, sizeof(fPOINT), 1, _pFile);

	wstring strPath = LoadWstring(_pFile);
	wstring strKey = LoadWstring(_pFile);

	pTex = ResManager::Manager().LoadTexture(strPath, strKey);
	fread(&idxTile, sizeof(int), 1, _pFile);
}

void Tile::render(HDC _dc)
{
	fPOINT ptCamPos = Camera::Cam().GetCamPos(pos);
	//Rectangle(_dc, ptCamPos.x, ptCamPos.y, ptCamPos.x +TileSizeX , ptCamPos.y +TileSizeY);

	int iXCnt = (int)pTex->GetWidth() / TileSizeX;
	int iLow = idxTile / iXCnt;
	int iCol = idxTile % iXCnt;

	TransparentBlt(_dc
		, (int)ptCamPos.x
		, (int)ptCamPos.y
		, TileSizeX
		, TileSizeY
		, pTex->GetTexDC()
		, iCol * TileSizeX
		, iLow * TileSizeY
		, TileSizeX
		, TileSizeY
		, RGB(255, 0, 255));
}

void Tile::update()
{
	bool bMouseOn = isMouseOn(false);

	int iXCnt = (int)pTex->GetWidth() / TileSizeX;
	int iYCnt = (int)pTex->GetHeight() / TileSizeY;

	int iMaxCnt = iXCnt * iYCnt;

	fPOINT mouse = KeyManager::Manager().GetMouseCur();
	mouse = Camera::Cam().GetCamMousePos(mouse);
	Stage_Maptool* maptool = (Stage_Maptool*)StageManager::Manager().GetCurStage();
	MouseObj* pMouse = maptool->GetMouseObj();
	int mouseIdx = pMouse->GetTileIdx();

	if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && bMouseOn == true)
	{
		idxTile += 1;

		if (idxTile > iMaxCnt)
		{
			idxTile = 0;
		}

		
		if (mouseIdx != -1)
		{
			idxTile = mouseIdx;
		}
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_RBTN, STATE_TAB) && bMouseOn == true)
	{
		idxTile -= 1;

		if (idxTile < 0)
		{
			idxTile = iMaxCnt;
		}
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_HOLD) && bMouseOn == true)
	{
		if (mouseIdx != -1)
		{
			idxTile = mouseIdx;
		}
	}

}

void Tile::init()
{
	pTex = ResManager::Manager().FindTexture(L"Map_Tile");

	size.x = TileSizeX;
	size.y = TileSizeY;
}

void Tile::enterCollision(Collider * _other)
{
}

void Tile::onCollision(Collider * _other)
{
}

void Tile::exitCollision(Collider * _other)
{
}
