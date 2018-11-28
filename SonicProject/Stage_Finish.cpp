#include "stdafx.h"
#include "Stage_Finish.h"
#include "PathManager.h"
#include "ResManager.h"
#include "GameManager.h"
#include "StageManager.h"
#include "UIManager.h"


Stage_Finish::Stage_Finish()
	:m_hVideo(NULL)
{
}


Stage_Finish::~Stage_Finish()
{
	MCIWndClose(m_hVideo);
	MCIWndDestroy(m_hVideo);
	m_hVideo = 0;
}



void Stage_Finish::enter()
{
	wstring strPath = PathManager::GetResPath();

	strPath += L"\\Video\\Finish.wmv";

	m_hVideo = MCIWndCreate(g_hWnd, hInst, MCIWNDF_NOTIFYMODE | MCIWNDF_NOTIFYPOS, strPath.c_str());

	if (m_hVideo != NULL)
	{
		SetWindowPos(m_hVideo, NULL, 0, 0, WindowSizeX, WindowSizeY + 30 , NULL);

		MCIWndPlay(m_hVideo);
	}

	StageManager::Manager().SetCurStageType(STAGE_FINISH);

	UIManager::Manager().SetTime(0, 0, 0);
}

void Stage_Finish::exit()
{
	MCIWndClose(m_hVideo);
	MCIWndDestroy(m_hVideo);
	m_hVideo = 0;
}

void Stage_Finish::render(HDC _dc)
{
}

void Stage_Finish::update()
{
	int a = UIManager::Manager().GetHour();
	int b = UIManager::Manager().GetMin();

	if (UIManager::Manager().GetHour() >= 1
		&& UIManager::Manager().GetMin() >= 1
		&& UIManager::Manager().GetSec() >= 5)
	{
		StageManager::Manager().ChangeStage(STAGE_LOGO_SEGA);
	}
	
}

