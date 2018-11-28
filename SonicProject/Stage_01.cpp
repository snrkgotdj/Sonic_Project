#include "stdafx.h"
#include "Stage_01.h"
#include "Player.h"
#include "ResManager.h"
#include "KeyManager.h"
#include "StageManager.h"
#include "Texture.h"
#include "Camera.h"
#include "TimeManager.h"
#include "Collider.h"
#include "CollManager.h"
#include "Ring.h"
#include "Nill.h"
#include "PathManager.h"
#include "FireItem.h"
#include "WaterItem.h"
#include "ThunderItem.h"
#include "Spring.h"
#include "Spring_Left.h"
#include "Spring_Right.h"
#include "Knuckle.h"
#include "Tail.h"
#include "Sonic.h"
#include "UIManager.h"
#include "SoundManager.h"

Stage_01::Stage_01()
{
	FloorColor = RGB(0, 239, 239);
	WallColor = RGB(255, 0, 0);
	ChangeColor = RGB(148, 148, 148);
}


Stage_01::~Stage_01()
{
}


void Stage_01::enter()
{
	SoundManager::Manager()->PlayBGM(L"BGM_STAGE_01");

	StageManager::Manager().SetCurStageType(STAGE_01);

	UIManager::Manager().SetTime(0, 0, 0);

	LoadMap();

	Stage::LoadOBJ(L"Stage_01");

	CreatePlayer();

	CreateSpring();

	SetColPair();
}

void Stage_01::exit()
{
	SoundManager::Manager()->StopSound(L"BGM_STAGE_01");

	Stage::exit();
}

void Stage_01::render(HDC _dc)
{
	fPOINT CamBackPos = Camera::Cam().GetBackCamPos(fPOINT{ 0, 0 },10);
	BitBlt(_dc, (int)CamBackPos.x, (int)CamBackPos.y, (int)3000, (int)750, m_BackDC, 0, 0, SRCCOPY);	

	fPOINT CamPos = Camera::Cam().GetCamPos(fPOINT{ 0, -200 });
	TransparentBlt(_dc, (int)CamPos.x, (int)CamPos.y, (int)15000, (int)3190, m_MapDC, 0, 0, (int)15000, (int)3190, RGB(0, 0, 0));

	Stage::render(_dc);

	TransparentBlt(_dc, (int)CamPos.x, (int)CamPos.y, (int)15000, (int)3190, m_CoverDC, 0, 0, (int)15000, (int)3190, RGB(0, 0, 0));

	Stage::EditRender(_dc);
}

void Stage_01::update()
{
	Stage::CheckDie();

	Stage::update();

	KeyCheck();

	Stage::EditMode(L"Stage_01");

	if (vecObj[Obj_PLAYER][0]->GetPos().x >= 15000)
	{
		StageManager::Manager().ChangeStage(STAGE_FINAL);
	}

}

void Stage_01::LoadMap()
{
	StageSize = POINT{ 15000,3000 };

	Camera::Cam().SetLimit(StageSize);

	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_01\\Stage_01_Map.bmp", L"Stage_01_front");
	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_01\\Stage_01_back.bmp", L"Stage_01_back");
	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_01\\Stage_01_Map_cover.bmp", L"Stage_01_cover");

	m_MapDC = ResManager::Manager().FindTexture(L"Stage_01_front")->GetTexDC();
	m_BackDC = ResManager::Manager().FindTexture(L"Stage_01_back")->GetTexDC();
	m_CoverDC = ResManager::Manager().FindTexture(L"Stage_01_cover")->GetTexDC();

}

void Stage_01::SetColPair()
{
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_SPRING });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_ITEM });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_NILL });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_RING });

}



void Stage_01::CreateSpring()
{
	Spring_Right* Spring_Right_00 = new Spring_Right;
	Spring_Right_00->init(fPOINT{ 10.f, 580.f }, 1500.f);
	vecObj[OBJ_SPRING].push_back(Spring_Right_00);

}

void Stage_01::KeyCheck()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_ENTER, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_01);
	}

	if (vecObj[Obj_PLAYER][0]->GetPos().y >= StageSize.y)
	{
		StageManager::Manager().ChangeStage(STAGE_01);
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_TAB, STATE_TAB) && m_eStageMode == MODE_PLAY)
	{
		m_eStageMode = MODE_EDIT;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_TAB, STATE_TAB) && m_eStageMode == MODE_EDIT)
	{
		m_eStageMode = MODE_PLAY;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_ESC, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_SELECT);
	}
}

void Stage_01::CreatePlayer()
{
	if (StageManager::Manager().GetCharactorMode() == KNUCKLE_MODE)
	{
		Knuckle * pKnuckle = new Knuckle;
		pKnuckle->init(fPOINT{ 100, 100 }, STAGE_01);
		pKnuckle->SetColor(FloorColor, WallColor, ChangeColor);
		vecObj[Obj_PLAYER].push_back(pKnuckle);
	}

	else if (StageManager::Manager().GetCharactorMode() == TAIL_MODE)
	{
		Tail * pTail = new Tail;
		pTail->init(fPOINT{ 100, 100 }, STAGE_01);
		pTail->SetColor(FloorColor, WallColor, ChangeColor);
		vecObj[Obj_PLAYER].push_back(pTail);
	}

	else if (StageManager::Manager().GetCharactorMode() == SONIC_MODE)
	{
		Sonic * pSonic = new Sonic;
		pSonic->init(fPOINT{ 100, 100 }, STAGE_01);
		pSonic->SetColor(FloorColor, WallColor, ChangeColor);
		vecObj[Obj_PLAYER].push_back(pSonic);
	}
}