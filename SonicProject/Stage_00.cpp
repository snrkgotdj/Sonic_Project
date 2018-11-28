#include "stdafx.h"
#include "Stage_00.h"
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
#include "SoundManager.h"
#include "SiverSonic.h"
#include "OBJ_Box.h"
#include "Stair.h"
#include "NillWall.h"
#include "Goal.h"
#include "UIManager.h"

Stage_00::Stage_00()
	:m_bRenderChange(true)
	, m_fAccRender(0.f)
{
	FloorColor = RGB(0, 224, 224);
	WallColor = RGB(224, 0, 0);
	ChangeColor = RGB(150, 150, 150);
}


Stage_00::~Stage_00()
{
	Stage::~Stage();
}



void Stage_00::enter()
{
	StageManager::Manager().SetCurStageType(STAGE_00);

	UIManager::Manager().SetTime(0,0,0);

	LoadMap();

	SetColPair();

	CreatePlayer();

	Stage::LoadOBJ(L"Stage_00");

	SetColPair();

	CreateBoss();

	CreateOBJ();

	//BGM 재생
	SoundManager::Manager()->PlayBGM(L"BGM_STAGE_00");
}

void Stage_00::render(HDC _dc)
{
	fPOINT CamBackPos = Camera::Cam().GetBackCamPos(fPOINT{ 0, -700 },5);
	BitBlt(_dc, (int)CamBackPos.x, (int)CamBackPos.y, (int)6006, (int)2000, m_BackDC, 0, 0, SRCCOPY);

	Stage::render(_dc);

	fPOINT CamPos = Camera::Cam().GetCamMousePos(fPOINT{ 0,200 });
	if (m_bRenderChange == true)
		TransparentBlt(_dc, 0, 0, WindowSizeX, WindowSizeY, m_MapDC, (int)CamPos.x, (int)CamPos.y, WindowSizeX, WindowSizeY, RGB(0, 0, 0));

	else if (m_bRenderChange == false)
		TransparentBlt(_dc, 0, 0, WindowSizeX, WindowSizeY, m_LightDC, (int)CamPos.x, (int)CamPos.y, WindowSizeX, WindowSizeY, RGB(0, 0, 0));

	Stage::EditRender(_dc);
}

void Stage_00::update()
{
	CheckDie();

	Stage::update();

	RanderChange();

	KeyCheck();

	Stage::EditMode(L"Stage_00");
}



void Stage_00::LoadMap()
{
	StageSize = POINT{ 20182,2780 };

	Camera::Cam().SetLimit(StageSize);

	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Stage_00_Map.bmp", L"Stage_00_front");
	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Stage_00_back.bmp", L"Stage_00_back");
	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Stage_00_Map_light.bmp", L"Stage_00_light");

	m_MapDC = ResManager::Manager().FindTexture(L"Stage_00_front")->GetTexDC();
	m_BackDC = ResManager::Manager().FindTexture(L"Stage_00_back")->GetTexDC();
	m_LightDC = ResManager::Manager().FindTexture(L"Stage_00_light")->GetTexDC();


}

void Stage_00::SetColPair()
{
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_SPRING });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_ITEM });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_NILL });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_RING });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_BOSS });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_FEATURE });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_GOAL });

}

void Stage_00::CreatePlayer()
{
	if (StageManager::Manager().GetCharactorMode() == KNUCKLE_MODE)
	{
		Knuckle * pKnuckle = new Knuckle;
		pKnuckle->init(fPOINT{ 100, 1800 }, STAGE_00);
		//pKnuckle->init(fPOINT{ 19600, 1000 }, STAGE_00);
		//pKnuckle->init(fPOINT{ 11140, 2000 }, STAGE_00);
		//pKnuckle->init(fPOINT{ 7200, 2000 }, STAGE_00);
		//pKnuckle->init(fPOINT{ 4000, 2000 }, STAGE_00);

		pKnuckle->SetColor(FloorColor, WallColor, ChangeColor);
		vecObj[Obj_PLAYER].push_back(pKnuckle);
	}

	else if (StageManager::Manager().GetCharactorMode() == TAIL_MODE)
	{
		Tail * pTail = new Tail;
		pTail->init(fPOINT{ 100, 1800 }, STAGE_00);
		pTail->SetColor(FloorColor, WallColor, ChangeColor);
		vecObj[Obj_PLAYER].push_back(pTail);
	}

	else if (StageManager::Manager().GetCharactorMode() == SONIC_MODE)
	{
		Sonic * pSonic = new Sonic;
		//pSonic->init(fPOINT{ 19600, 1000 }, STAGE_00);
		pSonic->init(fPOINT{ 100, 1800 }, STAGE_00);
		pSonic->SetColor(FloorColor, WallColor, ChangeColor);
		vecObj[Obj_PLAYER].push_back(pSonic);
	}
}

