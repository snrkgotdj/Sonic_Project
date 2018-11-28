#include "stdafx.h"
#include "RingItem.h"
#include "Collider.h"
#include "ResManager.h"
#include "Player.h"
#include "Texture.h"
#include "Camera.h"
#include "TimeManager.h"


RingItem::RingItem()
{
}


RingItem::~RingItem()
{
}



void RingItem::render(HDC _dc)
{
	if (DEBUGRENDER == true)
	{
		collider->render(_dc);
	}

	fPOINT CamPos = Camera::Cam().GetCamPos(pos);

	TransparentBlt(_dc, (int)CamPos.x - (int)size.x, (int)CamPos.y - (int)size.y * 2, 56, 64, m_TexDC, 0, 0, 56, 64, RGB(231, 0, 198));

	if (m_fAccTime >= 1.f && m_fAccTime < 1.1f)
	{
		TransparentBlt(_dc, (int)CamPos.x - (int)size.x, (int)CamPos.y - (int)size.y * 2, 56, 64, m_NomalDC, 0, 0, 56, 64, RGB(255, 0, 255));
	}
}

void RingItem::update()
{
	m_fAccTime += DT;

	if (m_fAccTime >= 1.05f)
	{
		m_fAccTime = 0.f;
	}
}

void RingItem::enterCollision(Collider * _other)
{
	if (ANI_JUMP == ((Player*)(_other->GetOwner()))->GetAnimation())
	{
		Item::enterCollision(_other);
		((Player*)(_other->GetOwner()))->PlusRing(10);
	}

	else if (ANI_JUMP != ((Player*)(_other->GetOwner()))->GetAnimation())
	{
		if (((Player*)(_other->GetOwner()))->GetDir() == DIR_RIGHT)
		{
			((Player*)(_other->GetOwner()))->SetSpeed(0.f);
			((Player*)(_other->GetOwner()))->SetState(PLAYER_RIGHTPUSH);
		}

		else if (((Player*)(_other->GetOwner()))->GetDir() == DIR_LEFT)
		{
			((Player*)(_other->GetOwner()))->SetSpeed(0.f);
			((Player*)(_other->GetOwner()))->SetState(PLAYER_LEFTPUSH);
		}
	}
}

void RingItem::onCollision(Collider * _other)
{
	if (ANI_JUMP != ((Player*)(_other->GetOwner()))->GetAnimation())
	{
		Item::onCollision(_other);
	}

}

void RingItem::exitCollision(Collider * _other)
{
	((Player*)(_other->GetOwner()))->SetOnStair(false);
}

void RingItem::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 28.f, 32.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Item\\Box\\RingBox.bmp", L"Box_Ring");
	m_TexDC = ResManager::Manager().FindTexture(L"Box_Ring")->GetTexDC();

	ResManager::Manager().LoadTexture(L"\\Item\\Box\\NomalBox.bmp", L"Box_Nomal");
	m_NomalDC = ResManager::Manager().FindTexture(L"Box_Nomal")->GetTexDC();
}

void RingItem::init()
{
	size = fPOINT{ 28.f, 32.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Item\\Box\\RingBox.bmp", L"Box_Ring");
	m_TexDC = ResManager::Manager().FindTexture(L"Box_Ring")->GetTexDC();

	ResManager::Manager().LoadTexture(L"\\Item\\Box\\NomalBox.bmp", L"Box_Nomal");
	m_NomalDC = ResManager::Manager().FindTexture(L"Box_Nomal")->GetTexDC();
}

