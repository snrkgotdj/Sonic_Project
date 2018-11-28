#include "stdafx.h"
#include "Effect_Ring.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"


Effect_Ring::Effect_Ring()
{
}


Effect_Ring::~Effect_Ring()
{
}



void Effect_Ring::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Effect_Ring::update()
{
	if (true == Anim->GetCurAnimation()->isFin())
	{
		OBJ::Die();
		Anim->GetCurAnimation()->SetFin(false);
	}
}

void Effect_Ring::init(fPOINT _pos)
{
	pos = _pos;

	ResManager::Manager().LoadTexture(L"\\Effect\\Star_Effect_00.bmp", L"STAR_EFFECT");

	Anim = new Animator;

	Anim->AddAnimation(L"Star_Effect", ResManager::Manager().FindTexture(L"STAR_EFFECT"), fPOINT{ 0,0 }, 1, fPOINT{ 32,32 }, 4, 0.1f, RGB(255, 0, 255), 1);
	Anim->PlayAnimation(L"Star_Effect");
}