void Stage_00::exit()
{
	Camera::Cam().SetPause(false);

	Stage::exit();

	SoundManager::Manager()->StopSound(L"BGM_STAGE_00");
}



void Stage_00::RanderChange()
{
	m_fAccRender += 20 * DT;

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


void Stage_00::KeyCheck()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_ENTER, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_00);
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_TAB, STATE_TAB) && m_eStageMode == MODE_PLAY)
	{
		m_eStageMode = MODE_EDIT;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_TAB, STATE_TAB) && m_eStageMode == MODE_EDIT)
	{
		m_eStageMode = MODE_PLAY;
	}

	if (vecObj[Obj_PLAYER][0]->GetPos().y >= StageSize.y)
	{
		StageManager::Manager().ChangeStage(STAGE_00);
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_ESC, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_SELECT);
	}
}

void Stage_00::CreateBoss()
{
	SiverSonic * pSiverSonic = new SiverSonic;
	pSiverSonic->init(fPOINT{ 20100, 500 });
	vecObj[OBJ_BOSS].push_back(pSiverSonic);
}

void Stage_00::CreateOBJ()
{
	//박스
	OBJ_Box * pBox_00 = new OBJ_Box;
	pBox_00->init(fPOINT{ 11410, 2527 }, MOVE_TOP);
	vecObj[OBJ_FEATURE].push_back(pBox_00);

	OBJ_Box * pBox_01 = new OBJ_Box;
	pBox_01->init(fPOINT{ 11647, 2527 }, MOVE_LEFT);
	vecObj[OBJ_FEATURE].push_back(pBox_01);

	OBJ_Box * pBox_02 = new OBJ_Box;
	pBox_02->init(fPOINT{ 11530, 2399 }, MOVE_RIGHT);
	vecObj[OBJ_FEATURE].push_back(pBox_02);

	//계단
	Stair * Stair_00 = new Stair;
	Stair_00->init(fPOINT{ 7200, 2390 }, MOVE_LEFT);
	vecObj[OBJ_FEATURE].push_back(Stair_00);

	Stair * Stair_01 = new Stair;
	Stair_01->init(fPOINT{ 7000, 2220 }, MOVE_RIGHT);
	vecObj[OBJ_FEATURE].push_back(Stair_01);

	Stair * Stair_02 = new Stair;
	Stair_02->init(fPOINT{ 3300, 1100 }, MOVE_END);
	vecObj[OBJ_FEATURE].push_back(Stair_02);

	/*Stair * Stair_03 = new Stair;
	Stair_03->init(fPOINT{ 3300, 1000 }, MOVE_END);
	vecObj[OBJ_FEATURE].push_back(Stair_03);*/

	Stair * Stair_04 = new Stair;
	Stair_04->init(fPOINT{ 3300, 1300 }, MOVE_END);
	vecObj[OBJ_FEATURE].push_back(Stair_04);

	Stair * Stair_05 = new Stair;
	Stair_05->init(fPOINT{ 16400, 1400 }, MOVE_END);
	vecObj[OBJ_FEATURE].push_back(Stair_05);

	Stair * Stair_07 = new Stair;
	Stair_07->init(fPOINT{ 16400, 1600 }, MOVE_END);
	vecObj[OBJ_FEATURE].push_back(Stair_07);
}
