#include "stdafx.h"
#include "Effect_Stone.h"
#include "ResManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "TimeManager.h"

Effect_Stone::Effect_Stone()
	:m_bDir(DIR_RIGHT)
	, m_fAccTime(0.f)
{
}


Effect_Stone::~Effect_Stone()
{
}



void Effect_Stone::init(fPOINT _pos, bool _Dir)
{
	pos = _pos;

	m_bDir = _Dir;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });


	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Stone.bmp", L"Stone");

	Anim = new Animator;

	Anim->AddAnimation(L"Stone", ResManager::Manager().FindTexture(L"Stone"), fPOINT{ 0,0 }, 1, fPOINT{ 46,46 }, 2, 0.05f, RGB(255, 0, 255), 0);

	Anim->PlayAnimation(L"Stone");
}

void Effect_Stone::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Effect_Stone::update()
{
	m_fAccTime += 2*DT;
	pos.x -= 200 * DT;

	if (m_bDir == DIR_RIGHT)
	{
		pos.y -= 200 * DT;
	}

	else if (m_bDir == DIR_LEFT)
	{
		pos.y += 200 * DT;
	}

	if (m_fAccTime >= 1)
	{
		OBJ::Die();
	}
}
