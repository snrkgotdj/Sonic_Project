#include "stdafx.h"
#include "NillWall.h"
#include "OBJ_Box.h"
#include "ResManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Camera.h"
#include "Animation.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Player.h"
#include "StageManager.h"
#include "Stage.h"
#include "SoundManager.h"


NillWall::NillWall()
	:m_eMoveState(MOVE_END)
	, m_NillCol(NULL)
	, m_ptOriginPos{}
	, m_bMove(true)
{
}


NillWall::~NillWall()
{
	if (m_NillCol != NULL)
		delete m_NillCol;
}


void NillWall::render(HDC _dc)
{
	Anim->render(_dc, pos);

}

void NillWall::update()
{
	collider->update();

	m_NillCol->update();

	CheckNill();

	if (m_eMoveState == MOVE_RIGHT)
	{
		if (pos.x < 150 + m_ptOriginPos.x&& m_bMove == true)
		{
			pos.x += 150 * DT;
			if (pos.x >= 150 + m_ptOriginPos.x)
			{
				pos.x = 150 + m_ptOriginPos.x;
				m_eMoveState = MOVE_LEFT;
			}
		}
	}

	else if (m_eMoveState == MOVE_LEFT && m_bMove == true)
	{
		if (pos.x > m_ptOriginPos.x - 150 && m_bMove == true)
		{
			pos.x -= 150 * DT;
			if (pos.x <= m_ptOriginPos.x - 150)
			{
				pos.x = m_ptOriginPos.x - 150;
				m_eMoveState = MOVE_RIGHT;
			}
		}

	}
}

void NillWall::enterCollision(Collider * _other)
{
	if (((Player*)(_other->GetOwner()))->GetPos().y >= ((Player*)(_other->GetOwner()))->GetOldPos().y
		&& ((Player*)(_other->GetOwner()))->GetOldPos().y <= pos.y - size.y * 2 + 5)
	{
		((Player*)(_other->GetOwner()))->SetYPos(pos.y - size.y * 2 + 1);
		((Player*)(_other->GetOwner()))->SetGravity(0.f);
		((Player*)(_other->GetOwner()))->SetJumpSpeed(0.f);
		((Player*)(_other->GetOwner()))->SetOnGround(true);
		((Player*)(_other->GetOwner()))->SetCanJump(true);
		((Player*)(_other->GetOwner()))->SetGradient(fPOINT{ 1,0 });
		((Player*)(_other->GetOwner()))->SetOnStair(true);
	}

}

void NillWall::onCollision(Collider * _other)
{
	if (m_eMoveState == MOVE_RIGHT && m_bMove == true)
	{
		((Player*)(_other->GetOwner()))->MoveXPos(75);
	}

	else if (m_eMoveState == MOVE_LEFT && m_bMove == true)
	{
		((Player*)(_other->GetOwner()))->MoveXPos(-75);
	}

	if (((Player*)(_other->GetOwner()))->GetPos().y >= ((Player*)(_other->GetOwner()))->GetOldPos().y
		&& ((Player*)(_other->GetOwner()))->GetOldPos().y <= pos.y - size.y * 2 + 5)
	{
		((Player*)(_other->GetOwner()))->SetOnGround(true);
		((Player*)(_other->GetOwner()))->SetCanJump(true);
		((Player*)(_other->GetOwner()))->SetYPos(pos.y - size.y * 2 + 1);
		((Player*)(_other->GetOwner()))->SetGravity(0.f);
		((Player*)(_other->GetOwner()))->SetJumpSpeed(0.f);
	}
}

void NillWall::exitCollision(Collider * _other)
{
	((Player*)(_other->GetOwner()))->SetOnStair(false);
}

void NillWall::init(fPOINT _pos, MOVE_STATE _state)
{
	pos = _pos;
	size = fPOINT{ 94, 32 };
	m_ptOriginPos = pos;
	m_eMoveState = _state;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	m_NillCol = new Collider(this);
	m_NillCol->SetType(COL_RECT);
	m_NillCol->SetOffset(fPOINT{ 90, 0 });
	m_NillCol->SetSize(fPOINT{ 20,15 });

	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Right_NillWall.bmp", L"Stage_00_Right_NillWall");
	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Left_NillWall.bmp", L"Stage_00_Left_NillWall");


	Anim = new Animator;

	Anim->AddAnimation(L"Right_NillWall", ResManager::Manager().FindTexture(L"Stage_00_Right_NillWall"), fPOINT{ 0,0 }, 1, fPOINT{ 192,64 }, 1, 0.2f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"Left_NillWall", ResManager::Manager().FindTexture(L"Stage_00_Left_NillWall"), fPOINT{ 0,0 }, 1, fPOINT{ 192,64 }, 1, 0.2f, RGB(255, 0, 255), 1);

	if(_state == MOVE_RIGHT)
		Anim->PlayAnimation(L"Right_NillWall");

	else if (_state == MOVE_LEFT)
		Anim->PlayAnimation(L"Left_NillWall");

}

