#include "stdafx.h"
#include "Emerald.h"
#include "ResManager.h"
#include "StageManager.h"
#include "Stage.h"
#include "Animator.h"
#include "Collider.h"


Emerald::Emerald()
{
}

Emerald::~Emerald()
{
}


void Emerald::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 31.f, 30.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Item\\Emerald.bmp", L"Emerald");

	Anim = new Animator;

	Anim->AddAnimation(L"Emerald", ResManager::Manager().FindTexture(L"Emerald"), fPOINT{ 0,0 }, 1, fPOINT{ 128,96 }, 21, 0.025f, RGB(255, 0, 255), 0);

	Anim->PlayAnimation(L"Emerald");
}

void Emerald::render(HDC _dc)
{
	Anim->render(_dc, pos);

	//collider->render(_dc);
}

void Emerald::update()
{
}

void Emerald::enterCollision(Collider * _other)
{
	StageManager::Manager().ChangeStage(STAGE_FINISH);
}
