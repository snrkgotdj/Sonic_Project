#include "stdafx.h"
#include "Stage_Select.h"
#include "ResManager.h"
#include "Texture.h"
#include "TimeManager.h"
#include "Camera.h"
#include "KeyManager.h"
#include "StageManager.h"
#include "SoundManager.h"

Stage_Select::Stage_Select()
	: m_bRenderChange(true)
	, m_fAccRender(0.f)
	, Select_Pos{ 411 ,100 }
	, Select_Charactor(SONIC_MODE)
{
	
}


Stage_Select::~Stage_Select()
{
}



void Stage_Select::enter()
{
	StageManager::Manager().SetCurStageType(STAGE_SELECT);

	ResManager::Manager().LoadTexture(L"\\Select\\DATA_SELECT.bmp", L"SELECT_back");
	ResManager::Manager().LoadTexture(L"\\Select\\Select_Box.bmp", L"SELECT_BOX");
	ResManager::Manager().LoadTexture(L"\\Select\\Select_Red.bmp", L"SELECT_RED");
	ResManager::Manager().LoadTexture(L"\\Select\\Sonic.bmp", L"SELECT_Sonic");
	ResManager::Manager().LoadTexture(L"\\Select\\Knuckle.bmp", L"SELECT_Knuckle");
	ResManager::Manager().LoadTexture(L"\\Select\\Tail.bmp", L"SELECT_Tail");

	SoundManager::Manager()->PlaySoundW(L"BGM_STAGE_SELECT",false);
}

void Stage_Select::exit()
{
	SoundManager::Manager()->StopSound(L"BGM_STAGE_SELECT");
}

void Stage_Select::render(HDC _dc)
{
	BitBlt(_dc, 0, 0, WindowSizeX, WindowSizeY, ResManager::Manager().FindTexture(L"SELECT_back")->GetTexDC(), 0, 0, SRCCOPY);

	fPOINT campos = { 400,100 };
	Camera::Cam().GetCamPos(campos);
	TransparentBlt(_dc, (int)campos.x, (int)campos.y, 200, 381, ResManager::Manager().FindTexture(L"SELECT_BOX")->GetTexDC(), 0, 0, 200, 381, RGB(255, 0, 255));
	TransparentBlt(_dc, (int)campos.x + 300, (int)campos.y, 200, 381, ResManager::Manager().FindTexture(L"SELECT_BOX")->GetTexDC(), 0, 0, 200, 381, RGB(255, 0, 255));
	TransparentBlt(_dc, (int)campos.x - 300, (int)campos.y, 200, 381, ResManager::Manager().FindTexture(L"SELECT_BOX")->GetTexDC(), 0, 0, 200, 381, RGB(255, 0, 255));

	TransparentBlt(_dc, (int)campos.x + 60, (int)campos.y + 20, 80, 100, ResManager::Manager().FindTexture(L"SELECT_Knuckle")->GetTexDC(), 0, 0, 80, 100, RGB(255, 0, 255));
	TransparentBlt(_dc, (int)campos.x + 340, (int)campos.y+20, 103, 100, ResManager::Manager().FindTexture(L"SELECT_Tail")->GetTexDC(), 0, 0, 103, 100, RGB(255, 0, 255));
	TransparentBlt(_dc, (int)campos.x - 250, (int)campos.y + 20, 79, 100, ResManager::Manager().FindTexture(L"SELECT_Sonic")->GetTexDC(), 0, 0, 79, 100, RGB(255, 0, 255));


	if (m_bRenderChange == true)
		TransparentBlt(_dc, (int)Select_Pos.x, (int)Select_Pos.y, 167, 381, ResManager::Manager().FindTexture(L"SELECT_RED")->GetTexDC(), 0, 0, 167, 381, RGB(255, 0, 255));
}

void Stage_Select::update()
{
	RanderChange();

	CharactorChanage();

	ChooseCharactor();
}


void Stage_Select::RanderChange()
{
	m_fAccRender += 5 * DT;

	if (m_fAccRender >= 0 && m_fAccRender < 1)
	{
		m_bRenderChange = false;
	}

	else if (m_fAccRender >= 1 && m_fAccRender < 2)
	{
		m_bRenderChange = true;
	}

	else if (m_fAccRender >= 2)
	{
		m_fAccRender = 0;
	}
}

void Stage_Select::CharactorChanage()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_TAB))
	{
		Select_Pos.x += 300;

		if (Select_Pos.x > 711)
		{
			Select_Pos.x = 711;
		}
		SoundManager::Manager()->StopSound(L"Sound_Buttom_Move");
		SoundManager::Manager()->PlaySoundW(L"Sound_Buttom_Move", false);
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_TAB))
	{
		Select_Pos.x -= 300;
		
		if (Select_Pos.x < 111)
		{
			Select_Pos.x = 111;
		}

		SoundManager::Manager()->StopSound(L"Sound_Buttom_Move");
		SoundManager::Manager()->PlaySoundW(L"Sound_Buttom_Move", false);
	}
}

void Stage_Select::ChooseCharactor()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_ENTER, STATE_TAB))
	{
		if (Select_Pos.x <= 200)
		{
			StageManager::Manager().SetCharactorMode(SONIC_MODE);
		}

		else if (Select_Pos.x >= 300 && Select_Pos.x <= 500)
		{
			StageManager::Manager().SetCharactorMode(KNUCKLE_MODE);
		}

		else if (Select_Pos.x >= 600 && Select_Pos.x <= 800)
		{
			StageManager::Manager().SetCharactorMode(TAIL_MODE);
		}

		StageManager::Manager().ChangeStage(STAGE_START);
	}
}