void NillWall::init(MOVE_STATE _state)
{
	size = fPOINT{ 96, 32 };

	m_ptOriginPos = pos;
	m_eMoveState = _state;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	m_NillCol = new Collider(this);
	m_NillCol->SetType(COL_RECT);
	if (m_eMoveState == MOVE_RIGHT)
	{
		m_NillCol->SetOffset(fPOINT{ 80, 0 });
	}

	else if (m_eMoveState == MOVE_LEFT)
	{
		m_NillCol->SetOffset(fPOINT{ -80, 0 });
	}
	
	m_NillCol->SetSize(fPOINT{ 20,15 });

	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Right_NillWall.bmp", L"Stage_00_Right_NillWall");
	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Left_NillWall.bmp", L"Stage_00_Left_NillWall");


	Anim = new Animator;

	Anim->AddAnimation(L"Right_NillWall", ResManager::Manager().FindTexture(L"Stage_00_Right_NillWall"), fPOINT{ 0,0 }, 1, fPOINT{ 192,64 }, 1, 0.2f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"Left_NillWall", ResManager::Manager().FindTexture(L"Stage_00_Left_NillWall"), fPOINT{ 0,0 }, 1, fPOINT{ 192,64 }, 1, 0.2f, RGB(255, 0, 255), 1);

	if (m_eMoveState == MOVE_RIGHT)
		Anim->PlayAnimation(L"Right_NillWall");

	else if (m_eMoveState == MOVE_LEFT)
		Anim->PlayAnimation(L"Left_NillWall");


}

void NillWall::CheckNill()
{
	Player* pPlayer = ((Player*)(StageManager::Manager().GetCurStage()->GetListObj(Obj_PLAYER)[0]));


	if (ANI_HITTED == pPlayer->GetAnimation() || pPlayer->GetInvincible() == true || pPlayer->isSuper()==true)
	{
		return;
	}

	fPOINT PlayerPos = pPlayer->GetPos();
	fPOINT PlayerSize = pPlayer->GetSize();
	
	
	if (abs(PlayerPos.x - m_NillCol->GetPos().x) < abs(PlayerSize.x + m_NillCol->GetSize().x) &&
		abs((PlayerPos.y - PlayerSize.y) - (m_NillCol->GetPos().y - m_NillCol->GetSize().y)) < abs(PlayerSize.y + m_NillCol->GetSize().y))
	{
		if (m_eMoveState == MOVE_LEFT)
		{
			pPlayer->SetDir(DIR_RIGHT);
			pPlayer->SetState(PLAYER_HITTED);
			pPlayer->SetSpeed(-250.f);
			pPlayer->SetGravity(0.f);
			pPlayer->SetJumpSpeed(300.f);
			pPlayer->SetInvincible(true);
			if (pPlayer->GetShield() == SHIELD_END)
			{
				if (0 != pPlayer->GetRingCnt())
				{
					SoundManager::Manager()->PlaySoundW(L"Sound_SpitRing", false);
					pPlayer->SpitOutRing();
					pPlayer->SetRingCnt(0);
				}

				else
				{
					SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
				}

			}
			else if (pPlayer->GetShield() != SHIELD_END)
			{
				SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
			}

		}

		else if (m_eMoveState == MOVE_RIGHT)
		{
			pPlayer->SetDir(DIR_LEFT);
			pPlayer->SetState(PLAYER_HITTED);
			pPlayer->SetSpeed(+250.f);
			pPlayer->SetGravity(0.f);
			pPlayer->SetJumpSpeed(300.f);
			pPlayer->SetInvincible(true);
			if (pPlayer->GetShield() == SHIELD_END)
			{
				if (0 != pPlayer->GetRingCnt())
				{
					SoundManager::Manager()->PlaySoundW(L"Sound_SpitRing", false);
					pPlayer->SpitOutRing();
					pPlayer->SetRingCnt(0);
				}
				else
				{
					SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
				}
			}

			else if (pPlayer->GetShield() != SHIELD_END)
			{
				SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
			}
		}
	}
}