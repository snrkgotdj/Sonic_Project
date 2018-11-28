#include "stdafx.h"
#include "UI_Life.h"
#include "ResManager.h"
#include "Texture.h"
#include "StageManager.h"


void UI_Life::render(HDC _dc)
{
	TransparentBlt(_dc, 40, WindowSizeY - 60, 130, 46, m_GameUI, 0, 0, 130, 46, RGB(255, 0, 255));
}

void UI_Life::update()
{
}

void UI_Life::init()
{
	if (StageManager::Manager().GetCharactorMode() == KNUCKLE_MODE)
	{
		ResManager::Manager().LoadTexture(L"\\UI\\Life\\Knuckle_Life.bmp", L"Life_UI");
	}
	else if (StageManager::Manager().GetCharactorMode() == SONIC_MODE)
	{
		ResManager::Manager().LoadTexture(L"\\UI\\Life\\Sonic_Life.bmp", L"Life_UI");
	}
	else if (StageManager::Manager().GetCharactorMode() == TAIL_MODE)
	{
		ResManager::Manager().LoadTexture(L"\\UI\\Life\\Tail_Life.bmp", L"Life_UI");
	}

	m_GameUI = ResManager::Manager().FindTexture(L"Life_UI")->GetTexDC();


}

UI_Life::UI_Life()
{
}


UI_Life::~UI_Life()
{
}
