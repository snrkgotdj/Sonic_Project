#include "stdafx.h"
#include "Spring_Left.h"
#include "Collider.h"
#include "ResManager.h"
#include "Animation.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Player.h"
#include "SoundManager.h"

Spring_Left::Spring_Left()
	: m_fSpringPower(0.f)
	, m_fAccTime(0.f)
	, TLeftSpring(NULL)
	, m_bOnCollision(false)
{
}


Spring_Left::~Spring_Left()
{
}


void Spring_Left::render(HDC _dc)
{
	if (DEBUGRENDER == true)
	{
		collider->render(_dc);
	}
	Anim->render(_dc, pos);
}

void Spring_Left::update()
{
	collider->update();
	if (true == m_bOnCollision)
	{
		m_fAccTime += 2 * DT;

		if (m_fAccTime >= 1)
		{
			m_fAccTime = 0.f;
			m_bOnCollision = false;
			Anim->PlayAnimation(L"spring_left_stay");
		}
	}
}

void Spring_Left::enterCollision(Collider * _other)
{
	((Player*)(_other->GetOwner()))->SetState(PLAYER_LEFTWalK);
	((Player*)(_other->GetOwner()))->SetSpeed(-m_fSpringPower);
	((Player*)(_other->GetOwner()))->SetGradient(fPOINT{ 1.f, 0.f });

	Anim->PlayAnimation(L"spring_left_active");
	m_bOnCollision = true;

	SoundManager::Manager()->StopSound(L"Sound_Spring");
	SoundManager::Manager()->PlaySoundW(L"Sound_Spring", false);
}

void Spring_Left::onCollision(Collider * _other)
{
}

void Spring_Left::exitCollision(Collider * _other)
{
}

void Spring_Left::init(fPOINT _pos, float _Power)
{
	pos = _pos;
	size = fPOINT{ 15.f, 30.f };
	m_fSpringPower = _Power;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	TLeftSpring = ResManager::Manager().LoadTexture(L"\\Item\\Spring\\Spring_LEFT.bmp", L"Spring_LEFT");

	Anim = new Animator;
	Anim->AddAnimation(L"spring_left_stay", TLeftSpring, fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.02f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"spring_left_active", TLeftSpring, fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.02f, RGB(255, 0, 255), 1);

	Anim->PlayAnimation(L"spring_left_stay");
}

void Spring_Left::init()
{
	size = fPOINT{ 15.f, 30.f };
	m_fSpringPower = 1700;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	TLeftSpring = ResManager::Manager().LoadTexture(L"\\Item\\Spring\\Spring_LEFT.bmp", L"Spring_LEFT");

	Anim = new Animator;
	Anim->AddAnimation(L"spring_left_stay", TLeftSpring, fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.02f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"spring_left_active", TLeftSpring, fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.02f, RGB(255, 0, 255), 1);

	Anim->PlayAnimation(L"spring_left_stay");
}

