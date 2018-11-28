#include "stdafx.h"
#include "StartBack.h"
#include "ResManager.h"
#include "Texture.h"
#include "Camera.h"

void StartBack::init()
{
	BackTex = ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Test\\TileMap.bmp", L"Stage_back");
	//BackTex1 = ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00_col_01.bmp", L"Stage_back1");
}

void StartBack::render(HDC _dc)
{
	fPOINT CamPos = Camera::Cam().GetCamMousePos(fPOINT{ 0,200});
	
	BitBlt(_dc, 0, 0, WindowSizeX, WindowSizeY, BackTex->GetTexDC(), (int)CamPos.x, (int)CamPos.y, SRCCOPY);
	//BitBlt(_dc, 0, 0, WindowSizeX, WindowSizeY, BackTex1->GetTexDC(), CamPos.x, CamPos.y, SRCCOPY);
	//TransparentBlt(_dc, 0, 0, WindowSizeX, WindowSizeY, BackTex->GetTexDC(), 0, 0, WindowSizeX, WindowSizeY, RGB(4, 146, 252));
	
}

StartBack::StartBack()
{
}


StartBack::~StartBack()
{
}
