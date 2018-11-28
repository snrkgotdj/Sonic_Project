#include "stdafx.h"
#include "Nill.h"
#include "Collider.h"
#include "Animator.h"
#include "Texture.h"
#include "ResManager.h"
#include "Camera.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "Player.h"
#include "Ring.h"
#include "StageManager.h"
#include "Stage.h"
#include "SoundManager.h"



Nill::Nill()
{
}


Nill::~Nill()
{
}


void Nill::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 31.f, 30.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	m_NillDC = ResManager::Manager().LoadTexture(L"\\Item\\Nill\\Nill_UP.bmp", L"Nill_UP")->GetTexDC();

}

void Nill::init()
{
	size = fPOINT{ 31.f, 30.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	m_NillDC = ResManager::Manager().LoadTexture(L"\\Item\\Nill\\Nill_UP.bmp", L"Nill_UP")->GetTexDC();
}


void Nill::render(HDC _dc)
{
	fPOINT CamPos = Camera::Cam().GetCamPos(pos);
	TransparentBlt(_dc, (int)CamPos.x - (int)size.x, (int)CamPos.y - (int)size.y * 2, (int)size.x * 2, (int)size.y * 2, m_NillDC, 0, 0, (int)size.x * 2, (int)size.y * 2, RGB(255, 0, 255));

	if(DEBUGRENDER == true)
		collider->render(_dc);
}

void Nill::update()
{

}

void Nill::enterCollision(Collider * _other)
{

}

void Nill::onCollision(Collider * _other)
{
	if (ANI_HITTED == ((Player*)(_other->GetOwner()))->GetAnimation() || ((Player*)(_other->GetOwner()))->GetInvincible() == true || ((Player*)(_other->GetOwner()))->isSuper()==true)
	{
		return;
	}


	if (((Player*)(_other->GetOwner()))->GetDir() == DIR_RIGHT)
	{
		((Player*)(_other->GetOwner()))->SetState(PLAYER_HITTED);
		((Player*)(_other->GetOwner()))->SetSpeed(-250.f);
		((Player*)(_other->GetOwner()))->SetGravity(0.f);
		((Player*)(_other->GetOwner()))->SetJumpSpeed(300.f);
		((Player*)(_other->GetOwner()))->SetInvincible(true);
		((Player*)(_other->GetOwner()))->SetClimb(false);
		((Player*)(_other->GetOwner()))->SetOnStair(false);
		if (((Player*)(_other->GetOwner()))->GetShield() == SHIELD_END)
		{
			if (0 != ((Player*)(_other->GetOwner()))->GetRingCnt())
			{
				SoundManager::Manager()->PlaySoundW(L"Sound_SpitRing", false);
				SpitOutRing(_other);
				((Player*)(_other->GetOwner()))->SetRingCnt(0);
			}

			else
			{
				SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
			}
		}
		else if (((Player*)(_other->GetOwner()))->GetShield() != SHIELD_END)
		{
			SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
		}
	}

	else if (((Player*)(_other->GetOwner()))->GetDir() == DIR_LEFT)
	{
		((Player*)(_other->GetOwner()))->SetState(PLAYER_HITTED);
		((Player*)(_other->GetOwner()))->SetSpeed(+250.f);
		((Player*)(_other->GetOwner()))->SetGravity(0.f);
		((Player*)(_other->GetOwner()))->SetJumpSpeed(300.f);
		((Player*)(_other->GetOwner()))->SetInvincible(true);
		((Player*)(_other->GetOwner()))->SetClimb(false);
		((Player*)(_other->GetOwner()))->SetOnStair(false);
		if (((Player*)(_other->GetOwner()))->GetShield() == SHIELD_END)
		{
			if (0 != ((Player*)(_other->GetOwner()))->GetRingCnt())
			{
				SoundManager::Manager()->PlaySoundW(L"Sound_SpitRing", false);
				SpitOutRing(_other);
				((Player*)(_other->GetOwner()))->SetRingCnt(0);
			}
			else
			{
				SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
			}

		}
		else if (((Player*)(_other->GetOwner()))->GetShield() != SHIELD_END)
		{
			SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
		}
	}
}

void Nill::SpitOutRing(Collider * _other)
{
	int iRingCnt = ((Player*)(_other->GetOwner()))->GetRingCnt();


	for (int i = 0; i < iRingCnt; ++i)
	{
		Ring* pRing = new Ring(true, getRandomNumber(0, (float)M_PI) 
			,StageManager::Manager().GetCurStage()->GetFloorColor()
			, StageManager::Manager().GetCurStage()->GetWallColor()
		, StageManager::Manager().GetCurStageType());

		pRing->init(fPOINT{ _other->GetOwner()->GetPos().x, _other->GetOwner()->GetPos().y });
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_RING).push_back(pRing);
	}
}

float Nill::getRandomNumber(float min, float max)
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_real_distribution<float> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}

