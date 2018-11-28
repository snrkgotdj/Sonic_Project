#include "stdafx.h"
#include "StageManager.h"
#include "Stage_Logo.h"
#include "Stage_Start.h"
#include "Stage_Maptool.h"
#include "OBJ.h"
#include "KeyManager.h"
#include "Stage_ICE.h"
#include "Stage_00.h"
#include "Stage_Select.h"
#include "Stage_01.h"
#include "Stage_Logo_Sega.h"
#include "Stage_Final.h"
#include "Stage_Finish.h"



void StageManager::init()
{
	//m_eCharactor = KNUCKLE_MODE;
	//m_eCharactor = TAIL_MODE;
	m_eCharactor = SONIC_MODE;

	ArrStage[STAGE_LOGO_SEGA] = new Stage_Logo_Sega;
	ArrStage[STAGE_LOGO] = new Stage_Logo;
	ArrStage[STAGE_SELECT] = new Stage_Select;
	ArrStage[STAGE_START] = new Stage_Start;
	ArrStage[STAGE_00] = new Stage_00;
	ArrStage[STAGE_01] = new Stage_01;
	ArrStage[STAGE_FINAL] = new Stage_Final;
	ArrStage[STAGE_FINISH] = new Stage_Finish;
	
	CurStage = ArrStage[STAGE_LOGO_SEGA];

	CurStageType = STAGE_LOGO;
	
	CurStage->enter();
}

void StageManager::render(HDC _dc)
{
	CurStage->render(_dc);
}

void StageManager::update()
{
	CurStage->update();

	if (true == KeyManager::Manager().GetKeyState(KEY_9, STATE_TAB))
	{
		DEBUGRENDER = false;
	}
	else if (true == KeyManager::Manager().GetKeyState(KEY_0, STATE_TAB))
	{
		DEBUGRENDER = true;
	}
}

void StageManager::ChangeStage(STAGE_TYPE _type)
{
	CurStage->exit();
	CurStage = ArrStage[_type];
	CurStage->enter();
}


StageManager::StageManager()
	: CurStage(NULL)
	, ArrStage{}
	, CurStageType(STAGE_END)
{
}


StageManager::~StageManager()
{
	for (int i = 0; i < STAGE_END; ++i)
	{
		if (ArrStage[i] != NULL)
		{
			delete ArrStage[i];
			ArrStage[i] = NULL;
		}
	}
}
