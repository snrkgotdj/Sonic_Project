#include "stdafx.h"
#include "Stage_Final.h"
#include "StageManager.h"
#include "ResManager.h"
#include "Texture.h"
#include "Camera.h"
#include "Sonic.h"
#include "Final_Boss_00.h"
#include "Missile.h"
#include "TimeManager.h"
#include "CollManager.h"
#include "Stone_00.h"
#include "Stone_01.h"
#include "Stone_02.h"
#include "Effect_Stone.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "Final_Boss_01.h"
#include "Emerald.h"
#include "Ring.h"
#include "KeyManager.h"



Stage_Final::Stage_Final()
	:m_ptMapPos{}
	, m_fMissileCreateTime(0.f)
	, m_fMissileCreateTime_01(0.f)
	, m_fStone_00_CreateTime(0.f)
	, m_fStone_01_CreateTime(0.f)
	, m_fStone_02_CreateTime(0.f)
	, m_fRingCreateTime(0.f)
	, m_bBossON(false)
	, m_bBossON_01(false)
	, m_pBoss(NULL)
	, m_pPlayer(NULL)
	, m_pBoss_01(NULL)
{
}


Stage_Final::~Stage_Final()
{
}


void Stage_Final::enter()
{
	UIManager::Manager().SetTime(0, 0, 0);

	StageManager::Manager().SetCurStageType(STAGE_FINAL);

	LoadMap();

	SetColPair();

	CreatePlayer();

	//BGM 재생
	SoundManager::Manager()->PlayBGM(L"BGM_STAGE_FINAL");
}

void Stage_Final::exit()
{
	SoundManager::Manager()->StopSound(L"BGM_STAGE_FINAL");
}

void Stage_Final::render(HDC _dc)
{
	fPOINT CamBackPos = Camera::Cam().GetBackCamPos(m_ptMapPos, 5);
	BitBlt(_dc, (int)CamBackPos.x, (int)CamBackPos.y, (int)2560, (int)1416, m_MapDC, 0, 0, SRCCOPY);

	Stage::render(_dc);
}

void Stage_Final::update()
{
	CheckDie();

	if (m_bBossON_01 == false)
	{
		if (UIManager::Manager().GetHour() >= 1)
		{
			CreateMissile();
		}

		else
		{
			CreateStone();
			CreateRing();
		}
	}

	else if (m_bBossON_01 == true)
	{
		if(m_bBossON == false)
			CreateBoss_01();

		CreateStone();

		m_fMissileCreateTime += DT;

		m_fMissileCreateTime_01 += DT;

		if (m_fMissileCreateTime_01 >= 4)
		{
			Missile * pMissile_00 = new Missile;
			pMissile_00->init(fPOINT{ m_pBoss_01->GetPos().x + 200, m_pBoss_01->GetPos().y - 100 }, m_pPlayer, true);
			vecObj[OBJ_MISSILE].push_back(pMissile_00);
			m_fMissileCreateTime_01 = 0.f;
		}
	}

	Stage::update();
	if (m_ptMapPos.x > -1200)
	{
		m_ptMapPos.x -= 10 * DT;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_ESC, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_SELECT);
	}
}

void Stage_Final::LoadMap()
{
	StageSize = POINT{ 2560,4500 };

	Camera::Cam().SetLimit(StageSize);

	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_Final\\Stage_Final_Map.bmp", L"Stage_Final");

	m_MapDC = ResManager::Manager().FindTexture(L"Stage_Final")->GetTexDC();
}

void Stage_Final::CreatePlayer()
{
	Sonic * pSonic = new Sonic;
	pSonic->init(fPOINT{ 100, 1540 }, STAGE_FINAL);
	pSonic->SetSuperSonic(true);
	pSonic->SetState(PLAYER_FINALSTAGE);
	pSonic->SetSpeed(900);
	pSonic->SetSize(fPOINT{ 32,32 });
	pSonic->SetRingCnt(50);
	pSonic->SetAnimation(ANI_FINALSTAGE);
	vecObj[Obj_PLAYER].push_back(pSonic);

	m_pPlayer = pSonic;
}


void Stage_Final::CreateBoss()
{
	Final_Boss_00 * pBoss_00 = new Final_Boss_00;
	pBoss_00->init(fPOINT{ 700, 1540 });
	vecObj[OBJ_BOSS].push_back(pBoss_00);

}

