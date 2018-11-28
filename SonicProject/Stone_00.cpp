#include "stdafx.h"
#include "Stone_00.h"
#include "ResManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Effect_Stone.h"
#include "StageManager.h"
#include "Stage.h"
#include "SoundManager.h"


Stone_00::Stone_00()
	:m_fSpeed(1000.f)
{
}


Stone_00::~Stone_00()
{
}


void Stone_00::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 32,32 };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });


	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Stone_00.bmp", L"Stone_00");

	Anim = new Animator;

	Anim->AddAnimation(L"Stone_00", ResManager::Manager().FindTexture(L"Stone_00"), fPOINT{ 0,0 }, 1, fPOINT{ 64,64 }, 1, 0.5f, RGB(255, 0, 255), 1);

	Anim->PlayAnimation(L"Stone_00");
}


void Stone_00::update()
{
	collider->update();
	pos.x -= m_fSpeed * DT;

	if (pos.x <= -200)
	{
		OBJ::Die();
	}
}

void Stone_00::enterCollision(Collider * _other)
{
	SoundManager::Manager()->StopSound(L"Sound_StoneBreak");
	SoundManager::Manager()->PlaySoundW(L"Sound_StoneBreak", false);

	Effect_Stone * pStone_Effect_00 = new Effect_Stone;
	pStone_Effect_00->init(fPOINT{ getRandomNumber(pos.x - size.x, pos.x + size.x) , getRandomNumber(pos.y - size.y, pos.y + size.y) }, DIR_RIGHT);
	StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pStone_Effect_00);

	Effect_Stone * pStone_Effect_01 = new Effect_Stone;
	pStone_Effect_01->init(fPOINT{ getRandomNumber(pos.x - size.x, pos.x + size.x),getRandomNumber(pos.y - size.y, pos.y + size.y) }, DIR_LEFT);
	StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pStone_Effect_01);

	OBJ::Die();
}
