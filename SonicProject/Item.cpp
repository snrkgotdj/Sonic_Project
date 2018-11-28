#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "Collider.h"
#include "Camera.h"
#include "Effect_ItemBomb.h"
#include "StageManager.h"
#include "Stage.h"
#include "ResManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

Item::Item()
	: m_fAccTime(0.f)
{
}


Item::~Item()
{
}

void Item::render(HDC _dc)
{
	if (DEBUGRENDER == true)
	{
		collider->render(_dc);
	}

	fPOINT CamPos = Camera::Cam().GetCamPos(pos);

	TransparentBlt(_dc, (int)CamPos.x - (int)size.x, (int)CamPos.y - (int)size.y * 2, 56, 64, m_TexDC, 0, 0, 56, 64, RGB(255, 0, 255));
}

void Item::enterCollision(Collider * _other)
{
	Effect_ItemBomb* pEffect = new Effect_ItemBomb;
	pEffect->init(pos);
	StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pEffect);

	((Player*)(_other->GetOwner()))->SetJumpSpeed(500);
	((Player*)(_other->GetOwner()))->SetGravity(0.f);

	((Player*)(_other->GetOwner()))->SetOnStair(false);
	OBJ::Die();

	SoundManager::Manager()->StopSound(L"Sound_Itembreak");
	SoundManager::Manager()->PlaySoundW(L"Sound_Itembreak", false);
}

void Item::onCollision(Collider * _other)
{

	if (KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB) == true)
	{
		return;
	}

	// 面倒 柳青 规氢 眉农
	fPOINT ptPos = ((Player*)(_other->GetOwner()))->GetPos();
	fPOINT ptSize = ((Player*)(_other->GetOwner()))->GetSize();
	fPOINT ptOldPos = ((Player*)(_other->GetOwner()))->GetOldPos();

	if (ptPos.y > ptOldPos.y && ptOldPos.x < pos.x + size.x && ptOldPos.x > pos.x - size.x && ptOldPos.y < pos.y- size.y*2 + 5)
	{
		m_ColDirect = COL_TOP;
	}


	else if (ptPos.y < ptOldPos.y && ptOldPos.x < pos.x + size.x && ptOldPos.x > pos.x - size.x)
	{
		m_ColDirect = COL_BOTTOM;
	}

	else if (ptOldPos.x - ptSize.x >= pos.x + size.x - 1 && ptOldPos.y > pos.y - size.y*2 + 4 && ptOldPos.y < pos.y )
	{
		if (ptOldPos.x > pos.x)
			m_ColDirect = COL_RIGHT;

	}

	else if (ptOldPos.x + ptSize.x <= pos.x - size.x + 1 && ptOldPos.y > pos.y - size.y * 2 + 4 && ptOldPos.y < pos.y)
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
		((Player*)(_other->GetOwner()))->SetState(PLAYER_LEFTPUSH);
		((Player*)(_other->GetOwner()))->SetXPos(pos.x + size.x + ptSize.x - 1);
		((Player*)(_other->GetOwner()))->SetSpeed(0.f);

		if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_AWAY))
		{
			((Player*)(_other->GetOwner()))->SetXPos(pos.x + size.x + ptSize.x);
		}

		if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_TAB))
		{
			((Player*)(_other->GetOwner()))->SetXPos(pos.x + size.x + ptSize.x);
		}

		break;
	case COL_LEFT:
		((Player*)(_other->GetOwner()))->SetState(PLAYER_RIGHTPUSH);
		((Player*)(_other->GetOwner()))->SetXPos(pos.x - size.x - ptSize.x + 1);
		((Player*)(_other->GetOwner()))->SetSpeed(0.f);

		if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_AWAY))
		{
			((Player*)(_other->GetOwner()))->SetXPos(pos.x - size.x - ptSize.x);
		}

		if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_TAB))
		{
			((Player*)(_other->GetOwner()))->SetXPos(pos.x - size.x - ptSize.x);
		}

		break;
	default:
		break;
	}
	
}

void Item::exitCollision(Collider * _other)
{
	((Player*)(_other->GetOwner()))->SetOnStair(false);
}
