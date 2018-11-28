#include "stdafx.h"
#include "Effect_Break.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "Player.h"

Effect_Break::Effect_Break()
{
}


Effect_Break::~Effect_Break()
{
}

void Effect_Break::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Effect_Break::update()
{
	pos.x = player->GetPos().x;
	pos.y = player->GetPos().y + 10;

	if (true == Anim->GetCurAnimation()->isFin())
	{
		OBJ::Die();
		Anim->GetCurAnimation()->SetFin(false);
	}
}

void Effect_Break::init(Player* _player)
{
	pos.x = _player->GetPos().x;
	pos.y = _player->GetPos().y + 10;

	player = _player;


	ResManager::Manager().LoadTexture(L"\\Effect\\Break.bmp", L"BREAK_EFFECT");

	Anim = new Animator;

	Anim->AddAnimation(L"Break_Effect", ResManager::Manager().FindTexture(L"BREAK_EFFECT"), fPOINT{ 0,0 }, 1, fPOINT{ 26,28 }, 4, 0.1f, RGB(255, 0, 255), 1);
	Anim->PlayAnimation(L"Break_Effect");
}

