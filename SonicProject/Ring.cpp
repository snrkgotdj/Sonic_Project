#include "stdafx.h"
#include "Ring.h"
#include "Collider.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
#include "Player.h"
#include "Effect_Ring.h"
#include "StageManager.h"
#include "Stage.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "UIManager.h"

Ring::Ring()
	:m_bSpitedRing(false)
	, m_ptVector{}
{
}

Ring::Ring(bool _Spit, float _Radian, COLORREF _floorColor, COLORREF _wallColor, STAGE_TYPE _type)
	: m_bCanEat(false)
	, m_fAccRender(0.f)
	, m_fAccMaintain(0.f)
	, m_bOnGround(false)
{
	m_bSpitedRing = true;
	m_iGravity = 600;
	m_fSpeed = 1000;
	m_fRadian = _Radian;
	m_FloorColor = _floorColor;
	m_WallColor = _wallColor;

	if (STAGE_START == _type)
	{
		Col_DC = ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Test\\TileMap_Col.bmp", L"Stage_Col")->GetTexDC();
	}

	else if (STAGE_00 == _type)
	{
		Col_DC = ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Stage_00_Col.bmp", L"Stage_00_Col")->GetTexDC();
	}

	else if (STAGE_01 == _type)
	{
		Col_DC = ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_01\\Stage_01_Col.bmp", L"Stage_01_Col")->GetTexDC();
	}
}

void Ring::Gravity()
{
	if (m_fSpeed > 0)
	{
		m_fSpeed -= 300 * DT;
	}

	else if (m_fSpeed < 0)
	{
		m_fSpeed = 0;
	}

	pos.y += m_iGravity * DT;
}


Ring::~Ring()
{
}

void Ring::render(HDC _dc)
{
	if (m_bSpitedRing == false)
	{
		Anim->render(_dc, pos);
	}
	
	else if (m_bSpitedRing == true)
	{
		if (m_bRenderChange == true)
			Anim->render(_dc, pos);
	}
}

void Ring::update()
{
	collider->update();
	if (((Player*)StageManager::Manager().GetCurStage()->GetListObj(Obj_PLAYER)[0])->GetShield() == SHIELD_THUNDER)
	{
		FollowPlayer();
	}

	if (m_bSpitedRing == true)
	{
		Gravity();

		RanderChange();

		RingMove();

		MaintainRing();

		CheckWall();
	}

	if (StageManager::Manager().GetCurStageType() == STAGE_FINAL)
	{
		pos.x -= 800 * DT;

		if (pos.x <= -200)
		{
			OBJ::Die();
		}
	}
}

void Ring::enterCollision(Collider * _other)
{
	
}

void Ring::onCollision(Collider * _other)
{
	UIManager::Manager().PlusScore(20);
	if (m_bSpitedRing == false)
	{
		Effect_Ring* Ring_Effect = new Effect_Ring;
		Ring_Effect->init(pos);
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(Ring_Effect);

		((Player*)(_other->GetOwner()))->PlusRing(1);
		OBJ::Die();

		SoundManager::Manager()->StopSound(L"Sound_Ring");
		SoundManager::Manager()->PlaySoundW(L"Sound_Ring", false);
	}

	else if (m_bSpitedRing == true)
	{
		if (m_bCanEat == true)
		{
			Effect_Ring* Ring_Effect = new Effect_Ring;
			Ring_Effect->init(pos);
			StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(Ring_Effect);

			((Player*)(_other->GetOwner()))->PlusRing(1);
			OBJ::Die();

			SoundManager::Manager()->StopSound(L"Sound_Ring");
			SoundManager::Manager()->PlaySoundW(L"Sound_Ring", false);
		}
	}
}

void Ring::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 16.f, 16.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Item\\Ring\\Ring.bmp", L"RING");

	Anim = new Animator;
	Anim->AddAnimation(L"Ring", ResManager::Manager().FindTexture(L"RING"), fPOINT{ 0,0 }, 1, fPOINT{ 32,32 }, 3, 0.2f, RGB(255, 0, 255), 0);

	Anim->PlayAnimation(L"Ring");
}

