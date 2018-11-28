#include "stdafx.h"
#include "Effect_Spin.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"



Effect_Spin::Effect_Spin()
{
}


Effect_Spin::~Effect_Spin()
{
}



void Effect_Spin::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Effect_Spin::update()
{
	if (true == Anim->GetCurAnimation()->isFin())
	{
		OBJ::Die();
		Anim->GetCurAnimation()->SetFin(false);
	}
}

void Effect_Spin::init(fPOINT _pos, bool _dir)
{
	pos.y = _pos.y;

	ResManager::Manager().LoadTexture(L"\\Effect\\Spin_Effect_Right.bmp", L"Spin_Effect_Right");
	ResManager::Manager().LoadTexture(L"\\Effect\\Spin_Effect_Left.bmp", L"Spin_Effect_Left");

	Anim = new Animator;

	Anim->AddAnimation(L"Effect_Spin_Right", ResManager::Manager().FindTexture(L"Spin_Effect_Right"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 7, 0.1f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"Effect_Spin_Left", ResManager::Manager().FindTexture(L"Spin_Effect_Left"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 7, 0.1f, RGB(255, 0, 255), 1);

	if (_dir == DIR_RIGHT)
	{
		pos.x = _pos.x - 30;
		Anim->PlayAnimation(L"Effect_Spin_Right");
	}

	else if (_dir == DIR_LEFT)
	{
		pos.x = _pos.x + 30;
		Anim->PlayAnimation(L"Effect_Spin_Left");
	}
}

