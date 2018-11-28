#include "stdafx.h"
#include "Effect_Fire.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "StageManager.h"
#include "Stage.h"

Effect_Fire::Effect_Fire()
{
}


Effect_Fire::~Effect_Fire()
{
}



void Effect_Fire::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Effect_Fire::update()
{
	pos.x = player->GetPos().x -10;
	pos.y = player->GetPos().y ;

	/*if (true == Anim->GetCurAnimation()->isFin())
	{
		OBJ::Die();
		Anim->GetCurAnimation()->SetFin(false);
	}*/

}

void Effect_Fire::init(Player * _player)
{
	pos.x = _player->GetPos().x - 10;
	pos.y = _player->GetPos().y ;

	player = _player;

	ResManager::Manager().LoadTexture(L"\\Effect\\Skill_Effect\\Fire\\FireSkill_Right.bmp", L"FIRE_EFFECT");

	Anim = new Animator;

	Anim->AddAnimation(L"Fire_Effect", ResManager::Manager().FindTexture(L"FIRE_EFFECT"), fPOINT{ 0,0 }, 1, fPOINT{ 140,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->PlayAnimation(L"Fire_Effect");
}

