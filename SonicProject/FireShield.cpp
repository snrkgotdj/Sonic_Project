#include "stdafx.h"
#include "FireShield.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
#include "StageManager.h"
#include "Stage.h"
#include "Player.h"
#include "TimeManager.h"

FireShield::FireShield()
	:m_fAccTime(0.f)
	, m_bSkillOn(false)
{
}


FireShield::~FireShield()
{
}

void FireShield::init(Player* _player)
{
	player = _player;
	ResManager::Manager().LoadTexture(L"\\Shield\\FireShield_Front.bmp", L"Shied_Fire");
	ResManager::Manager().LoadTexture(L"\\Effect\\Skill_Effect\\Fire\\FireSkill_Right.bmp", L"FIRE_EFFECT");
	ResManager::Manager().LoadTexture(L"\\Effect\\Skill_Effect\\Fire\\FireSkill_Left.bmp", L"FIRE_EFFECT_Left");

	m_ShieldTexDC = ResManager::Manager().FindTexture(L"Shied_Fire")->GetTexDC();

	Anim = new Animator;
	Anim->AddAnimation(L"Fire_Shield", ResManager::Manager().FindTexture(L"Shied_Fire"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 18, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Fire_Effect", ResManager::Manager().FindTexture(L"FIRE_EFFECT"), fPOINT{ 0,0 }, 1, fPOINT{ 140,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Fire_Effect_Left", ResManager::Manager().FindTexture(L"FIRE_EFFECT_Left"), fPOINT{ 0,0 }, -1, fPOINT{ 140,100 }, 4, 0.05f, RGB(255, 0, 255), 0);

	Anim->PlayAnimation(L"Fire_Shield");
}

void FireShield::render(HDC _dc)
{

	Anim->render(_dc, pos);

}

void FireShield::update()
{
	pos = player->GetPos();

	if (m_bSkillOn == true)
	{
		m_fAccTime += DT;

		if (m_fAccTime >= 0.5)
		{
			Anim->PlayAnimation(L"Fire_Shield");
			m_fAccTime = 0.f;

			m_bSkillOn = false;
		}
	}


	if (player->GetShield() != SHIELD_FIRE)
	{
		OBJ::Die();
	}
}

void FireShield::enterCollision(Collider * _other)
{
	OBJ::Die();
	player->SetShieldState(SHIELD_END);
}


void FireShield::PlayAnimation(const wstring & _strKey)
{
	Anim->PlayAnimation(_strKey);

	m_bSkillOn = true;
}