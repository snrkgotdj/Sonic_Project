#include "stdafx.h"
#include "LifeBox.h"
#include "Collider.h"
#include "ResManager.h"
#include "Player.h"
#include "Texture.h"
#include "Camera.h"
#include "TimeManager.h"
#include "UIManager.h"
#include "StageManager.h"

LifeBox::LifeBox()
{
}


LifeBox::~LifeBox()
{
}



void LifeBox::render(HDC _dc)
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

void LifeBox::update()
{
	m_fAccTime += DT;

	if (m_fAccTime >= 1.05f)
	{
		m_fAccTime = 0.f;
	}
}

void LifeBox::enterCollision(Collider * _other)
{
	if (ANI_JUMP == ((Player*)(_other->GetOwner()))->GetAnimation())
	{
		Item::enterCollision(_other);
		UIManager::Manager().PlusLife(1);
		return;
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

void LifeBox::onCollision(Collider * _other)
{
	if (ANI_JUMP != ((Player*)(_other->GetOwner()))->GetAnimation())
	{
		Item::onCollision(_other);
	}
	
}

void LifeBox::exitCollision(Collider * _other)
{
	((Player*)(_other->GetOwner()))->SetOnStair(false);
}

void LifeBox::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 28.f, 32.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	Charactor_Mode Charactor = StageManager::Manager().GetCharactorMode();

	if (Charactor == KNUCKLE_MODE)
	{
		ResManager::Manager().LoadTexture(L"\\Item\\Box\\KnuckleBox.bmp", L"Box_Knuckle");
		m_TexDC = ResManager::Manager().FindTexture(L"Box_Knuckle")->GetTexDC();
	}
	
	else if (Charactor == SONIC_MODE)
	{
		ResManager::Manager().LoadTexture(L"\\Item\\Box\\SonicBox.bmp", L"Box_Sonic");
		m_TexDC = ResManager::Manager().FindTexture(L"Box_Sonic")->GetTexDC();
	}

	else if (Charactor == TAIL_MODE)
	{
		ResManager::Manager().LoadTexture(L"\\Item\\Box\\TailBox.bmp", L"Box_Tail");
		m_TexDC = ResManager::Manager().FindTexture(L"Box_Tail")->GetTexDC();
	}

	ResManager::Manager().LoadTexture(L"\\Item\\Box\\NomalBox.bmp", L"Box_Nomal");
	m_NomalDC = ResManager::Manager().FindTexture(L"Box_Nomal")->GetTexDC();
}

void LifeBox::init()
{
	size = fPOINT{ 28.f, 32.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	Charactor_Mode Charactor = StageManager::Manager().GetCharactorMode();

	if (Charactor == KNUCKLE_MODE)
	{
		ResManager::Manager().LoadTexture(L"\\Item\\Box\\KnuckleBox.bmp", L"Box_Knuckle");
		m_TexDC = ResManager::Manager().FindTexture(L"Box_Knuckle")->GetTexDC();
	}

	else if (Charactor == SONIC_MODE)
	{
		ResManager::Manager().LoadTexture(L"\\Item\\Box\\SonicBox.bmp", L"Box_Sonic");
		m_TexDC = ResManager::Manager().FindTexture(L"Box_Sonic")->GetTexDC();
	}

	else if (Charactor == TAIL_MODE)
	{
		ResManager::Manager().LoadTexture(L"\\Item\\Box\\TailBox.bmp", L"Box_Tail");
		m_TexDC = ResManager::Manager().FindTexture(L"Box_Tail")->GetTexDC();
	}

	ResManager::Manager().LoadTexture(L"\\Item\\Box\\NomalBox.bmp", L"Box_Nomal");
	m_NomalDC = ResManager::Manager().FindTexture(L"Box_Nomal")->GetTexDC();
}

