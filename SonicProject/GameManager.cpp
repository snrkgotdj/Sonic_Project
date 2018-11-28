#include "stdafx.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "StageManager.h"
#include "Camera.h"
#include "CollManager.h"
#include "PathManager.h"
#include "UIManager.h"
#include "SoundManager.h"


void GameManager::init()
{
	m_dc = GetDC(g_hWnd);
	m_BackDC = CreateCompatibleDC(m_dc);
	m_BackBitmap = CreateCompatibleBitmap(m_dc, WindowSizeX, WindowSizeY);

	HBITMAP oldbitmap = (HBITMAP)SelectObject(m_BackDC, m_BackBitmap);
	DeleteObject(oldbitmap);

	PathManager::init();

	SoundManager::Manager()->init();
	
	TimeManager::Manager().init();
	
	KeyManager::Manager().init();
	
	StageManager::Manager().init();

	UIManager::Manager().init();
}

void GameManager::play()
{
	update();
	render();
}

void GameManager::render()
{
	if (StageManager::Manager().GetCurStageType() == STAGE_FINISH)
		return;

	RECT rt = { 0,0,WindowSizeX,WindowSizeY };
	FillRect(m_BackDC, &rt, HBRUSH(WHITE_BRUSH));

	StageManager::Manager().render(m_BackDC);
	
	TimeManager::Manager().render(m_BackDC);

	STAGE_TYPE stage = StageManager::Manager().GetCurStageType();

	if(StageManager::Manager().GetCurStageType() != STAGE_LOGO && StageManager::Manager().GetCurStageType() != STAGE_SELECT)
		UIManager::Manager().render(m_BackDC);

	BitBlt(m_dc, 0, 0, WindowSizeX, WindowSizeY, m_BackDC, 0, 0, SRCCOPY);
}

void GameManager::update()
{
	KeyManager::Manager().update();
	StageManager::Manager().update();
	TimeManager::Manager().update();
	CollManager::Manager().update();
	UIManager::Manager().update();
	Camera::Cam().update();
}



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
	ReleaseDC(g_hWnd, m_dc);

	DeleteObject(m_BackBitmap);
	DeleteDC(m_BackDC);
}