void Ring::init()
{
	size = fPOINT{ 16.f, 16.f };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Item\\Ring\\Ring.bmp", L"RING");

	Anim = new Animator;
	Anim->AddAnimation(L"Ring", ResManager::Manager().FindTexture(L"RING"), fPOINT{ 0,0 }, 1, fPOINT{ 32,32 }, 3, 0.2f, RGB(255, 0, 255), 0);

	Anim->PlayAnimation(L"Ring");
}




void Ring::RanderChange()
{
	m_fAccRender += 10 * DT;

	if (m_fAccRender >= 0 && m_fAccRender < 1)
	{
		m_bRenderChange = false;
	}

	else if (m_fAccRender >= 1 && m_fAccRender < 2)
	{
		m_bRenderChange = true;
	}

	else if (m_fAccRender >= 2)
	{
		m_fAccRender = 0;
	}
}

void Ring::MaintainRing()
{
	m_fAccMaintain += DT;


	if (m_fAccMaintain >= 0.5)
	{
		m_bCanEat = true;
	}

	if (m_fAccMaintain >= 5)
	{
		OBJ::Die();
	}
}

void Ring::RingMove()
{
	float a = cosf(m_fRadian);
	float b = sinf(m_fRadian);


	pos.x += (cosf(m_fRadian)) * m_fSpeed * DT;
	pos.y -= (sinf(m_fRadian)) * m_fSpeed * DT;
}

void Ring::FollowPlayer()
{
	fPOINT PlayerPos = ((Player*)StageManager::Manager().GetCurStage()->GetListObj(Obj_PLAYER)[0])->GetPos();
	fPOINT PlayerSize = ((Player*)StageManager::Manager().GetCurStage()->GetListObj(Obj_PLAYER)[0])->GetSize();

	float x1 = PlayerPos.x;
	float x2 = pos.x;
	float y1 = PlayerPos.y - PlayerSize.y;
	float y2 = pos.y - size.y;

	if (abs(pos.x - PlayerPos.x) < 300 && abs((pos.y - size.y) - (PlayerPos.y - PlayerSize.y)) < 300)
	{
		float v = sqrt((x1 - x2) * (x1 - x2) + (y2 - y1) * (y2 - y1));
		if (v == 0)
			assert(NULL);

		m_ptVector.x = (x1 - x2) / v;
		m_ptVector.y = (y2 - y1) / v;
	}

	pos.x += m_ptVector.x * 500 * DT;
	pos.y -= m_ptVector.y * 500 * DT;
}


void Ring::CheckWall()
{
	if (GetPixel(Col_DC, (int)pos.x, (int)pos.y + 1 + 200) == m_FloorColor
		|| GetPixel(Col_DC, (int)pos.x, (int)pos.y + 1 + 200) == m_WallColor)
	{
		m_fSpeed = 700;
	}

	else if (GetPixel(Col_DC, (int)pos.x - (int)size.x, (int)pos.y - (int)size.y + 200) == m_FloorColor
		|| GetPixel(Col_DC, (int)pos.x - (int)size.x, (int)pos.y - (int)size.y + 200) == m_WallColor)
	{
		m_fRadian = (float)M_PI - m_fRadian;
	}

	else if (GetPixel(Col_DC, (int)pos.x + (int)size.x, (int)pos.y - (int)size.y + 200) == m_FloorColor
		|| GetPixel(Col_DC, (int)pos.x + (int)size.x, (int)pos.y - (int)size.y + 200) == m_WallColor)
	{
		m_fRadian = (float)M_PI - m_fRadian;
	}

	if (GetPixel(Col_DC, (int)pos.x , (int)pos.y - (int)size.y*2 - 1 + 200) == m_FloorColor
		|| GetPixel(Col_DC, (int)pos.x , (int)pos.y - (int)size.y*2 -1 + 200) == m_WallColor)
	{
		m_fSpeed = 600;
	}
}
