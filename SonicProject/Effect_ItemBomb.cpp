#include "stdafx.h"
#include "Effect_ItemBomb.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"

Effect_ItemBomb::Effect_ItemBomb()
{
}


Effect_ItemBomb::~Effect_ItemBomb()
{
}


void Effect_ItemBomb::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Effect_ItemBomb::update()
{
	if (true == Anim->GetCurAnimation()->isFin())
	{
		OBJ::Die();
		Anim->GetCurAnimation()->SetFin(false);
	}
}

void Effect_ItemBomb::init(fPOINT _pos)
{
	pos.x = _pos.x;
	pos.y = _pos.y - 15;

	ResManager::Manager().LoadTexture(L"\\Effect\\ItemBomb.bmp", L"ITEM_BOMB");
	
	Anim = new Animator;

	Anim->AddAnimation(L"Item_Bomb", ResManager::Manager().FindTexture(L"ITEM_BOMB"), fPOINT{ 0,0 }, 1, fPOINT{ 78,76 }, 5, 0.05f, RGB(255, 0, 255), 1);
	Anim->PlayAnimation(L"Item_Bomb");
}

