#include "stdafx.h"
#include "ThunderItem.h"
#include "Collider.h"
#include "ResManager.h"
#include "Player.h"
#include "Texture.h"
#include "Camera.h"
#include "TimeManager.h"


ThunderItem::ThunderItem()
{
}


ThunderItem::~ThunderItem()
{
}



void ThunderItem::render(HDC _dc)
{
	Item::render(_dc);

	if (m_fAccTime >= 1.f && m_fAccTime < 1.1f)
	{
		fPOINT CamPos = Camera::Cam().GetCamPos(pos);

		TransparentBlt(_dc, (int)CamPos.x - (int)size.x, (int)CamPos.y - (int)size.y * 2, 56, 64, m_NomalDC, 0, 0, 56, 64, RGB(255, 0, 255));
	}
}

void ThunderItem::update()
{
	m_fAccTime += DT;

	if (m_fAccTime >= 1.05f)
	{
		m_fAccTime = 0.f;
	}
}

void ThunderItem::enterCollision(Collider * _other)
{
	if (ANI_JUMP == ((Player*)(_other->GetOwner()))->GetAnimation())
	{
		Item::enterCollision(_other);
		((Player*)(_other->GetOwner()))->SetShieldState(SHIELD_THUNDER);
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

void ThunderItem::onCollision(Collider * _other)
{
	if (ANI_JUMP != ((Player*)(_other->GetOwner()))->GetAnimation())
	{
		Item::onCollision(_other);
	}

}

void ThunderItem::exitCollision(Collider * _other)
{
	((Player*)(_other->GetOwner()))->SetOnStair(false);
}

void ThunderItem::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 28.f, 32.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Item\\Box\\ThunderBox.bmp", L"Box_Thunder");
	m_TexDC = ResManager::Manager().FindTexture(L"Box_Thunder")->GetTexDC();
	ResManager::Manager().LoadTexture(L"\\Item\\Box\\NomalBox.bmp", L"Box_Nomal");
	m_NomalDC = ResManager::Manager().FindTexture(L"Box_Nomal")->GetTexDC();
}

void ThunderItem::init()
{
	size = fPOINT{ 28.f, 32.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Item\\Box\\ThunderBox.bmp", L"Box_Thunder");
	m_TexDC = ResManager::Manager().FindTexture(L"Box_Thunder")->GetTexDC();
	ResManager::Manager().LoadTexture(L"\\Item\\Box\\NomalBox.bmp", L"Box_Nomal");
	m_NomalDC = ResManager::Manager().FindTexture(L"Box_Nomal")->GetTexDC();
}

