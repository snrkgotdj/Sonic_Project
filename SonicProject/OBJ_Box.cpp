#include "stdafx.h"
#include "OBJ_Box.h"
#include "ResManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Camera.h"
#include "Animation.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Player.h"
#include "KeyManager.h"

OBJ_Box::OBJ_Box()
	:m_iMove(MOVE_END)
	, m_fSpeed(50.f)
{

}


OBJ_Box::~OBJ_Box()
{
}



void OBJ_Box::Move_Top()
{
	if (pos.y >= 2399)
	{
		pos.y -= m_fSpeed * DT;

		if (pos.y <= 2399)
		{
			pos.y = 2399;
			m_iMove = MOVE_RIGHT;
		}
	}
}

void OBJ_Box::Move_Right()
{
	if (pos.x <= 11637)
	{
		pos.x += m_fSpeed * DT;

		if (pos.x >= 11637)
		{
			pos.x = 11637;
			m_iMove = MOVE_BOTTOM;
		}
	}
}

void OBJ_Box::Move_Bottom()
{
	if (pos.y <= 2527)
	{
		pos.y += m_fSpeed * DT;

		if (pos.y >= 2527)
		{
			pos.y = 2527;
			m_iMove = MOVE_LEFT;
		}
	}
}

void OBJ_Box::Move_Left()
{
	if (pos.x >= 11410)
	{
		pos.x -= m_fSpeed * DT;

		if (pos.x <= 11410)
		{
			pos.x = 11410;
			m_iMove = MOVE_TOP;
		}
	}

}

void OBJ_Box::render(HDC _dc)
{
	Anim->render(_dc, pos);

	//collider->render(_dc);
}

void OBJ_Box::update()
{
	collider->update();

	switch (m_iMove)
	{
	case MOVE_TOP:
		Move_Top();
		break;
	case MOVE_BOTTOM:
		Move_Bottom();
		break;
	case MOVE_RIGHT:
		Move_Right();
		break;
	case MOVE_LEFT:
		Move_Left();
		break;
	case MOVE_END:
		break;
	default:
		break;
	}
}

void OBJ_Box::enterCollision(Collider * _other)
{
	if (KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB) == true)
	{
		return;
	}

	// 面倒 柳青 规氢 眉农
	fPOINT ptPos = ((Player*)(_other->GetOwner()))->GetPos();
	fPOINT ptSize = ((Player*)(_other->GetOwner()))->GetSize();
	fPOINT ptOldPos = ((Player*)(_other->GetOwner()))->GetOldPos();
	
	if (ptPos.y > ptOldPos.y && ptOldPos.x < pos.x + size.x && ptOldPos.x > pos.x - size.x && ptOldPos.y <= pos.y -size.y * 2 + 5)
	{
		m_ColDirect = COL_TOP;
	}

	
	else if(ptPos.y < ptOldPos.y && ptOldPos.x < pos.x + size.x && ptOldPos.x > pos.x - size.x)
	{
		m_ColDirect = COL_BOTTOM;
	}

	else if (ptOldPos.x - ptSize.x >= pos.x + size.x-5)
	{
		if (ptOldPos.x > pos.x)
			m_ColDirect = COL_RIGHT;
		
	}

	else if (ptOldPos.x + ptSize.x <= pos.x - size.x +5)
	{
		if (ptOldPos.x < pos.x)
			m_ColDirect = COL_LEFT;
	}

	switch (m_ColDirect)
	{
	case COL_TOP:
		
		((Player*)(_other->GetOwner()))->SetYPos(pos.y - size.y * 2 + 1);
		((Player*)(_other->GetOwner()))->SetGravity(0.f);
		((Player*)(_other->GetOwner()))->SetJumpSpeed(0.f);
		((Player*)(_other->GetOwner()))->SetOnGround(true);
		((Player*)(_other->GetOwner()))->SetCanJump(true);
		((Player*)(_other->GetOwner()))->SetGradient(fPOINT{ 1,0 });
		((Player*)(_other->GetOwner()))->SetOnStair(true);
		break;
	case COL_BOTTOM:
		//((Player*)(_other->GetOwner()))->SetYPos(pos.y - size.y * 2 + 1);

		break;
	case COL_RIGHT:
		
		((Player*)(_other->GetOwner()))->SetXPos(pos.x + size.x + ptSize.x);
		((Player*)(_other->GetOwner()))->SetSpeed(0.f);

		break;
	case COL_LEFT:

		((Player*)(_other->GetOwner()))->SetXPos(pos.x - size.x - ptSize.x);
		((Player*)(_other->GetOwner()))->SetSpeed(0.f);
		break;
	default:
		break;
	}


}

void OBJ_Box::onCollision(Collider * _other)
{
	if (KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB) == true 
		|| (m_ColDirect == COL_RIGHT&& KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD) == true)
		|| (m_ColDirect == COL_LEFT&& KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD) == true))
	{
		return;
	}

	if (m_ColDirect == COL_TOP)
	{
		if (m_iMove == MOVE_RIGHT)
		{
			((Player*)(_other->GetOwner()))->MoveXPos(25);
		}
		

		else if (m_iMove == MOVE_LEFT)
		{
			((Player*)(_other->GetOwner()))->MoveXPos(-25);
		}
	}

	fPOINT ptPos = ((Player*)(_other->GetOwner()))->GetPos();
	fPOINT ptSize = ((Player*)(_other->GetOwner()))->GetSize();
	fPOINT ptOldPos = ((Player*)(_other->GetOwner()))->GetOldPos();

	if (ptPos.y < ptOldPos.y)
	{
		return;
	}

	switch (m_ColDirect)
	{
	case COL_TOP:
		if (((Player*)(_other->GetOwner()))->GetAnimation() == ANI_JUMP && ptOldPos.y > pos.y)
		{
			return;
		}

		((Player*)(_other->GetOwner()))->SetYPos(pos.y - size.y * 2 + 1);
		((Player*)(_other->GetOwner()))->SetOnGround(true);
		((Player*)(_other->GetOwner()))->SetCanJump(true);
		((Player*)(_other->GetOwner()))->SetGradient(fPOINT{ 1,0 });
		((Player*)(_other->GetOwner()))->SetOnStair(true);
		break;
	case COL_BOTTOM:
		//((Player*)(_other->GetOwner()))->SetYPos(pos.y - size.y * 2 + 1);

		break;
	case COL_RIGHT:
		
		((Player*)(_other->GetOwner()))->SetXPos(pos.x + size.x + ptSize.x);
		((Player*)(_other->GetOwner()))->SetSpeed(0.f);

		break;
	case COL_LEFT:
		((Player*)(_other->GetOwner()))->SetXPos(pos.x - size.x - ptSize.x );
		((Player*)(_other->GetOwner()))->SetSpeed(0.f);

		break;
	default:
		break;
	}

}

void OBJ_Box::exitCollision(Collider * _other)
{
	((Player*)(_other->GetOwner()))->SetOnStair(false);
}

void OBJ_Box::init(fPOINT _pos, int _move)
{
	pos = _pos;
	size = fPOINT{ 64, 64.f };
	m_iMove = _move;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Box.bmp", L"Stage_00_Box");

	Anim = new Animator;

	Anim->AddAnimation(L"Box", ResManager::Manager().FindTexture(L"Stage_00_Box"), fPOINT{ 0,0 }, 1, fPOINT{ 128,128 }, 1, 0.2f, RGB(255, 0, 255), 1);

	Anim->PlayAnimation(L"Box");
}


