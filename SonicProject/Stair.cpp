#include "stdafx.h"
#include "Stair.h"
#include "OBJ_Box.h"
#include "ResManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Camera.h"
#include "Animation.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Player.h"

Stair::Stair()
	:m_eMoveState(MOVE_END)
{
}


Stair::~Stair()
{
}



void Stair::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Stair::update()
{
	collider->update();

	if (m_eMoveState == MOVE_RIGHT)
	{
		pos.x += 100 * DT;

		if (pos.x >= 7330)
		{
			pos.x = 7330;

			m_eMoveState = MOVE_LEFT;
		}
	}

	else if (m_eMoveState == MOVE_LEFT)
	{
		pos.x -= 100 * DT;

		if (pos.x <= 6872)
		{
			pos.x = 6872;

			m_eMoveState = MOVE_RIGHT;
		}
	}
}

void Stair::enterCollision(Collider * _other)
{
	if (((Player*)(_other->GetOwner()))->GetPos().y >= ((Player*)(_other->GetOwner()))->GetOldPos().y
		&& ((Player*)(_other->GetOwner()))->GetOldPos().y <= pos.y - size.y * 2 + 5 )
	{
		((Player*)(_other->GetOwner()))->SetYPos(pos.y - size.y * 2 + 1);
		((Player*)(_other->GetOwner()))->SetGravity(0.f);
		((Player*)(_other->GetOwner()))->SetJumpSpeed(0.f);
		((Player*)(_other->GetOwner()))->SetOnGround(true);
		((Player*)(_other->GetOwner()))->SetCanJump(true);
		((Player*)(_other->GetOwner()))->SetGradient(fPOINT{1,0});
		((Player*)(_other->GetOwner()))->SetOnStair(true);
	}
}

void Stair::onCollision(Collider * _other)
{
	if (m_eMoveState == MOVE_RIGHT)
	{
		((Player*)(_other->GetOwner()))->MoveXPos(50);
	}

	else if (m_eMoveState == MOVE_LEFT)
	{
		((Player*)(_other->GetOwner()))->MoveXPos(-50);
	}

	if (((Player*)(_other->GetOwner()))->GetPos().y >= ((Player*)(_other->GetOwner()))->GetOldPos().y
		&& ((Player*)(_other->GetOwner()))->GetOldPos().y <= pos.y - size.y * 2 + 5)
	{
		((Player*)(_other->GetOwner()))->SetOnGround(true);
		((Player*)(_other->GetOwner()))->SetCanJump(true);
		((Player*)(_other->GetOwner()))->SetYPos(pos.y - size.y * 2 +1);
		((Player*)(_other->GetOwner()))->SetGravity(0.f);
		((Player*)(_other->GetOwner()))->SetJumpSpeed(0.f);
	}
}

void Stair::exitCollision(Collider * _other)
{
	((Player*)(_other->GetOwner()))->SetOnStair(false);

}

void Stair::init(fPOINT _pos, MOVE_STATE _state)
{
	pos = _pos;
	size = fPOINT{ 48, 16 };

	m_eMoveState = _state;
	
	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Stair.bmp", L"Stage_00_Stair");

	Anim = new Animator;

	Anim->AddAnimation(L"Stair", ResManager::Manager().FindTexture(L"Stage_00_Stair"), fPOINT{ 0,0 }, 1, fPOINT{ 96,32 }, 1, 0.2f, RGB(255, 0, 255), 1);

	Anim->PlayAnimation(L"Stair");
}

