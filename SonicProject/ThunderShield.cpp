#include "stdafx.h"
#include "ThunderShield.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
#include "StageManager.h"
#include "Stage.h"
#include "Player.h"

void ThunderShield::init(Player * _player)
{
	player = _player;
	ResManager::Manager().LoadTexture(L"\\Shield\\ThunderShield.bmp", L"Shied_Thunder");

	m_ShieldTexDC = ResManager::Manager().FindTexture(L"Shied_Thunder")->GetTexDC();

	Anim = new Animator;
	Anim->AddAnimation(L"Thunder_Shield", ResManager::Manager().FindTexture(L"Shied_Thunder"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 12, 0.1f, RGB(255, 0, 255), 0);
	Anim->PlayAnimation(L"Thunder_Shield");
}

void ThunderShield::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void ThunderShield::update()
{
	pos = player->GetPos();
	if (player->GetShield() != SHIELD_THUNDER)
	{
		OBJ::Die();
	}
}

void ThunderShield::enterCollision(Collider * _other)
{
	OBJ::Die();
	player->SetShieldState(SHIELD_END);
}

ThunderShield::ThunderShield()
{
}


ThunderShield::~ThunderShield()
{
}
