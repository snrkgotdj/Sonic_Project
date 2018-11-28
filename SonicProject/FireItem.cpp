#include "stdafx.h"
#include "FireItem.h"
#include "ResManager.h"
#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "Camera.h"
#include "Player.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "Camera.h"

FireItem::FireItem()
{
}


FireItem::~FireItem()
{
}


void FireItem::render(HDC _dc)
{
	Item::render(_dc);
	
	if (m_fAccTime >= 1.f && m_fAccTime < 1.1f)
	{
		fPOINT CamPos = Camera::Cam().GetCamPos(pos);

		TransparentBlt(_dc, (int)CamPos.x - (int)size.x, (int)CamPos.y - (int)size.y * 2, 56, 64, m_NomalDC, 0, 0, 56, 64, RGB(255, 0, 255));
	}
}

void FireItem::update()
{
	m_fAccTime += DT;

	if (m_fAccTime >= 1.05f)
	{
		m_fAccTime = 0.f;
	}
}

void FireItem::enterCollision(Collider * _other)
{
	if (ANI_JUMP == ((Player*)(_other->GetOwner()))->GetAnimation() || ANI_ROLL == ((Player*)(_other->GetOwner()))->GetAnimation())
	{
		Item::enterCollision(_other);
		((Player*)(_other->GetOwner()))->SetShieldState(SHIELD_FIRE);

		return;
	}


	// 面倒 柳青 规氢 眉农
	fPOINT ptPos = ((Player*)(_other->GetOwner()))->GetPos();
	fPOINT ptSize = ((Player*)(_other->GetOwner()))->GetSize();
	fPOINT ptOldPos = ((Player*)(_other->GetOwner()))->GetOldPos();
	if (ptOldPos.y <= pos.y - size.y * 2 + 5)
	{
		if (ptOldPos.y < ptPos.y)
		{
			m_ColDirect = COL_TOP;
		}
	}

	else if (ptOldPos.y - ptSize.y * 2 - 5 >= pos.y)
	{
		if (ptOldPos.y > ptPos.y)
		{
			m_ColDirect = COL_BOTTOM;
		}
	}

	else
	{
		if (ptOldPos.x < pos.x)
			m_ColDirect = COL_LEFT;
		else if (ptOldPos.x > pos.x)
			m_ColDirect = COL_RIGHT;
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
		((Player*)(_other->GetOwner()))->SetXPos(pos.x + size.x + ptSize.x + 1);
		((Player*)(_other->GetOwner()))->SetSpeed(0.f);

		break;
	case COL_LEFT:
		((Player*)(_other->GetOwner()))->SetState(PLAYER_RIGHTPUSH);
		((Player*)(_other->GetOwner()))->SetXPos(pos.x - size.x - ptSize.x - 1);
		((Player*)(_other->GetOwner()))->SetSpeed(0.f);
		break;
	default:
		break;
	}
	
}

void FireItem::onCollision(Collider * _other)
{
	if (ANI_JUMP != ((Player*)(_other->GetOwner()))->GetAnimation())
	{
		Item::onCollision(_other);
	}

}

void FireItem::exitCollision(Collider * _other)
{
	Item::exitCollision(_other);
}

void FireItem::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 28.f, 32.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Item\\Box\\FireBox.bmp", L"Box_Fire");
	ResManager::Manager().LoadTexture(L"\\Item\\Box\\NomalBox.bmp", L"Box_Nomal");

	m_TexDC = ResManager::Manager().FindTexture(L"Box_Fire")->GetTexDC();
	m_NomalDC = ResManager::Manager().FindTexture(L"Box_Nomal")->GetTexDC();
}

void FireItem::init()
{
	size = fPOINT{ 28.f, 32.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Item\\Box\\FireBox.bmp", L"Box_Fire");
	
	ResManager::Manager().LoadTexture(L"\\Item\\Box\\NomalBox.bmp", L"Box_Nomal");

	m_TexDC = ResManager::Manager().FindTexture(L"Box_Fire")->GetTexDC();

	m_NomalDC = ResManager::Manager().FindTexture(L"Box_Nomal")->GetTexDC();
}