void Stage_Final::CreateMissile()
{
	m_fMissileCreateTime += DT;

	if (m_bBossON == false)
	{
		m_bBossON = true;

		Final_Boss_00 * pBoss_00 = new Final_Boss_00;
		pBoss_00->init(fPOINT{ 1500,  m_pPlayer->GetPos().y });
		m_pBoss = pBoss_00;
		vecObj[OBJ_BOSS].push_back(pBoss_00);
	}

	if (m_pBoss == NULL || m_pBoss->isDie() == true)
	{
		m_pPlayer->SetPause(true);

		return;
	}

	if (m_fMissileCreateTime >= 2)
	{
		Missile * pMissile_00 = new Missile;
		pMissile_00->init(fPOINT{ m_pBoss->GetPos().x + 200, m_pBoss->GetPos().y - 20}, m_pPlayer, true);
		vecObj[OBJ_MISSILE].push_back(pMissile_00);
		m_fMissileCreateTime = 0.f;
	}
}


void Stage_Final::CreateRing()
{
	m_fRingCreateTime += DT;

	if (m_fRingCreateTime >= 2.5)
	{
		Ring * pRing_00 = new Ring;
		pRing_00->init(fPOINT{ m_pPlayer->GetPos().x + 1200, m_pPlayer->GetPos().y  + 10});
		vecObj[OBJ_RING].push_back(pRing_00);

		Ring * pRing_01 = new Ring;
		pRing_01->init(fPOINT{ m_pPlayer->GetPos().x + 1250, m_pPlayer->GetPos().y + 10 });
		vecObj[OBJ_RING].push_back(pRing_01);

		Ring * pRing_02 = new Ring;
		pRing_02->init(fPOINT{ m_pPlayer->GetPos().x + 1300, m_pPlayer->GetPos().y + 10 });
		vecObj[OBJ_RING].push_back(pRing_02);

		m_fRingCreateTime = 0.f;
	}
}


void Stage_Final::CreateStone()
{
	m_fStone_00_CreateTime += 5 * DT;
	m_fStone_01_CreateTime += 2 * DT;
	m_fStone_02_CreateTime += DT;
	m_fMissileCreateTime += DT;

	fPOINT PlayerPos = m_pPlayer->GetPos();

	if (m_fStone_00_CreateTime >= 1)
	{
		Stone_00 * pStone_00 = new Stone_00;
		pStone_00->init(fPOINT{ PlayerPos.x + 1200, getRandomNumber(PlayerPos.y -300, PlayerPos.y + 400) });
		vecObj[OBJ_STONE].push_back(pStone_00);
		m_fStone_00_CreateTime = 0.f;
	}

	if (m_fStone_01_CreateTime >= 1)
	{
		Stone_01 * pStone_01 = new Stone_01;
		pStone_01->init(fPOINT{ PlayerPos.x + 1200, getRandomNumber(PlayerPos.y - 300, PlayerPos.y + 300) });
		vecObj[OBJ_STONE].push_back(pStone_01);
		m_fStone_01_CreateTime = 0.f;
	}

	if (m_fStone_02_CreateTime >= 3)
	{
		Stone_02 * pStone_02 = new Stone_02;
		pStone_02->init(fPOINT{ PlayerPos.x + 1200,getRandomNumber(PlayerPos.y - 300, PlayerPos.y + 300) });
		vecObj[OBJ_STONE].push_back(pStone_02);
		m_fStone_02_CreateTime = 0.f;
	}
	
	if (m_fMissileCreateTime >= 2)
	{
		Missile * pMissile_00 = new Missile;
		pMissile_00->init(fPOINT{ PlayerPos.x + 1200, PlayerPos.y }, m_pPlayer, false);
		vecObj[OBJ_MISSILE].push_back(pMissile_00);

		Missile * pMissile_01 = new Missile;
		pMissile_01->init(fPOINT{ PlayerPos.x + 1200, PlayerPos.y + 150 }, m_pPlayer, false);
		vecObj[OBJ_MISSILE].push_back(pMissile_01);

		m_fMissileCreateTime = 0.f;
	}
}

void Stage_Final::CreateBoss_01()
{
	m_bBossON = true;
	Final_Boss_01 * pBoss_00 = new Final_Boss_01;
	pBoss_00->init(fPOINT{ m_pPlayer->GetPos().x - 600, m_pPlayer->GetPos().y + 600 });
	m_pBoss_01 = pBoss_00;
	vecObj[OBJ_BOSS_01].push_back(pBoss_00);

	m_pPlayer->SetPause(false);
}



void Stage_Final::SetColPair()
{
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_MISSILE });
	CollManager::Manager().SetColPair(ColPair{ OBJ_BOSS, OBJ_MISSILE });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_STONE });
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_BOSS_01});
	CollManager::Manager().SetColPair(ColPair{ Obj_PLAYER, OBJ_RING });

}


float Stage_Final::getRandomNumber(float min, float max)
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_real_distribution<float> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}