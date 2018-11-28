#include "stdafx.h"
#include "Final_Boss_01.h"
#include "ResManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "Player.h"
#include "StageManager.h"
#include "Stage.h"
#include "Effect_Missile_Bomb.h"
#include "Emerald.h"

float Final_Boss_01::getRandomNumber(float min, float max)
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_real_distribution<float> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}


Final_Boss_01::Final_Boss_01()
	:m_eBossState(BOSS_APPEAR)
	, m_iLife(8)
	, m_bHitted(false)
	, m_bDie(false)
	, m_fAccTime(0.f)
	, m_fBurnTime(0.f)
	, m_fHittedTime(0.f)
{
}


Final_Boss_01::~Final_Boss_01()
{
}


void Final_Boss_01::init(fPOINT _pos)
{
	pos = _pos;
	m_ptStartPos = _pos;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetSize(fPOINT{ 80, 80 });
	collider->SetOffset(fPOINT{ 20, 150 });

	m_eOBJ_TYPE = OBJ_BOSS;

	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Final_Boss_01.bmp", L"Boss_Final_01");
	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Final_Boss_01_Hitted.bmp", L"Boss_Final_Hitted_01");

	Anim = new Animator;

	Anim->AddAnimation(L"Boss_00", ResManager::Manager().FindTexture(L"Boss_Final_01"), fPOINT{ 0,0 }, 1, fPOINT{ 414 ,318 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Boss_00_Hitted", ResManager::Manager().FindTexture(L"Boss_Final_Hitted_01"), fPOINT{ 0,0 }, 1, fPOINT{ 414 ,318 }, 2, 0.025f, RGB(255, 0, 255), 0);

	Anim->PlayAnimation(L"Boss_00");
}

void Final_Boss_01::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Final_Boss_01::update()
{
	collider->update();

	switch (m_eBossState)
	{
	case BOSS_APPEAR:
		Boss_Apear();
		break;
	case BOSS_IDLE:
		Boss_Idle();
		break;

		
	case BOSS_DASHTURN:
		break;

	case BOSS_DIE:
		Boss_Die();
		break;

	case BOSS_END:
		break;
	default:
		break;
	}

	if (m_bHitted == true || m_bDie == true)
	{
		Boss_HItted();
	}
}

void Final_Boss_01::enterCollision(Collider * _other)
{
	SoundManager::Manager()->StopSound(L"Sound_BossDamage");
	SoundManager::Manager()->PlaySoundW(L"Sound_BossDamage", false);

	((Player*)(_other->GetOwner()))->SetAnimation(ANI_HITTED);
	((Player*)(_other->GetOwner()))->SetInvincible(true);

	m_bHitted = true;
	m_iLife -= 1;

	if (m_iLife <= 0)
	{
		if (m_eBossState != BOSS_DIE)
		{
			Emerald* pEmerald = new Emerald;
			pEmerald->init(fPOINT{ pos.x, pos.y - 100});
			StageManager::Manager().GetCurStage()->GetListObj(OBJ_STONE).push_back(pEmerald);
		}
		
		m_bDie = true;
		m_eBossState = BOSS_DIE;
	}
}


void Final_Boss_01::Boss_Apear()
{
	SoundManager::Manager()->PlaySoundW(L"Sound_Boss_01_Apear", false);
	pos.x += 600 * DT;

	pos.y -= 200 * DT;

	if (pos.y <= m_ptStartPos.y - 300)
	{
		m_eBossState = BOSS_IDLE;
		SoundManager::Manager()->StopSound(L"Sound_Boss_01_Apear");
	}
}

void Final_Boss_01::Boss_Idle()
{
}

void Final_Boss_01::Boss_HItted()
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

void Final_Boss_01::Boss_Die()
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

	pos.x -= 300 * DT;

	if (pos.x <= 0)
	{
		OBJ::Die();
		SoundManager::Manager()->StopSound(L"Sound_BossDeath");
	}
}
