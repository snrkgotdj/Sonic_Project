#include "stdafx.h"
#include "Spring.h"
#include "Camera.h"
#include "Collider.h"
#include "Player.h"
#include "OBJ.h"
#include "ResManager.h"
#include "Animator.h"
#include "Animation.h"
#include "Texture.h"
#include "TimeManager.h"
#include "SoundManager.h"

Spring::Spring()
	: TUpSpring(NULL)
	, m_bOnCollision(false)
	, m_fAccTime(0.f)
{
}


Spring::~Spring()
{
	OBJ::~OBJ();
}


void Spring::render(HDC _dc)
{
	if (DEBUGRENDER == true)
	{
		collider->render(_dc);
	}
	Anim->render(_dc, pos);
}

void Spring::update()
{
	collider->update();
	if (true == m_bOnCollision)
	{
		m_fAccTime += 2 * DT;

		if (m_fAccTime >= 1)
		{
			m_fAccTime = 0.f;
			m_bOnCollision = false;
			Anim->PlayAnimation(L"spring_up_stay");
		}
	}
}

void Spring::enterCollision(Collider * _other)
{
	((Player*)(_other->GetOwner()))->SetState(PLAYER_SPRINGJUMP);
	((Player*)(_other->GetOwner()))->SetSpringSpeed(m_fSpringPower);
	((Player*)(_other->GetOwner()))->SetGravity(0.f);
	((Player*)(_other->GetOwner()))->SetClimb(false);

	Anim->PlayAnimation(L"spring_up_active");
	m_bOnCollision = true;

	SoundManager::Manager()->StopSound(L"Sound_Spring");
	SoundManager::Manager()->PlaySoundW(L"Sound_Spring", false);
}

void Spring::onCollision(Collider * _other)
{
	((Player*)(_other->GetOwner()))->SetState(PLAYER_SPRINGJUMP);
}

void Spring::exitCollision(Collider * _other)
{
}

void Spring::init(fPOINT _pos, float _Power)
{
	pos = _pos;
	size = fPOINT{ 30.f, 15.f };
	m_fSpringPower = _Power;


	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	TUpSpring = ResManager::Manager().LoadTexture(L"\\Item\\Spring\\Spring_UP.bmp", L"Spring_UP");

	Anim = new Animator;
	Anim->AddAnimation(L"spring_up_stay", TUpSpring, fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"spring_up_active", TUpSpring, fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.02f, RGB(255, 0, 255), 1);
	
	Anim->PlayAnimation(L"spring_up_stay");
}

void Spring::init()
{
	size = fPOINT{ 30.f, 15.f };
	m_fSpringPower = 1600;


	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	TUpSpring = ResManager::Manager().LoadTexture(L"\\Item\\Spring\\Spring_UP.bmp", L"Spring_UP");

	Anim = new Animator;
	Anim->AddAnimation(L"spring_up_stay", TUpSpring, fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"spring_up_active", TUpSpring, fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.02f, RGB(255, 0, 255), 1);

	Anim->PlayAnimation(L"spring_up_stay");
}
