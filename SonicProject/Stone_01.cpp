#include "stdafx.h"
#include "Stone_01.h"
#include "ResManager.h"
#include "Collider.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Effect_Stone.h"
#include "StageManager.h"
#include "Stage.h"
#include "SoundManager.h"

Stone_01::Stone_01()
	:m_fSpeed(600)
{
}


Stone_01::~Stone_01()
{
}


void Stone_01::init(fPOINT _pos)
{
	pos = _pos;

	size = fPOINT{ 48,48 };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });


	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Stone_01.bmp", L"Stone_01");

	Anim = new Animator;

	Anim->AddAnimation(L"Stone", ResManager::Manager().FindTexture(L"Stone_01"), fPOINT{ 0,0 }, 1, fPOINT{ 96,96 }, 1, 0.5f, RGB(255, 0, 255), 1);

	Anim->PlayAnimation(L"Stone");
}

void Stone_01::update()
{
	collider->update();

	//pos.x -= 100 * DT;

	pos.x -= m_fSpeed * DT;

	if (pos.x <= -200)
	{
		OBJ::Die();
	}
}

void Stone_01::enterCollision(Collider * _other)
{
	SoundManager::Manager()->StopSound(L"Sound_StoneBreak");
	SoundManager::Manager()->PlaySoundW(L"Sound_StoneBreak", false);

	Effect_Stone * pStone_Effect_00 = new Effect_Stone;
	pStone_Effect_00->init(fPOINT{ getRandomNumber(pos.x - size.x, pos.x + size.x) , getRandomNumber(pos.y - size.y, pos.y + size.y) }, DIR_RIGHT);
	StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pStone_Effect_00);

	Effect_Stone * pStone_Effect_01 = new Effect_Stone;
	pStone_Effect_01->init(fPOINT{ getRandomNumber(pos.x - size.x, pos.x + size.x),getRandomNumber(pos.y - size.y, pos.y + size.y) }, DIR_LEFT);
	StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pStone_Effect_01);

	Effect_Stone * pStone_Effect_02 = new Effect_Stone;
	pStone_Effect_02->init(fPOINT{ getRandomNumber(pos.x - size.x, pos.x + size.x) , getRandomNumber(pos.y - size.y, pos.y + size.y) }, DIR_RIGHT);
	StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pStone_Effect_02);

	OBJ::Die();

}

