#include "stdafx.h"
#include "Effect_Missile_Bomb.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"



Effect_Missile_Bomb::Effect_Missile_Bomb()
{
}


Effect_Missile_Bomb::~Effect_Missile_Bomb()
{
}



void Effect_Missile_Bomb::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Effect_Missile_Bomb::update()
{
	if (true == Anim->GetCurAnimation()->isFin())
	{
		OBJ::Die();
		Anim->GetCurAnimation()->SetFin(false);
	}
}

void Effect_Missile_Bomb::init(fPOINT _pos)
{
	pos = _pos;

	ResManager::Manager().LoadTexture(L"\\Boss\\BossExplosion.bmp", L"Boss_Explosion");

	Anim = new Animator;

	Anim->AddAnimation(L"Explosion", ResManager::Manager().FindTexture(L"Boss_Explosion"), fPOINT{ 0,0 }, 1, fPOINT{ 80,82 }, 32, 0.025f, RGB(255, 0, 255), 1);

	Anim->PlayAnimation(L"Explosion");
}

