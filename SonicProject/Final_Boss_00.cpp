#include "stdafx.h"
#include "Final_Boss_00.h"
#include "ResManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Effect_Missile_Bomb.h"
#include "StageManager.h"
#include "Stage.h"
#include "Stage_Final.h"
#include "SoundManager.h"
#include "Emerald.h"

float getRandomNumber(float min, float max)
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_real_distribution<float> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}


Final_Boss_00::Final_Boss_00()
	:m_iLife(10)
	, m_fAccTime(0.f)
	, m_fHittedTime(0.f)
	, m_eBossState(BOSS_IDLE)
	, m_fBurnTime(0.f)
	, m_bDie(false)
	, m_bHitted(false)
{
}


Final_Boss_00::~Final_Boss_00()
{
}



void Final_Boss_00::init(fPOINT _pos)
{
	pos = _pos;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetSize(fPOINT{ 50,23 });
	collider->SetOffset(fPOINT{ 180, 210 });

	m_eOBJ_TYPE = OBJ_BOSS;

	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Final_Boss_00.bmp", L"Boss_Final");
	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Final_Boss_00_Hitted.bmp", L"Boss_Final_Hitted");


	m_BossTex = ResManager::Manager().FindTexture(L"Boss_Final")->GetTexDC();

	Anim = new Animator;

	Anim->AddAnimation(L"Boss_00", ResManager::Manager().FindTexture(L"Boss_Final"), fPOINT{ 0,0 }, 1, fPOINT{ 506 ,272 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Boss_00_Hitted", ResManager::Manager().FindTexture(L"Boss_Final_Hitted"), fPOINT{ 0,0 }, 1, fPOINT{ 506 ,272 }, 2, 0.025f, RGB(255, 0, 255), 0);

	Anim->PlayAnimation(L"Boss_00");

}

void Final_Boss_00::render(HDC _dc)
{
	Anim->render(_dc,pos);
}

void Final_Boss_00::update()
{
	collider->update();

	if (m_eBossState == BOSS_IDLE)
	{
		Boss_Idle();
	}

	else if (m_eBossState == BOSS_DIE)
	{
		Boss_Die();
	}

	if (m_bHitted == true || m_bDie == true)
	{
		Boss_HItted();
	}
}

void Final_Boss_00::enterCollision(Collider * _other)
{
	SoundManager::Manager()->StopSound(L"Sound_BossDamage");
	SoundManager::Manager()->PlaySoundW(L"Sound_BossDamage", false);

	m_bHitted = true;
	m_iLife -= 1;

	if (m_iLife <= 0)
	{
		m_bDie = true;
		m_eBossState = BOSS_DIE;
	}
}



void Final_Boss_00::Boss_HItted()
{
	m_fAccTime += 30 * DT;
	m_fHittedTime += 2 * DT;

	if (m_fAccTime >= 0 && m_fAccTime < 1)
	{
		Anim->PlayAnimation(L"Boss_00_Hitted");
	}

	else if (m_fAccTime >= 1 && m_fAccTime < 2)
	{
		Anim->PlayAnimation(L"Boss_00");
	}

	else if (m_fAccTime >= 2)
	{
		m_fAccTime = 0;
	}

	if (m_fHittedTime >= 1)
	{
		m_fAccTime = 0;
		m_fHittedTime = 0;
		Anim->PlayAnimation(L"Boss_00");
		m_bHitted = false;
	}
}

void Final_Boss_00::Boss_Idle()
{
	if (pos.x > 700)
	{
		pos.x -= 100 * DT;

		if (pos.x <= 700)
		{
			pos.x = 700;
		}
	}
}

void Final_Boss_00::Boss_Die()
{
	SoundManager::Manager()->PlaySoundW(L"Sound_BossDeath", true);

	m_fBurnTime += 10 * DT;

	if (m_fBurnTime >= 1)
	{
		Effect_Missile_Bomb* pEffect = new Effect_Missile_Bomb;
		pEffect->init(fPOINT{ getRandomNumber(pos.x - 129, pos.x + 129), getRandomNumber(pos.y - 272, pos.y) });
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pEffect);

		m_fBurnTime = 0;
	}

	pos.y += 50 * DT;

	pos.x -= 120 * DT;

	if (pos.x <= 0)
	{
		OBJ::Die();
		((Stage_Final*)(StageManager::Manager().GetCurStage()))->SetBossOn_01(true);
		((Stage_Final*)(StageManager::Manager().GetCurStage()))->SetBossOn(false);
		SoundManager::Manager()->StopSound(L"Sound_BossDeath");

		
	}
}

