#include "stdafx.h"
#include "WaterShield.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
#include "StageManager.h"
#include "Stage.h"
#include "Player.h"
#include "TimeManager.h"

WaterShield::WaterShield()
	:m_bRenderChange(true)
	, m_fAccRender(0.f)
	, m_bSkillOn(false)
	, m_fAccTime(0.f)
{
}


WaterShield::~WaterShield()
{
}


void WaterShield::init(Player * _player)
{
	player = _player;

	ResManager::Manager().LoadTexture(L"\\Shield\\WaterShield.bmp", L"Shied_Water");
	ResManager::Manager().LoadTexture(L"\\Effect\\Skill_Effect\\Water\\WaterSkill.bmp", L"WATER_EFFECT");

	m_ShieldTexDC = ResManager::Manager().FindTexture(L"Shied_Water")->GetTexDC();

	Anim = new Animator;
	
	Anim->AddAnimation(L"Water_Shield", ResManager::Manager().FindTexture(L"Shied_Water"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 9, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Water_Effect", ResManager::Manager().FindTexture(L"WATER_EFFECT"), fPOINT{ 0,0 }, 1, fPOINT{ 154,100 }, 4, 0.08f, RGB(255, 0, 255), 0);

	Anim->PlayAnimation(L"Water_Shield");
}

void WaterShield::PlayAnimation(const wstring & _strKey)
{
	Anim->PlayAnimation(_strKey,0);

	m_bSkillOn = true;
}

void WaterShield::render(HDC _dc)
{
	if (m_bRenderChange == true || m_bSkillOn == true)
		Anim->render(_dc, pos);
}

void WaterShield::update()
{
	RanderChange();

	pos = player->GetPos();

	if (m_bSkillOn == true)
	{
		m_fAccTime += DT;

		if (m_fAccTime >= 0.6)
		{
			Anim->PlayAnimation(L"Water_Shield");
			m_fAccTime = 0.f;

			m_bSkillOn = false;
		}
	}

	if (player->GetShield() != SHIELD_WATER)
	{
		OBJ::Die();
	}
}

void WaterShield::enterCollision(Collider * _other)
{
	OBJ::Die();
	player->SetShieldState(SHIELD_END);
}



void WaterShield::RanderChange()
{
	m_fAccRender += 40 * DT;

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