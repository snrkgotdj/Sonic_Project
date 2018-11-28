#include "stdafx.h"
#include "FireShield_Back.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
#include "StageManager.h"
#include "Stage.h"
#include "Player.h"
#include "TimeManager.h"


void FireShield_Back::init(Player * _player)
{
	player = _player;
	ResManager::Manager().LoadTexture(L"\\Shield\\FireShield_Back.bmp", L"Shied_Fire_Back");

	m_ShieldTexDC = ResManager::Manager().FindTexture(L"Shied_Fire_Back")->GetTexDC();

	Anim = new Animator;
	Anim->AddAnimation(L"Fire_Shield_Back", ResManager::Manager().FindTexture(L"Shied_Fire_Back"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 18, 0.05f, RGB(255, 0, 255), 0);
	Anim->PlayAnimation(L"Fire_Shield_Back");
}

void FireShield_Back::render(HDC _dc)
{
	if(m_bRendOn == true)
	{
		Anim->render(_dc, pos);
	}
}

void FireShield_Back::update()
{
	pos = player->GetPos();

	if (m_bSkillOn == true)
	{
		m_fAccTime += DT;

		if (m_fAccTime >= 0.5)
		{
			m_bRendOn = true;
			m_fAccTime = 0.f;
			m_bSkillOn = false;
		}
	}

	if (player->GetShield() != SHIELD_FIRE)
	{
		OBJ::Die();
	}
}

void FireShield_Back::enterCollision(Collider * _other)
{
	OBJ::Die();
}

FireShield_Back::FireShield_Back()
	:m_bRendOn(true)
	, m_fAccTime(0.f)
	, m_bSkillOn(false)
{
}


FireShield_Back::~FireShield_Back()
{
}
