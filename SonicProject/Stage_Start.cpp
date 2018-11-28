#include "stdafx.h"
#include "Stage_Start.h"
#include "ResManager.h"
#include "Texture.h"
#include "OBJ.h"
#include "KeyManager.h"
#include "StageManager.h"
#include "Player.h"
#include "Camera.h"
#include "Tile.h"
#include "PathManager.h"
#include "Spring.h"
#include "CollManager.h"
#include "Spring_Right.h"
#include "Spring_Left.h"
#include "FireItem.h"
#include "FireShield.h"
#include "WaterItem.h"
#include "ThunderItem.h"
#include "Nill.h"
#include "Ring.h"
#include "Knuckle.h"
#include "Tail.h"
#include "Sonic.h"
#include "UI_Life.h"
#include "UI_Score.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "LifeBox.h"

Stage_Start::Stage_Start()
{
	FloorColor = RGB(0, 192, 224);
	WallColor = RGB(160, 96, 64);
	ChangeColor = RGB(150, 150, 150);
}


Stage_Start::~Stage_Start()
{

	Stage::~Stage();
}

void Stage_Start::enter()
{
	UIManager::Manager().CharactorLifeTexLoad();

	StageManager::Manager().SetCurStageType(STAGE_START);

	StageSize = POINT{ 4800,1200 };

	Camera::Cam().SetLimit(StageSize);

	Startback.init();

	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Test\\TileMap_Front.bmp", L"Stage_Test_Front");

	m_BackCover = ResManager::Manager().FindTexture(L"Stage_Test_Front")->GetTexDC();;


	CreateOBJ();

	SetColPair();

	SoundManager::Manager()->PlayBGM(L"BGM_STAGE_START");
}


void Stage_Start::exit()
{
	Stage::exit();

	SoundManager::Manager()->StopSound(L"BGM_STAGE_START");
}

void Stage_Start::render(HDC _dc)
{
	Startback.render(_dc);
	
	Stage::render(_dc);

	fPOINT CamPos = Camera::Cam().GetCamMousePos(fPOINT{ 0,200 });

	if(DEBUGRENDER == false)
		TransparentBlt(_dc, 0, 0, WindowSizeX, WindowSizeY, m_BackCover, (int)CamPos.x, (int)CamPos.y, WindowSizeX, WindowSizeY, RGB(255,0,255));

}

void Stage_Start::update()
{
	CheckDie();

	Stage::update();

	if (true == KeyManager::Manager().GetKeyState(KEY_ENTER, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_START);
	}

	if (vecObj[Obj_PLAYER][0]->GetPos().x >= StageSize.x || true == KeyManager::Manager().GetKeyState(KEY_F1, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_00);
	}

	else if (vecObj[Obj_PLAYER][0]->GetPos().y >= StageSize.y)
	{
		StageManager::Manager().ChangeStage(STAGE_START);
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_ESC, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_SELECT);
	}
}

void Stage_Start::CreatePlayer()
{
	if (StageManager::Manager().GetCharactorMode() == KNUCKLE_MODE)
	{
		Knuckle * pKnuckle = new Knuckle;

		pKnuckle->SetColor(FloorColor, WallColor, ChangeColor);

		pKnuckle->init(fPOINT{ 100, 400 }, STAGE_START);

		vecObj[Obj_PLAYER].push_back(pKnuckle);
	}
	
	else if (StageManager::Manager().GetCharactorMode() == TAIL_MODE)
	{
		Tail * pTail = new Tail;

		pTail->SetColor(FloorColor, WallColor, ChangeColor);

		pTail->init(fPOINT{ 100, 400 }, STAGE_START);

		vecObj[Obj_PLAYER].push_back(pTail);
	}

	else if (StageManager::Manager().GetCharactorMode() == SONIC_MODE)
	{
		Sonic * pSonic = new Sonic;

		pSonic->SetColor(FloorColor, WallColor, ChangeColor);

		pSonic->init(fPOINT{ 100, 400 }, STAGE_START);

		vecObj[Obj_PLAYER].push_back(pSonic);
	}

	
}

void Stage_Start::CreateItem()
{
	FireItem* FireItem_00 = new FireItem;
	FireItem_00->init(fPOINT{ 360.f, 552.f });
	vecObj[OBJ_ITEM].push_back(FireItem_00);

	WaterItem* WaterItem_00 = new WaterItem;
	WaterItem_00->init(fPOINT{ 460.f, 552.f });
	vecObj[OBJ_ITEM].push_back(WaterItem_00);

	ThunderItem* ThunderItem_00 = new ThunderItem;
	ThunderItem_00->init(fPOINT{ 560.f, 552.f });
	vecObj[OBJ_ITEM].push_back(ThunderItem_00);

	LifeBox* LifeBox_00 = new LifeBox;
	LifeBox_00->init(fPOINT{ 660.f, 552.f });
	vecObj[OBJ_ITEM].push_back(LifeBox_00);
}

void Stage_Start::CreateNill()
{
	Nill* Nill_UP_01 = new Nill;
	Nill_UP_01->init(fPOINT{ 800.f, 700.f });
	vecObj[OBJ_NILL].push_back(Nill_UP_01);
}

void Stage_Start::CreateRing()
{
	Ring* Ring_00 = new Ring;
	Ring_00->init(fPOINT{ 1610.f, 600.f });
	vecObj[OBJ_RING].push_back(Ring_00);

	Ring* Ring_01 = new Ring;
	Ring_01->init(fPOINT{ 1610.f, 500.f });
	vecObj[OBJ_RING].push_back(Ring_01);
	
	Ring* Ring_02 = new Ring;
	Ring_02->init(fPOINT{ 1610.f, 400.f });
	vecObj[OBJ_RING].push_back(Ring_02);
	
	Ring* Ring_03 = new Ring;
	Ring_03->init(fPOINT{ 1610.f, 300.f });
	vecObj[OBJ_RING].push_back(Ring_03);
	
	Ring* Ring_04 = new Ring;
	Ring_04->init(fPOINT{ 1610.f, 200.f });
	vecObj[OBJ_RING].push_back(Ring_04);
	
	Ring* Ring_05 = new Ring;
	Ring_05->init(fPOINT{ 1610.f, 100.f });
	vecObj[OBJ_RING].push_back(Ring_05);
}


void Stage_Start::CreateOBJ()
{
	CreatePlayer();

	CreateSpring();

	CreateItem();

	CreateNill();

	CreateRing();
}

void Stage_Start::CreateSpring()
{
	Spring* Spring_UP_00 = new Spring;
	Spring_UP_00->init(fPOINT{ 1616.f, 851.f }, 1700.f);
	vecObj[OBJ_SPRING].push_back(Spring_UP_00);

	Spring* Spring_UP_01 = new Spring;
	Spring_UP_01->init(fPOINT{ 2130.f, 700.f }, 1500.f);
	vecObj[OBJ_SPRING].push_back(Spring_UP_01);

	Spring_Right* Spring_Right_00 = new Spring_Right;
	Spring_Right_00->init(fPOINT{ 1060.f, 851.f }, 1500.f);
	vecObj[OBJ_SPRING].push_back(Spring_Right_00);

	/*Spring_Left* Spring_Left_00 = new Spring_Left;
	Spring_Left_00->init(fPOINT{ 4746.f, 547.f }, 1500.f);
	vecObj[OBJ_SPRING].push_back(Spring_Left_00);*/
}


void Stage_Start::SetColPair()
{
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_SPRING });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_ITEM });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_NILL });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_RING });
}


void Stage_Start::CreateUI()
{

}
