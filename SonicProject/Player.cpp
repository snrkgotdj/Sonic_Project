#include "stdafx.h"
#include "Player.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "Camera.h"
#include "Collider.h"
#include "StageManager.h"
#include "Stage.h"
#include "ResManager.h"
#include "Animator.h"
#include "Texture.h"
#include "OBJ.h"
#include "FireShield.h"
#include "FireShield_Back.h"
#include "WaterShield.h"
#include "ThunderShield.h"
#include "Effect_Spin.h"
#include "Effect_Break.h"
#include "SoundManager.h"
#include "Ring.h"


Player::Player()
	: state(PLAYER_STOP)
	, pTex_Col(NULL)
	, m_bDir(DIR_RIGHT)
	, m_bOnGround(false)
	, m_bChangeLayer(false)
	, m_bTurn(false)
	, m_bRightWallOn(false)
	, m_bLeftWallOn(false)
	, m_bClimbOn(false)
	, m_bCanJump(false)
	, m_bInvincible(false)
	, m_bRenderOn(true)
	, m_bOnStair(false)
	, m_Animation(ANI_STOP)
	, m_CheckType(CHECK_END)
	, m_eShield(SHIELD_END)
	, m_eOldShield(SHIELD_END)
	, m_fAccSpeed(0.f)
	, m_fInvincibleTime(0.f)
	, m_fSpeed(0.f)
	, m_fJumpSpeed(0.f)
	, m_fEndClimbTime(0.f)
	, m_fSpringSpeed(0.f)
	, m_fAccRender(0.f)
	, m_fBreakSpeed(0.f)
	, m_ptGravity{0.f, 1.f}
	, m_ptGradient{0.f, 0.f}
	, m_ptJumpGradient{0.f, 0.f}
	, FloorColor(RGB(0, 192, 224))
	, WallColor(RGB(160, 96, 64))
	, ChangeColor(RGB(150, 150, 150))
	, m_iRingCnt(0)
	, m_iLife(0)
	, m_bSuperSonic(false)
	, m_bPause(false)
{
}


Player::~Player()
{
	OBJ::~OBJ();
}


void Player::update()
{
	Camera::Cam().FollowPoint(pos);
	collider->update();

	m_ptOldPos = pos;
	m_ptOldGradient = m_ptGradient;
	m_eOldAnimation = m_Animation;

	switch (state)
	{
	case PLAYER_STOP:
		Player_Stop();
		break;
	case PLAYER_iDLE:
		Player_Idle();
		break;
	case PLAYER_JUMP:
		Player_Jump();
		break;
	case PLAYER_SIT:
		Player_Sit();
		break;
	case PLAYER_LOOKUP:
		Player_Lookup();
		break;
	case PLAYER_RIGHTWalK:
		Player_RightWalk();
		break;
	case PLAYER_LEFTWalK:
		Player_LeftWalk();
		break;
	case PLAYER_RIGHTBREAK:
		Player_RightBreak();
		break;
	case PLAYER_LEFTBREAK:
		Player_LeftBreak();
		break;
	case PLAYER_SPIN:
		Player_Spin();
		break;
	case PLAYER_SPINMOVE:
		Player_SpinMove();
		break;
	case PLAYER_SPINNING:
		Player_Spining();
		break;
	case PLAYER_DROP:
		Player_Drop();
		break;
	case PLAYER_RIGHTPUSH:
		Player_RightPush();
		break;
	case PLAYER_LEFTPUSH:
		Player_LeftPush();
		break;
	case PLAYER_LEFTCLIMB:
		Player_LeftClimb();
		break;
	case PLAYER_RIGHTCLIMB:
		Player_RightClimb();
		break;
	case PLAYER_ENDCLIMB_00:
		Player_EndClimb_00();
		break;
	case PLAYER_ENDCLIMB_01:
		Player_EndClimb_01();
		break;
	case PLAYER_ENDCLIMB_02:
		Player_EndClimb_02();
		break;
	case PLAYER_SPRINGJUMP:
		Player_SpringJump();
		break;
	case PLAYER_HITTED:
		Player_Hitted();
		break;
	case PLAYER_FINISH:
		Player_Finish();

	case PLAYER_END:
		break;
	default:
		break;
	}

	if (state != PLAYER_JUMP && m_bOnStair == false)
		CheckGradient();

	Jump_Move();

	Spring_Jump();

	GravityON();
	
	if(m_bOnStair == false)
		CheckPixel();

	Limit();
	
	CharactorMove();

	adjustCol();
	
	SwitchAnimation();

	CheckWall();

	ChangeLayer();

	ShieldON();

	if (m_Animation != m_eOldAnimation)
	{
		m_AccTime = 0;
	}
	if (m_bInvincible == true)
	{
		InvincibleTime();
	}
	
	m_eOldShield = m_eShield;
}


void Player::CheckGradient()
{
	CheckDownGradient();
	CheckUpGradient();
	CheckRightGradient();
	CheckLeftGradient();
}

void Player::CheckPixel()
{
	UpPixcel();
	DownPixcel();
	LeftPixcel();
	RightPixcel();
}

void Player::Limit()
{
	if (pos.x <= size.x)
		pos.x = size.x;

	if (m_bSuperSonic == false)
	{
		if (m_fSpeed >= 1500)
			m_fSpeed = 1500;
		else if (m_fSpeed <= -1500)
			m_fSpeed = -1500;
	}

	else if (m_bSuperSonic == true)
	{
		if (m_fSpeed >= 2000)
			m_fSpeed = 2000;
		else if (m_fSpeed <= -2000)
			m_fSpeed = -2000;
	}
	

	if (state != PLAYER_JUMP && state != PLAYER_SPRINGJUMP && (m_ptGravity.y - m_ptGradient.y * m_fSpeed - m_fJumpSpeed) >= 1000)
	{
		m_ptGravity.y = 1000 + m_ptGradient.y*m_fSpeed + m_fJumpSpeed;
	}

	
	if(Camera::Cam().isPause()== true)
	if (pos.x >= Camera::Cam().GetLimit().x - size.x)
	{
		pos.x = Camera::Cam().GetLimit().x - size.x;
	}
	
	else if (pos.x <= Camera::Cam().GetLimit().x - 1024 + size.x)
	{
		pos.x = Camera::Cam().GetLimit().x - 1024 + size.x;
	}
}

void Player::enterCollision(Collider * _other)
{
	
}

void Player::onCollision(Collider * _other)
{
}

void Player::exitCollision(Collider * _other)
{
}

void Player::ChangeLayer()
{
	float x = pos.x;
	float y = pos.y - size.y;

	if (GetPixel(Col_DC, (int)x, (int)y + 200) == ChangeColor)
	{
		if (m_ptOldPos.x > pos.x)
		{
			m_bTurn = true;
		}

		else if (m_ptOldPos.x < pos.x)
		{
			m_bTurn = false;
		}
	}
}

void Player::UpPixcel()
{
	if (pTex_Col == NULL)
	{
		return;
	}

	int x = (int)pos.x;
	int y = (int)pos.y + 1;

	if (m_bTurn == false)
	{
		while (GetGValue(GetPixel(Col_DC, (int)x, (int)y + 200)) == GetGValue(FloorColor) || (GetPixel(Col_DC, (int)x, (int)y + 200) == WallColor))
		{
			if (GetGValue(GetPixel(Col_DC, (int)x, (int)y - 1 + 200)) != GetGValue(FloorColor) && (GetPixel(Col_DC, (int)x, (int)y-1 + 200) != WallColor))
			{
				if ((m_ptOldPos.y - pos.y) > 0)
					break;

				pos.y = (float)y - 1;
				m_bOnGround = true;
				m_bCanJump = true;
				m_CheckType = CHECK_BOTTOM;
				m_ptGravity.y = 0.f;
				break;
			}

			else if (GetGValue(GetPixel(Col_DC, (int)x, (int)y - 1 + 200)) == GetGValue(FloorColor) || (GetPixel(Col_DC, (int)x, (int)y-1 + 200) == WallColor))
			{
				y -= 1;
			}
		}

		if (GetGValue(GetPixel(Col_DC, (int)x, (int)y + 2 + 200)) != GetGValue(FloorColor) && (GetPixel(Col_DC, (int)x, (int)y+ 2 + 200) != WallColor))
		{
			m_bOnGround = false;
			if (m_CheckType == CHECK_BOTTOM)
			{
				m_bCanJump = false;
			}
		}
	}

	else if (m_bTurn == true)
	{
		while (GetBValue(GetPixel(Col_DC, (int)x, (int)y + 200)) == GetBValue(FloorColor) || (GetPixel(Col_DC, (int)x, (int)y + 200) == WallColor))
		{
			if (GetBValue(GetPixel(Col_DC, (int)x, (int)y - 1 + 200)) != GetBValue(FloorColor) && (GetPixel(Col_DC, (int)x, (int)y - 1 + 200) != WallColor))
			{
				if ((m_ptOldPos.y - pos.y) > 0)
					break;

				pos.y = (float)y - 1;
				m_bOnGround = true;
				m_bCanJump = true;
				m_ptGravity.y = 0.f;
				m_CheckType = CHECK_BOTTOM;

				break;
			}

			else if (GetBValue(GetPixel(Col_DC, (int)x, (int)y - 1 + 200)) == GetBValue(FloorColor) || (GetPixel(Col_DC, (int)x, (int)y - 1 + 200) == WallColor))
			{
				y -= 1;
			}
		}

		if (GetBValue(GetPixel(Col_DC, (int)x, (int)y + 2 + 200)) != GetBValue(FloorColor) && (GetPixel(Col_DC, (int)x, (int)y + 2 + 200) != WallColor))
		{
			m_bOnGround = false;
			if (m_CheckType == CHECK_BOTTOM)
			{
				m_bCanJump = false;
			}
		}
	}

}

void Player::DownPixcel()
{

	if (pTex_Col == NULL)
	{
		return;
	}

	float y = pos.y - size.y -size.y - 1;
	float x = pos.x;

	if (m_bTurn == false)
	{
		while (GetGValue(GetPixel(Col_DC, (int)x, (int)y + 200)) == GetGValue(FloorColor))
		{
			if (GetGValue(GetPixel(Col_DC, (int)x, (int)y + 1 + 200)) != GetGValue(FloorColor))
			{
				pos.y = y + size.y + size.y + 1;
				m_bOnGround = true;
				m_bCanJump = true;
				m_ptGravity.y = 0.f;
				m_CheckType = CHECK_TOP;
				break;
			}

			else if (GetGValue(GetPixel(Col_DC, (int)x, (int)y + 1 + 200)) == GetGValue(FloorColor))
			{
				y += 1;
			}
		}

		if (m_CheckType == CHECK_TOP && GetGValue(GetPixel(Col_DC, (int)x, (int)y - 2 + 200)) != GetGValue(FloorColor) && (GetPixel(Col_DC, (int)x, (int)y - 2 + 200) != WallColor))
		{
			m_bCanJump = false;
		}
	}

	else if (m_bTurn == true)
	{
		COLORREF color = RGB(0, 192, 224);
		while (GetBValue(GetPixel(Col_DC, (int)x, (int)y + 200)) == GetBValue(FloorColor))
		{
			if (GetBValue(GetPixel(Col_DC, (int)x, (int)y + 1 + 200)) != GetBValue(FloorColor))
			{
				pos.y = y + size.y + size.y + 1;
				m_bOnGround = true;
				m_bCanJump = true;
				m_ptGravity.y = 0.f;
				m_CheckType = CHECK_TOP;
				break;
			}

			else if (GetBValue(GetPixel(Col_DC, (int)x, (int)y + 1 + 200)) == GetBValue(FloorColor))
			{
				y += 1;
			}
		}

		if (m_CheckType == CHECK_TOP && GetBValue(GetPixel(Col_DC, (int)x, (int)y - 2 + 200)) != GetBValue(FloorColor) && (GetPixel(Col_DC, (int)x, (int)y - 2 + 200) != WallColor))
		{
			m_bCanJump = false;
		}
	}
}

void Player::CheckWall()
{
	CheckRightWall();
	CheckLeftWall();
	CheckTopWall();
}

void Player::CheckRightWall()
{
	float x = pos.x + size.x;
	float y = pos.y - size.y;



	while (GetPixel(Col_DC, (int)x, (int)y + 200) == WallColor)
	{
		if (GetPixel(Col_DC, (int)x - 1, (int)y + 200) != WallColor)
		{
			pos.x = (float)((int)x - (int)size.x);
			m_bRightWallOn = true;
			return;
		}

		else if (GetPixel(Col_DC, (int)x - 1, (int)y + 200) == WallColor)
		{
			x -= 1;
		}
	}

	if (GetPixel(Col_DC, (int)x, (int)y + 200) != WallColor)
	{
		m_bRightWallOn = false;
	}
}

void Player::CheckLeftWall()
{
	float x = pos.x - size.x ;
	float y = pos.y - size.y;


	while (GetPixel(Col_DC, (int)x, (int)y + 200) == WallColor)
	{
		if (GetPixel(Col_DC, (int)x + 1, (int)y + 200) != WallColor)
		{
			pos.x = x + size.x;
			m_bLeftWallOn = true;
			return;
		}

		else if (GetPixel(Col_DC, (int)x + 1, (int)y + 200) == WallColor)
		{
			x += 1;
		}
	}

	if (GetPixel(Col_DC, (int)x, (int)y + 200) != WallColor)
	{
		m_bLeftWallOn = false;
	}
}

void Player::CheckTopWall()
{
	float x = pos.x;
	float y = pos.y - size.y*2;


	while (GetPixel(Col_DC, (int)x, (int)y + 200) == WallColor)
	{
		if (GetPixel(Col_DC, (int)x, (int)y + 1 + 200) != WallColor)
		{
			pos.y = y + size.y * 2;
			m_fJumpSpeed = 0;
			m_fSpringSpeed = 0;
			m_ptGradient = fPOINT{ 1.f, 0.f };
			if (m_bDir == DIR_RIGHT)
			{
				m_fSpeed = 150;
			}
			else if (m_bDir == DIR_LEFT)
			{
				m_fSpeed = -150;
			}

			m_ptGravity.y = 100;
			return;
		}

		else if (GetPixel(Col_DC, (int)x, (int)y + 1 + 200) == WallColor)
		{
			y += 1;
		}
	}
}

void Player::CheckDownGradient()
{
	if (m_CheckType != CHECK_BOTTOM)
	{
		return;
	}
	
	if (m_bOnGround == false)
		return;
	
	x1 = pos.x +5;
	y1 = pos.y;

	if (m_bTurn == false)
	{
		while (GetGValue(GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200)) != GetGValue(FloorColor) 
			&& GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200) != WallColor)
		{
			++y1;

			if (y1 >= pos.y + 10)
			{
				return;
			}

			if (GetGValue(GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200)) == GetGValue(FloorColor)
				|| GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200) == WallColor)
			{
				break;
			}
		}

		while (GetGValue(GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200)) == GetGValue(FloorColor)
			|| GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200) == WallColor)
		{
			if (GetGValue(GetPixel(Col_DC, (int)x1, (int)y1 + 200)) != GetGValue(FloorColor)
				&& GetPixel(Col_DC, (int)x1, (int)y1 + 200) != WallColor)
			{
				break;
			}

			else if (GetGValue(GetPixel(Col_DC, (int)x1, (int)y1 + 200)) == GetGValue(FloorColor)
				|| GetPixel(Col_DC, (int)x1, (int)y1 + 200) == WallColor)
			{
				y1 -= 1;
				if (y1 <= pos.y - 10)
				{
					break;
				}
			}
		}

		x2 = pos.x - 5;
		y2 = pos.y;

		while (GetGValue(GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200)) != GetGValue(FloorColor)
			&& GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200) != WallColor)
		{
			++y2;

			if (y2 >= pos.y + 10)
			{
				return;
			}
			if (GetGValue(GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200)) == GetGValue(FloorColor)
				|| GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200) == WallColor)
			{
				break;
			}
		}

		while (GetGValue(GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200)) == GetGValue(FloorColor)
			|| GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200) == WallColor)
		{
			if (GetGValue(GetPixel(Col_DC, (int)x2, (int)y2 + 200)) != GetGValue(FloorColor)
				&& GetPixel(Col_DC, (int)x2, (int)y2 + 200) != WallColor)
			{
				break;
			}
			else if (GetGValue(GetPixel(Col_DC, (int)x2, (int)y2 + 200)) == GetGValue(FloorColor)
				|| GetPixel(Col_DC, (int)x2, (int)y2 + 200) == WallColor)
			{
				y2 -= 1;
				if (y2 <= pos.y - 10)
				{
					break;
				}
			}
		}
	}

	else if (m_bTurn == true)
	{
		while (GetBValue(GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200)) != GetBValue(FloorColor)
			&& GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200) != WallColor)
		{
			++y1;
			if (y1 >= pos.y + 10)
			{
				return;
			}

			if (GetBValue(GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200)) == GetBValue(FloorColor)
				|| GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200) == WallColor)
			{
				break;
			}
		}

		while (GetBValue(GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200)) == GetBValue(FloorColor)
			|| GetPixel(Col_DC, (int)x1, (int)y1 + 1 + 200) == WallColor)
		{
			if (GetBValue(GetPixel(Col_DC, (int)x1, (int)y1 + 200)) != GetBValue(FloorColor)
				&& GetPixel(Col_DC, (int)x1, (int)y1 + 200) != WallColor)
			{
				break;
			}

			else if (GetBValue(GetPixel(Col_DC, (int)x1, (int)y1 + 200)) == GetBValue(FloorColor)
				|| GetPixel(Col_DC, (int)x1, (int)y1 + 200) == WallColor)
			{
				y1 -= 1;
				if (y1 <= pos.y - 10)
				{
					break;
				}
			}
		}

		x2 = pos.x - 5;
		y2 = pos.y;

		while (GetBValue(GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200)) != GetBValue(FloorColor)
			&& GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200) != WallColor)
		{
			++y2;
			if (y2 >= pos.y + 10)
			{
				return;
			}
			if (GetBValue(GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200)) == GetBValue(FloorColor)
				|| GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200) == WallColor)
			{
				break;
			}
		}

		while (GetBValue(GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200)) == GetBValue(FloorColor)
			|| GetPixel(Col_DC, (int)x2, (int)y2 + 1 + 200))
		{
			if (GetBValue(GetPixel(Col_DC, (int)x2, (int)y2 + 200)) != GetBValue(FloorColor)
				&& GetPixel(Col_DC, (int)x2, (int)y2 + 200) != WallColor)
			{
				break;
			}
			else if (GetBValue(GetPixel(Col_DC, (int)x2, (int)y2 + 200)) == GetBValue(FloorColor)
				|| GetPixel(Col_DC, (int)x2, (int)y2 + 200) == WallColor)
			{
				y2 -= 1;
				if (y2 <= pos.y - 10)
				{
					break;
				}
			}
		}
	}

	
	float v = sqrt((x1 - x2) * (x1 - x2) + (y2 - y1) * (y2 - y1));
	if (v == 0)
		assert(NULL);

	m_ptGradient.x = (x1 - x2) / v;
	m_ptGradient.y = (y2 - y1) / v;
}

void Player::CheckUpGradient()
{
	if (m_CheckType != CHECK_TOP)
		return;

	if (m_bOnGround == false)
		return;

	r1 = pos.x - 5;
	t1 = pos.y - size.y*2;

	if (m_bTurn == false)
	{
		while (GetGValue(GetPixel(Col_DC, (int)r1, (int)t1 - 1 + 200)) != GetGValue(FloorColor))
		{
			--t1;
			if (t1 <= pos.y - size.y*2 - 10)
			{
				return;
			}
			if (GetGValue(GetPixel(Col_DC, (int)r1, (int)t1 + 1 + 200)) == GetGValue(FloorColor))
			{
				break;
			}
		}

		while (GetGValue(GetPixel(Col_DC, (int)r1, (int)t1 - 1 + 200)) == GetGValue(FloorColor))
		{
			if (GetGValue(GetPixel(Col_DC, (int)r1, (int)t1 + 200)) != GetGValue(FloorColor))
			{
				break;
			}

			else
			{
				t1 += 1;
				if (t1 >= pos.y - size.y * 2 + 10)
				{
					break;
				}
			}
		}
		r2 = pos.x + 5;
		t2 = pos.y - size.y * 2;

		while (GetGValue(GetPixel(Col_DC, (int)r2, (int)t2 - 1 + 200)) != GetGValue(FloorColor))
		{
			--t2;
			if (t2 <= pos.y - size.y * 2 - 10)
			{
				return;
			}

			if (GetGValue(GetPixel(Col_DC, (int)r2, (int)t2 - 1 + 200)) == GetGValue(FloorColor))
			{
				break;
			}
		}

		while (GetGValue(GetPixel(Col_DC, (int)r2, (int)t2 - 1 + 200)) == GetGValue(FloorColor))
		{
			if (GetGValue(GetPixel(Col_DC, (int)r2, (int)t2 + 200)) != GetGValue(FloorColor))
			{
				break;
			}
			else
			{
				t2 += 1;

				if (t2 >= pos.y - size.y * 2 + 10)
				{
					break;
				}
			}
		}
	}

	else if (m_bTurn == true)
	{
		while (GetBValue(GetPixel(Col_DC, (int)r1, (int)t1 - 1 + 200)) != GetBValue(FloorColor))
		{
			--t1;
			if (t1 <= pos.y - size.y * 2 - 10)
			{
				return;
			}

			if (GetBValue(GetPixel(Col_DC, (int)r1, (int)t1 + 1 + 200)) == GetBValue(FloorColor))
			{
				break;
			}
		}

		while (GetBValue(GetPixel(Col_DC, (int)r1, (int)t1 - 1 + 200)) == GetBValue(FloorColor))
		{
			if (GetBValue(GetPixel(Col_DC, (int)r1, (int)t1 + 200)) != GetBValue(FloorColor))
			{
				break;
			}

			else
			{
				t1 += 1;
				if (t1 >= pos.y - size.y * 2 + 10)
				{
					break;
				}
			}
		}
		r2 = pos.x + 5;
		t2 = pos.y - size.y * 2;

		while (GetBValue(GetPixel(Col_DC, (int)r2, (int)t2 - 1 + 200)) != GetBValue(FloorColor))
		{
			--t2;
			if (t2 <= pos.y - size.y * 2 - 10)
			{
				return;
			}

			if (GetBValue(GetPixel(Col_DC, (int)r2, (int)t2 - 1 + 200)) == GetBValue(FloorColor))
			{
				break;
			}
		}

		while (GetBValue(GetPixel(Col_DC, (int)r2, (int)t2 - 1 + 200)) == GetBValue(FloorColor))
		{
			if (GetBValue(GetPixel(Col_DC, (int)r2, (int)t2 + 200)) != GetBValue(FloorColor))
			{
				break;
			}
			else
			{
				t2 += 1;

				if (t2 >= pos.y - size.y * 2 + 10)
				{
					break;
				}
			}
		}
	}

	float v = sqrt((r1 - r2) * (r1 - r2) + (t2 - t1) * (t2 - t1));
	if (v == 0)
		assert(NULL);

	m_ptGradient.x = (r1 - r2) / v;
	m_ptGradient.y = (t2 - t1) / v;
}

void Player::CheckRightGradient()
{
	if (m_CheckType != CHECK_RIGHT)
		return;

	if (m_bOnGround == false)
		return;

	i1 = pos.x + size.x;
	j1 = pos.y - size.y -5;

	if (m_bTurn == false)
	{
		while (GetGValue(GetPixel(Col_DC, (int)i1 + 1, (int)j1 + 200)) != GetGValue(FloorColor))
		{
			++i1;

			if (i1 >= pos.x + size.x + 10)
			{
				return;
			}

			if (GetGValue(GetPixel(Col_DC, (int)i1, (int)j1 + 200)) == GetGValue(FloorColor))
			{
				break;
			}
		}

		while (GetGValue(GetPixel(Col_DC, (int)i1 + 1, (int)j1 + 200)) == GetGValue(FloorColor))
		{
			if (GetGValue(GetPixel(Col_DC, (int)i1, (int)j1 + 200)) != GetGValue(FloorColor))
			{
				break;
			}

			else
			{
				i1 -= 1;
				if (i1 <= pos.x + size.x - 10)
				{
					break;
				}
			}
		}
		i2 = pos.x + size.x;
		j2 = pos.y - size.y + 5;

		while (GetGValue(GetPixel(Col_DC, (int)i2 + 1, (int)j2 + 200)) != GetGValue(FloorColor))
		{
			++i2;
			if (i2 > pos.x + size.x + 10)
			{
				return;
			}

			if (GetGValue(GetPixel(Col_DC, (int)i2, (int)j2 + 200)) == GetGValue(FloorColor))
			{
				break;
			}
		}

		while (GetGValue(GetPixel(Col_DC, (int)i2 + 1, (int)j2 + 200)) == GetGValue(FloorColor))
		{
			if (GetGValue(GetPixel(Col_DC, (int)i2, (int)j2 + 200)) != GetGValue(FloorColor))
			{
				break;
			}
			else
			{
				i2 -= 1;
				if (i2 <= pos.x + size.x - 10)
				{
					break;
				}
			}
		}
	}

	else if (m_bTurn == true)
	{
		while (GetBValue(GetPixel(Col_DC, (int)i1 + 1, (int)j1 + 200)) != GetBValue(FloorColor))
		{
			++i1;

			if (i1 > pos.x + size.x + 10)
				return;

			if (GetBValue(GetPixel(Col_DC, (int)i1, (int)j1 + 200)) == GetBValue(FloorColor))
			{
				break;
			}
		}

		while (GetBValue(GetPixel(Col_DC, (int)i1 + 1, (int)j1 + 200)) == GetBValue(FloorColor))
		{
			if (GetBValue(GetPixel(Col_DC, (int)i1, (int)j1 + 200)) != GetBValue(FloorColor))
			{
				break;
			}

			else
			{
				i1 -= 1;
				if (i1 <= pos.x + size.x - 10)
				{
					break;
				}
			}
		}
		i2 = pos.x + size.x;
		j2 = pos.y - size.y + 5;

		while (GetBValue(GetPixel(Col_DC, (int)i2 + 1, (int)j2 + 200)) != GetBValue(FloorColor))
		{
			++i2;
			if (i2 > pos.x + size.x + 15)
				return;

			if (GetBValue(GetPixel(Col_DC, (int)i2, (int)j2 + 200)) == GetBValue(FloorColor))
			{
				break;
			}
		}

		while (GetBValue(GetPixel(Col_DC, (int)i2 + 1, (int)j2 + 200)) == GetBValue(FloorColor))
		{
			if (GetBValue(GetPixel(Col_DC, (int)i2, (int)j2 + 200)) != GetBValue(FloorColor))
			{
				break;
			}
			else
			{
				i2 -= 1;
				if (i2 <= pos.x + size.x - 10)
				{
					break;
				}
			}
		}
	}
	

	float v = sqrt((i1 - i2) * (i1 - i2) + (j2 - j1) * (j2 - j1));
	if (v == 0)
		assert(NULL);

	m_ptGradient.x = (i1 - i2) / v;
	m_ptGradient.y = (j2 - j1) / v;
}

void Player::CheckLeftGradient()
{
	if (m_CheckType != CHECK_LEFT)
		return;

	if (m_bOnGround == false)
		return;

	p1 = pos.x - size.x;
	q1 = pos.y - size.y + 5;

	if (m_bTurn == false)
	{
		while (GetGValue(GetPixel(Col_DC, (int)p1 - 1, (int)q1 + 200)) != GetGValue(FloorColor))
		{
			--p1;
			if (p1 <= pos.x - size.x - 10)
			{
				return;
			}
			if (GetGValue(GetPixel(Col_DC, (int)p1, (int)q1 + 200)) == GetGValue(FloorColor))
			{
				break;
			}
		}

		while (GetGValue(GetPixel(Col_DC, (int)p1 - 1, (int)q1 + 200)) == GetGValue(FloorColor))
		{
			if (GetGValue(GetPixel(Col_DC, (int)p1, (int)q1 + 200)) != GetGValue(FloorColor))
			{
				break;
			}

			else
			{
				p1 += 1;
				if (p1 >= pos.x - size.x + 10)
				{
					break;
				}
			}
		}
		p2 = pos.x - size.x;
		q2 = pos.y - size.y - 5;

		while (GetGValue(GetPixel(Col_DC, (int)p2 - 1, (int)q2 + 200)) != GetGValue(FloorColor))
		{
			--p2;
			if (p2 <= pos.x - size.x - 10)
			{
				return;
			}
			if (GetGValue(GetPixel(Col_DC, (int)p2, (int)q2 + 200)) == GetGValue(FloorColor))
			{
				break;
			}
		}

		while (GetGValue(GetPixel(Col_DC, (int)p2 - 1, (int)q2 + 200)) == GetGValue(FloorColor))
		{
			if (GetGValue(GetPixel(Col_DC, (int)p2, (int)q2 + 200)) != GetGValue(FloorColor))
			{
				break;
			}
			else
			{
				p2 += 1;

				if (p2 >= pos.x - size.x + 10)
				{
					break;
				}
			}
		}
	}

	else if (m_bTurn == true)
	{
		while (GetBValue(GetPixel(Col_DC, (int)p1 - 1, (int)q1 + 200)) != GetBValue(FloorColor))
		{
			--p1;
			if (p1 <= pos.x - size.x - 10)
			{
				return;
			}

			if (GetBValue(GetPixel(Col_DC, (int)p1, (int)q1 + 200)) == GetBValue(FloorColor))
			{
				break;
			}
		}

		while (GetBValue(GetPixel(Col_DC, (int)p1 - 1, (int)q1 + 200)) == GetBValue(FloorColor))
		{
			if (GetBValue(GetPixel(Col_DC, (int)p1, (int)q1 + 200)) != GetBValue(FloorColor))
			{
				break;
			}

			else
			{
				p1 += 1;

				if (p1 >= pos.x - size.x + 10)
				{
					break;
				}
			}
		}
		p2 = pos.x - size.x;
		q2 = pos.y - size.y - 5;

		while (GetBValue(GetPixel(Col_DC, (int)p2 - 1, (int)q2 + 200)) != GetBValue(FloorColor))
		{
			--p2;
			if (p2 <= pos.x - size.x - 10)
			{
				return;
			}

			if (GetBValue(GetPixel(Col_DC, (int)p2, (int)q2 + 200)) == GetBValue(FloorColor))
			{
				break;
			}
		}

		while (GetBValue(GetPixel(Col_DC, (int)p2 - 1, (int)q2 + 200)) == GetBValue(FloorColor))
		{
			if (GetBValue(GetPixel(Col_DC, (int)p2, (int)q2 + 200)) != GetBValue(FloorColor))
			{
				break;
			}
			else
			{
				p2 += 1;

				if (p2 >= pos.x - size.x + 10)
				{
					break;
				}
			}
		}
	}
	

	float v = sqrt((p1 - p2) * (p1 - p2) + (q2 - q1) * (q2 - q1));
	if (v == 0)
		assert(NULL);

	m_ptGradient.x = (p1 - p2) / v;
	m_ptGradient.y = (q2 - q1) / v;
}

void Player::LeftPixcel()
{
	if (pTex_Col == NULL)
	{
		return;
	}

	float y = pos.y - size.y;
	float x = pos.x + size.x + 1;

	COLORREF color = RGB(255, 0, 0);

	if (m_bTurn == false)
	{
		while (GetGValue(GetPixel(Col_DC, (int)x, (int)y + 200)) == GetGValue(FloorColor))
		{
			if (GetGValue(GetPixel(Col_DC, (int)x - 1, (int)y + 200)) != GetGValue(FloorColor))
			{
				pos.x = x - size.x - 1;
				m_ptGravity.y = 0.f;
				m_CheckType = CHECK_RIGHT;
				m_bOnGround = true;
				m_bCanJump = true;
				break;
			}

			else if (GetGValue(GetPixel(Col_DC, (int)x - 1, (int)y + 200)) == GetGValue(FloorColor))
			{
				x -= 1;
			}
		}

		if (m_CheckType == CHECK_RIGHT && GetGValue(GetPixel(Col_DC, (int)x + 2, (int)y + 200)) != GetGValue(FloorColor))
		{
			m_bCanJump = false;
		}
	}

	else if (m_bTurn == true)
	{
		while (GetBValue(GetPixel(Col_DC, (int)x, (int)y + 200)) == GetBValue(FloorColor))
		{
			if (GetBValue(GetPixel(Col_DC, (int)x - 1, (int)y + 200)) != GetBValue(FloorColor))
			{
				pos.x = x - size.x - 1;
				m_bOnGround = true;
				m_bCanJump = true;
				m_ptGravity.y = 0.f;
				m_CheckType = CHECK_RIGHT;
				break;
			}

			else if (GetBValue(GetPixel(Col_DC, (int)x - 1, (int)y + 200)) == GetBValue(FloorColor))
			{
				x -= 1;
			}
		}

		if (m_CheckType == CHECK_RIGHT && GetBValue(GetPixel(Col_DC, (int)x + 2, (int)y + 200)) != GetBValue(FloorColor))
		{
			m_bCanJump = false;
		}
	}

	
}

void Player::RightPixcel()
{
	if (pTex_Col == NULL)
	{
		return;
	}

	float x = pos.x - size.x - 1;
	float y = pos.y - size.y;
	
	if (m_bTurn == false)
	{
		while (GetGValue(GetPixel(Col_DC, (int)x, (int)y + 200)) == GetGValue(FloorColor))
		{
			if (GetGValue(GetPixel(Col_DC, (int)x + 1, (int)y + 200)) != GetGValue(FloorColor))
			{
				pos.x = x + size.x + 1;
				m_bOnGround = true;
				m_bCanJump = true;
				m_ptGravity.y = 0.f;
				m_CheckType = CHECK_LEFT;
				break;
			}

			else if (GetGValue(GetPixel(Col_DC, (int)x + 1, (int)y + 200)) == GetGValue(FloorColor))
			{
				x += 1;
			}
		}
		if (m_CheckType == CHECK_LEFT && GetBValue(GetPixel(Col_DC, (int)x - 2, (int)y + 200)) != GetBValue(FloorColor))
		{
			m_bCanJump = false;
		}
	}

	else if (m_bTurn == true)
	{
		while (GetBValue(GetPixel(Col_DC, (int)x, (int)y + 200)) == GetBValue(FloorColor))
		{
			if (GetBValue(GetPixel(Col_DC, (int)x + 1, (int)y + 200)) != GetBValue(FloorColor))
			{
				pos.x = x + size.x + 1;
				m_bOnGround = true;
				m_bCanJump = true;
				m_ptGravity.y = 0.f;
				m_CheckType = CHECK_LEFT;
				break;
			}

			else if (GetBValue(GetPixel(Col_DC, (int)x + 1, (int)y + 200)) == GetBValue(FloorColor))
			{
				x += 1;
			}
		}

		if (m_CheckType == CHECK_LEFT && GetBValue(GetPixel(Col_DC, (int)x - 2, (int)y + 200)) != GetBValue(FloorColor))
		{
			m_bCanJump = false;
		}
	}
	
}

void Player::Player_Stop()
{
	
	if (true == KeyManager::Manager().GetKeyState(KEY_DOWN, STATE_HOLD))
	{
		state = PLAYER_SIT;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
	{
		if (m_fSpeed > 0 && m_ptGradient.x >= 0.8f)
		{
			m_fBreakSpeed = m_fSpeed;
			m_bDir = DIR_RIGHT;
			state = PLAYER_RIGHTBREAK;
			return;
		}
		m_bDir = DIR_LEFT;
		state = PLAYER_LEFTWalK;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
	{
		if (m_fSpeed < 0 && m_ptGradient.x >= 0.8f)
		{
			m_fBreakSpeed = m_fSpeed;
			m_bDir = DIR_LEFT;
			state = PLAYER_LEFTBREAK;
			return;
		}
		m_bDir = DIR_RIGHT;
		state = PLAYER_RIGHTWalK;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_UP, STATE_HOLD))
	{
		state = PLAYER_LOOKUP;
	}
	
	else if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB))
	{
		if (m_bOnGround == true)
		{
			m_Animation = ANI_JUMP;
			state = PLAYER_JUMP;
			m_bOnGround = false;

			float a = m_ptGradient.x;
			float b = m_ptGradient.y;

			float x = sqrt((b*b) / (a*a + b*b));
			float y = sqrt((a*a) / (a*a + b*b));

			if (a > 0 && b > 0)
			{
				m_ptJumpGradient.x = -x;
				m_ptJumpGradient.y = y;
			}

			else if (a < 0 && b > 0)
			{
				m_ptJumpGradient.x = -x;
				m_ptJumpGradient.y = -y;
			}

			else if (a < 0 && b < 0)
			{
				m_ptJumpGradient.x = x;
				m_ptJumpGradient.y = -y;
			}

			else if (a > 0 && b < 0)
			{
				m_ptJumpGradient.x = x;
				m_ptJumpGradient.y = y;
			}

			else
			{
				m_ptJumpGradient.x = x;
				m_ptJumpGradient.y = y;
			}
			m_fJumpSpeed = JUMP_SPEED;

			SoundManager::Manager()->PlaySoundW(L"Sound_Jump",false);
		}
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_UP, STATE_HOLD))
	{
		state = PLAYER_LOOKUP;
	}


	if ((int)m_fSpeed == 0 && state != PLAYER_JUMP)
	{
		m_fSpeed = 0;
		m_Animation = ANI_STOP;
	}

	else if (m_fSpeed != 0 && state != PLAYER_JUMP)
	{
		m_Animation = ANI_WALK;
	}
	
	////Idle 애니메이션
	//if (m_Animation == ANI_STOP)
	//{

	//}

}

void Player::Player_Idle()
{
}

void Player::Player_Jump()
{
	m_Animation = ANI_JUMP;

	if (true == m_bRightWallOn || true == m_bLeftWallOn)
	{
		m_fSpeed = 0.f;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
	{
		m_bDir = DIR_RIGHT;
		if (m_fSpeed <= 400)
		{
			m_fSpeed += 600 * DT;
		}

		else
		{
			m_fSpeed += 200 * DT;
		}

		if (m_bSuperSonic == true)
		{
			m_fSpeed += 400 * DT;
		}
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
	{
		m_bDir = DIR_LEFT;
		if (m_fSpeed >= -400)
		{
			m_fSpeed -= 600 * DT;
		}

		else
		{
			m_fSpeed -= 200 * DT;
		}

		if (m_bSuperSonic == true)
		{
			m_fSpeed -= 400 * DT;
		}
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB))
	{
		m_ptGravity.y = 0; 
		state = PLAYER_SPINNING;
	}


	if (m_bOnGround == true)
	{
		m_fSpeed = m_ptJumpGradient.x * m_fJumpSpeed + m_ptGradient.x * m_fSpeed;
		m_fJumpSpeed = 0;
		
		state = PLAYER_STOP;
		
		return;
	}
}

void Player::Player_Sit()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_DOWN, STATE_HOLD))
	{
		m_Animation = ANI_SIT;
		if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB))
		{
			if (m_bDir == DIR_RIGHT)
			{
				Effect_Spin* pEffect = new Effect_Spin;
				pEffect->init(pos, DIR_RIGHT);
				StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pEffect);
				SoundManager::Manager()->PlaySoundW(L"Sound_Spin", false);
			}

			else if (m_bDir == DIR_LEFT)
			{
				Effect_Spin* pEffect = new Effect_Spin;
				pEffect->init(pos, DIR_LEFT);
				StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pEffect);
				SoundManager::Manager()->PlaySoundW(L"Sound_Spin", false);
			}
			

			state = PLAYER_SPIN;
		}
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_DOWN, STATE_AWAY))
	{
		state = PLAYER_STOP;
	}
}

void Player::Player_Lookup()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_UP, STATE_HOLD))
	{
		m_Animation = ANI_LOOKUP;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_UP, STATE_AWAY))
	{
		state = PLAYER_STOP;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_DOWN, STATE_HOLD))
	{
		state = PLAYER_SIT;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
	{
		m_bDir = DIR_LEFT;
		state = PLAYER_LEFTWalK;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
	{
		m_bDir = DIR_RIGHT;
		state = PLAYER_RIGHTWalK;
	}
	else if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB))
	{
		if (m_bOnGround == true)
		{
			m_Animation = ANI_JUMP;
			state = PLAYER_JUMP;
			m_bOnGround = false;

			float a = m_ptGradient.x;
			float b = m_ptGradient.y;

			float x = sqrt((b*b) / (a*a + b*b));
			float y = sqrt((a*a) / (a*a + b*b));

			if (a > 0 && b > 0)
			{
				m_ptJumpGradient.x = -x;
				m_ptJumpGradient.y = y;
			}

			else if (a < 0 && b > 0)
			{
				m_ptJumpGradient.x = -x;
				m_ptJumpGradient.y = -y;
			}

			else if (a < 0 && b < 0)
			{
				m_ptJumpGradient.x = x;
				m_ptJumpGradient.y = -y;
			}

			else if (a > 0 && b < 0)
			{
				m_ptJumpGradient.x = x;
				m_ptJumpGradient.y = y;
			}

			else
			{
				m_ptJumpGradient.x = x;
				m_ptJumpGradient.y = y;
			}
			m_fJumpSpeed = JUMP_SPEED;
		}
	}
}

void Player::Player_RightWalk()
{
	m_bDir = DIR_RIGHT;

	if (m_bRightWallOn == true)
	{
		m_fSpeed = 0;
		if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
		{
			state = PLAYER_RIGHTPUSH;
			return;
		}
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD) )
	{
		if (m_bOnGround == true)
		{
			
			m_fSpeed += 600 * DT;
			m_Animation = ANI_WALK;
			

			if (m_bSuperSonic == true)
			{
				m_fSpeed += 400 * DT;
			}
		}
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
	{
		if (m_bOnGround == true)
		{
			if (m_ptGradient.x >= 0.8f && m_fSpeed >= 200)
			{
				m_fBreakSpeed = m_fSpeed;
				state = PLAYER_RIGHTBREAK;

				Effect_Break* pEffect = new Effect_Break;
				pEffect->init(this);
				StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pEffect);
			}

			else if (m_fSpeed < 200)
			{
				state = PLAYER_LEFTWalK;
			}
		}
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_DOWN, STATE_TAB) && m_fSpeed >= 200)
	{
		SoundManager::Manager()->StopSound(L"Sound_Spin");
		SoundManager::Manager()->PlaySoundW(L"Sound_Spin", false);
		state = PLAYER_SPINMOVE;
	}

	if (m_fSpeed == 0)
	{
		state = PLAYER_STOP;
	}

	if (m_bCanJump == false)
	{
		m_ptGradient.x += DT;
		
		if (m_ptGradient.x >= 1.f)
		{
			m_ptGradient.x = 1.f;
		}
		
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB) && m_bCanJump == true)
	{
		SoundManager::Manager()->PlaySoundW(L"Sound_Jump", false);

		state = PLAYER_JUMP;
		m_bOnGround = false;

		float a = m_ptGradient.x;
		float b = m_ptGradient.y;

		float x = sqrt((b*b) / (a*a + b*b));
		float y = sqrt((a*a) / (a*a + b*b));

		if (a > 0 && b > 0)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = y;
		}

		else if (a < 0 && b > 0)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = -y;
		}

		else if (a < 0 && b < 0)
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = -y;
		}

		else if (a == 0 && b == 1)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = y;
		}

		else if (a > 0 && b < 0)
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = y;
		}

		else
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = y;
		}
		m_fJumpSpeed = JUMP_SPEED;
	}
}

void Player::Player_LeftWalk()
{
	m_bDir = DIR_LEFT;

	if (m_bLeftWallOn == true)
	{
		m_fSpeed = 0;
		if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
		{
			m_fSpeed = 0;
			state = PLAYER_LEFTPUSH;
			return;
		}
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
	{
		
		m_fSpeed -= 600 * DT;
		m_Animation = ANI_WALK;
		

		if (m_bSuperSonic == true)
		{
			m_fSpeed -= 400 * DT;
			m_Animation = ANI_WALK;
		}
		
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
	{
		if (m_bOnGround == true)
		{
			if (m_ptGradient.x >= 0.8f && m_fSpeed <= -200)
			{
				m_fBreakSpeed = m_fSpeed;
				state = PLAYER_LEFTBREAK;

				Effect_Break* pEffect = new Effect_Break;
				pEffect->init(this);
				StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pEffect);
			}

			else if (m_fSpeed > -200)
			{
				state = PLAYER_RIGHTWalK;
			}
		}
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_DOWN, STATE_TAB) && m_fSpeed <= -200)
	{
		SoundManager::Manager()->StopSound(L"Sound_Spin");
		SoundManager::Manager()->PlaySoundW(L"Sound_Spin", false);
		state = PLAYER_SPINMOVE;
	}
	
	if (m_bCanJump == false)
	{
		m_ptGradient.x += DT;
		if (m_ptGradient.x >= 1.f)
		{
			m_ptGradient.x = 1.f;
		}
	}

	if (m_fSpeed == 0)
	{
		state = PLAYER_STOP;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB) && m_bCanJump == true)
	{
		SoundManager::Manager()->PlaySoundW(L"Sound_Jump", false);

		state = PLAYER_JUMP;
		m_bOnGround = false;

		float a = m_ptGradient.x;
		float b = m_ptGradient.y;

		float x = sqrt((b*b) / (a*a + b*b));
		float y = sqrt((a*a) / (a*a + b*b));

		if (a > 0 && b > 0)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = y;
		}

		else if (a < 0 && b > 0)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = -y;
		}

		else if (a < 0 && b < 0)
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = -y;
		}

		else if (a == 0 && b == 1)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = y;
		}

		else if (a > 0 && b < 0)
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = y;
		}

		else
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = y;
		}
		m_fJumpSpeed = JUMP_SPEED;
	}
}

void Player::Player_Spin()
{
	
	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_HOLD))
	{
		
		m_Animation = ANI_SPIN;
		m_fAccSpeed += 2000 * DT;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB))
	{
		m_fAccSpeed += 600;

		SoundManager::Manager()->StopSound(L"Sound_Spin");
		SoundManager::Manager()->PlaySoundW(L"Sound_Spin", false);
		if (m_bDir == DIR_RIGHT)
		{
			Effect_Spin* pEffect = new Effect_Spin;
			pEffect->init(pos, DIR_RIGHT);
			StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pEffect);
		}

		else if (m_bDir == DIR_LEFT)
		{
			Effect_Spin* pEffect = new Effect_Spin;
			pEffect->init(pos, DIR_LEFT);
			StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pEffect);
		}
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_DOWN, STATE_AWAY))
	{
		if (m_bDir == DIR_RIGHT)
		{
			m_fSpeed = m_fAccSpeed;
			m_fAccSpeed = 0;
		}
		else if (m_bDir == DIR_LEFT)
		{
			m_fSpeed = -m_fAccSpeed;
			m_fAccSpeed = 0;
		}
		state = PLAYER_SPINMOVE;
	}


}

void Player::Player_SpinMove()
{
	m_Animation = ANI_ROLL;

	if (m_bDir == DIR_RIGHT )
	{
		if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD) && m_bOnGround == true && m_ptGradient.x >= 0.8)
		{
			m_fBreakSpeed = m_fSpeed;
			state = PLAYER_RIGHTBREAK;
		}

		else if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
		{
			m_fSpeed += 100 * DT;

			if (m_bCanJump == false)
			{
				if (m_ptGradient.x <= 0.1)
				{
					pos.x += 200 * DT;
				}
			}
		}
	}

	else if (m_bDir == DIR_LEFT)
	{
		if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD) && m_bOnGround == true && m_ptGradient.x >= 0.8)
		{
			m_fBreakSpeed = m_fSpeed;
			state = PLAYER_LEFTBREAK;
		}

		else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
		{
			m_fSpeed -= 100 * DT;

			if (m_bCanJump == false)
			{
				if (m_ptGradient.x <= 0.1)
				{
					pos.x -= 200 * DT;
				}
			}
		}
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB) && m_bOnGround == true)
	{
		SoundManager::Manager()->PlaySoundW(L"Sound_Jump", false);
		state = PLAYER_JUMP;
		m_bOnGround = false;

		float a = m_ptGradient.x;
		float b = m_ptGradient.y;

		float x = sqrt((b*b) / (a*a + b*b));
		float y = sqrt((a*a) / (a*a + b*b));

		if (a > 0 && b > 0)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = y;
		}

		else if (a < 0 && b > 0)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = -y;
		}

		else if (a < 0 && b < 0)
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = -y;
		}

		else
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = y;
		}
		m_fJumpSpeed = JUMP_SPEED;
	}

	if ((int)m_fSpeed == 0)
	{
		state = PLAYER_STOP;
	}
}

void Player::Player_RightBreak()
{
	if(m_fSpeed >= 50)
		SoundManager::Manager()->PlaySoundW(L"Sound_Break", false);

	m_Animation = ANI_BREAK;

	m_fSpeed -= m_fBreakSpeed * 2 * DT;
	if (m_fSpeed <= 0)
	{
		m_fSpeed = 0;
	}

	if (m_bRightWallOn == true)
	{
		m_fSpeed = 0;
	}

	if ((int)m_fSpeed == 0)
	{
		state = PLAYER_STOP;
	}
}

void Player::Player_LeftBreak()
{
	if(m_fSpeed <= -50)
		SoundManager::Manager()->PlaySoundW(L"Sound_Break", false);

	m_Animation = ANI_BREAK;

	m_fSpeed -= m_fBreakSpeed * 2 * DT;
	if (m_fSpeed >= 0)
	{
		m_fSpeed = 0;
	}

	if (m_bLeftWallOn == true)
	{
		m_fSpeed = 0;
	}


	if ((int)m_fSpeed == 0)
	{
		state = PLAYER_STOP;
	}
}

void Player::Player_Spining()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_HOLD))
	{
		m_Animation = ANI_SPINING;
		if (m_bDir == DIR_RIGHT)
		{
			m_fSpeed = 400;
			pos.x += m_fSpeed * DT;

			if (m_bRightWallOn == true)
			{
				m_fSpeed = 0;
				m_bClimbOn = true;
				m_ptGradient.x = 1;
				m_ptGradient.y = 0;
				state = PLAYER_RIGHTCLIMB;
			}

		}

		else if (m_bDir == DIR_LEFT)
		{
			m_fSpeed = -400;
			pos.x += m_fSpeed * DT;

			if (m_bLeftWallOn == true && m_bDir == DIR_LEFT)
			{
				m_fSpeed = 0;
				m_bClimbOn = true;
				m_ptGradient.x = 1;
				m_ptGradient.y = 0;
				state = PLAYER_LEFTCLIMB;
			}
		}

		pos.y += 50 * DT;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_AWAY))
	{
		state = PLAYER_DROP;
	}

	if (true == m_bOnGround)
	{
		if (m_bDir == DIR_RIGHT)
			state = PLAYER_RIGHTWalK;
		else
			state = PLAYER_LEFTWalK;
	}
}

void Player::Player_Drop()
{
	m_Animation = ANI_DROP;

	if (m_bOnGround == true)
		state = PLAYER_STOP;
}

void Player::Player_RightPush()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
	{
		m_Animation = ANI_PUSH;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_AWAY))
	{
		state = PLAYER_STOP;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
	{
		state = PLAYER_LEFTWalK;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB) && m_bOnGround == true)
	{
		state = PLAYER_JUMP;
		m_bOnGround = false;

		float a = m_ptGradient.x;
		float b = m_ptGradient.y;

		float x = sqrt((b*b) / (a*a + b*b));
		float y = sqrt((a*a) / (a*a + b*b));

		if (a > 0 && b > 0)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = y;
		}

		else if (a < 0 && b > 0)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = -y;
		}

		else if (a < 0 && b < 0)
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = -y;
		}

		else
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = y;
		}
		m_fJumpSpeed = JUMP_SPEED;
	}

	if (m_bRightWallOn == false)
	{
		state = PLAYER_STOP;
	}
}

void Player::Player_LeftPush()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
	{
		m_Animation = ANI_PUSH;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_AWAY))
	{
		state = PLAYER_STOP;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
	{
		state = PLAYER_RIGHTWalK;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB) && m_bOnGround == true)
	{
		state = PLAYER_JUMP;
		m_bOnGround = false;

		float a = m_ptGradient.x;
		float b = m_ptGradient.y;

		float x = sqrt((b*b) / (a*a + b*b));
		float y = sqrt((a*a) / (a*a + b*b));

		if (a > 0 && b > 0)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = y;
		}

		else if (a < 0 && b > 0)
		{
			m_ptJumpGradient.x = -x;
			m_ptJumpGradient.y = -y;
		}

		else if (a < 0 && b < 0)
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = -y;
		}

		else
		{
			m_ptJumpGradient.x = x;
			m_ptJumpGradient.y = y;
		}
		m_fJumpSpeed = JUMP_SPEED;
	}

	if (m_bLeftWallOn == false)
	{
		state = PLAYER_STOP;
	}
}

void Player::Player_RightClimb()
{
	if (m_eOldAnimation != ANI_CLIMB)
	{
		m_AccTime = 0;
		m_Animation = ANI_CLIMB;
	}
	

	if (true == KeyManager::Manager().GetKeyState(KEY_UP, STATE_HOLD))
	{
		pos.y -= 130 * DT;

		m_AccTime += DT*7;

		if (m_AccTime > 6)
			m_AccTime = 0;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_DOWN, STATE_HOLD))
	{
		pos.y += 130 * DT;
		m_AccTime -= DT*7;

		if (m_AccTime <= 0)
			m_AccTime = 6;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB))
	{
		m_bClimbOn = false;
		m_ptJumpGradient.x = -0.196116f;
		m_ptJumpGradient.y = 0.980581f;

		state = PLAYER_JUMP;
	}

	if (false == m_bRightWallOn && m_ptOldPos.y > pos.y)
	{
		pos.x = pos.x + 17;
		state = PLAYER_ENDCLIMB_00;
	}

	else if (false == m_bRightWallOn && m_ptOldPos.y < pos.y)
	{
		state = PLAYER_JUMP;
		m_fJumpSpeed = 0;
		m_bClimbOn = false;
	}
}

void Player::Player_LeftClimb()
{
	m_Animation = ANI_CLIMB;

	if (true == KeyManager::Manager().GetKeyState(KEY_UP, STATE_HOLD))
	{
		pos.y -= 130 * DT;

		m_AccTime += DT * 7;

		if (m_AccTime > 6)
			m_AccTime = 0;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_DOWN, STATE_HOLD))
	{
		pos.y += 130 * DT;
		m_AccTime -= DT * 7;

		if (m_AccTime <= 0)
			m_AccTime = 6;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB))
	{
		m_bClimbOn = false;
		m_ptJumpGradient.x = 0.196116f;
		m_ptJumpGradient.y = 0.980581f;

		state = PLAYER_JUMP;
	}

	if (false == m_bLeftWallOn && m_ptOldPos.y > pos.y)
	{
		pos.x = pos.x -16;
		state = PLAYER_ENDCLIMB_00;
	}

	else if (false == m_bLeftWallOn && m_ptOldPos.y < pos.y)
	{
		state = PLAYER_JUMP;
		m_fJumpSpeed = 0;
		m_bClimbOn = false;
	}
}

void Player::Player_EndClimb_00()
{
	
	if (m_eOldAnimation != ANI_ENDCLIMB)
	{
		m_fEndClimbTime = 0.f;
	}
	m_Animation = ANI_ENDCLIMB;

	m_fEndClimbTime += 8* DT;

	if (m_fEndClimbTime >= 1)
	{
		if (m_bDir == DIR_RIGHT)
		{
			pos.x = pos.x + 5;
			pos.y = pos.y - 5;
		}
		
		else if (m_bDir == DIR_LEFT)
		{
			pos.x = pos.x - 5;
			pos.y = pos.y - 5;
		}
		state = PLAYER_ENDCLIMB_01;
	}
		

}

void Player::Player_EndClimb_01()
{

	m_fEndClimbTime += 8* DT;

	if (m_fEndClimbTime >= 2)
	{
		if (m_bDir == DIR_RIGHT)
		{
			pos.x = pos.x + 15;
			pos.y = pos.y - 25;
		}
		else if (m_bDir == DIR_LEFT)
		{
			pos.x = pos.x - 15;
			pos.y = pos.y - 25;
		}

		state = PLAYER_ENDCLIMB_02;
	}
}

void Player::Player_EndClimb_02()
{
	m_fEndClimbTime += 8* DT;

	if (m_fEndClimbTime >= 3)
	{
		if (m_bDir == DIR_RIGHT)
		{
			pos.x = pos.x + 15;
			pos.y = pos.y - 12;
		}
		else if (m_bDir == DIR_LEFT)
		{
			pos.x = pos.x - 15;
			pos.y = pos.y - 12;
		}
		state = PLAYER_STOP;
		m_bClimbOn = false;
	}
}

void Player::Player_SpringJump()
{
	m_Animation = ANI_SPRINGJUMP;
	m_ptGradient.x = 1.f;
	m_ptGradient.y = 0.f;

	if (true == m_bRightWallOn || true == m_bLeftWallOn)
	{
		m_fSpeed = 0;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
	{
		m_bDir = DIR_RIGHT;
		if (m_fSpeed <= 400)
		{
			m_fSpeed += 600 * DT;
		}

		else
		{
			m_fSpeed += 200 * DT;
		}
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
	{
		m_bDir = DIR_LEFT;
		if (m_fSpeed >= -400)
		{
			m_fSpeed -= 600 * DT;
		}

		else
		{
			m_fSpeed -= 200 * DT;
		}
	}
}

void Player::Player_Hitted()
{
	m_Animation = ANI_HITTED;
	m_AccTime += DT;
	m_fJumpSpeed -= 500 * DT;
	if (m_fJumpSpeed <= 0)
		m_fJumpSpeed = 0;


	if (m_bOnGround == true && m_AccTime >= 1.5)
	{
		m_fSpeed = m_ptJumpGradient.x * m_fJumpSpeed + m_ptGradient.x * m_fSpeed;
		m_fJumpSpeed = 0;
		m_fSpeed = 0;
		state = PLAYER_STOP;
		m_AccTime = 0;
		m_bCanJump = true;
		return;
	}

	if (m_eShield != SHIELD_END)
	{
		m_eShield = SHIELD_END;
	}
}

void Player::Player_Finish()
{
	m_Animation = ANI_VICTORY;

}

void Player::Jump_Move()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_U, STATE_HOLD))
	{
		m_iRingCnt += 1;
	}

	if (state != PLAYER_JUMP && state != PLAYER_HITTED)
		return;

	pos.x += m_ptJumpGradient.x * m_fJumpSpeed * DT;
	pos.y -= m_ptJumpGradient.y * m_fJumpSpeed * DT;

	
}

void Player::Spring_Jump()
{
	if (state != PLAYER_SPRINGJUMP)
		return;

	pos.y = pos.y - DT * m_fSpringSpeed;

	if (m_bOnGround == true)
		state = PLAYER_STOP;
}

void Player::CharactorMove()
{
	if (state == PLAYER_SPINNING || m_bClimbOn == true || m_Animation == ANI_TRANSFORM)
		return;

	pos.x = pos.x + m_ptGradient.x * DT * m_fSpeed;
	pos.y = pos.y - m_ptGradient.y * DT * m_fSpeed;

	
}

void Player::SwitchAnimation()
{
	switch (m_Animation)
	{
	case ANI_STOP:
		if (m_bDir  == DIR_RIGHT)
			Anim->PlayAnimation(L"rightidle1");
		else
			Anim->PlayAnimation(L"leftidle1");
		break;
	case ANI_iDLE:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightidle2");
		else
			Anim->PlayAnimation(L"leftidle2");
		break;
	case ANI_ROLL:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightroll");
		else
			Anim->PlayAnimation(L"leftroll");
		break;

	case ANI_JUMP:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightroll");
		else
			Anim->PlayAnimation(L"leftroll");

		break;

	case ANI_CROUCH:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightcrouch");
		else
			Anim->PlayAnimation(L"leftcrouch");

		break;
	case ANI_SIT:
		if (m_eOldAnimation == ANI_SIT)
			break;
		
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightsit",0);
		else
			Anim->PlayAnimation(L"leftsit",0);

		break;
	case ANI_LOOKUP:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightlookup");
		else
			Anim->PlayAnimation(L"leftlookup");

		break;

	case ANI_WALK:
		if (m_bDir == DIR_RIGHT)
		{
			if (m_fSpeed < 200 && m_fSpeed > -200)
			{
				if (m_ptGradient.x >= 0.8f)
					Anim->PlayAnimation(L"rightwalk");
				
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_R1");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_R2");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_R3");

				else if (m_ptGradient.x <= -0.8f)
					Anim->PlayAnimation(L"walk_R4");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R5");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R6");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R7");
			}
			else if ((m_fSpeed >= 200 && m_fSpeed < 300) || (m_fSpeed <-200 && m_fSpeed >= -300))
			{
				if (m_ptGradient.x >= 0.8f)
					Anim->PlayAnimation(L"rightwalk1");

				else if (m_ptGradient.x > 0.3 && m_ptGradient.x <= 0.8 && m_ptGradient.y > 0)
					Anim->PlayAnimation(L"walk_R1_1");

				else if (m_ptGradient.x > -0.3 && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0)
					Anim->PlayAnimation(L"walk_R2_1");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_R3_1");
			
				else if (m_ptGradient.x <= -0.8f)
					Anim->PlayAnimation(L"walk_R4_1");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R5_1");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R6_1");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R7_1");
			}
				
			else if ((m_fSpeed >= 300 && m_fSpeed < 400) || (m_fSpeed <-300 && m_fSpeed >= -400))
			{
				if (m_ptGradient.x >= 0.8f)
					Anim->PlayAnimation(L"rightwalk2");

				else if (m_ptGradient.x > 0.3 && m_ptGradient.x <= 0.8 && m_ptGradient.y > 0)
					Anim->PlayAnimation(L"walk_R1_2");

				else if (m_ptGradient.x > -0.3 && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0)
					Anim->PlayAnimation(L"walk_R2_2");
				
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_R3_2");

				else if (m_ptGradient.x <= -0.8f)
					Anim->PlayAnimation(L"walk_R4_2");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R5_2");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R6_2");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R7_2");
			}
				
			else if ((m_fSpeed >= 400 && m_fSpeed < ChangeWtoR) || (m_fSpeed < -400 && m_fSpeed > -ChangeWtoR))
			{
				if (m_ptGradient.x >= 0.8f)
					Anim->PlayAnimation(L"rightwalk3");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_R1_3");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_R2_3");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_R3_3");

				else if (m_ptGradient.x <= -0.8f)
					Anim->PlayAnimation(L"walk_R4_3");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R5_3");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R6_3");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_R7_3");

			}

			else if (m_fSpeed >= ChangeWtoR || m_fSpeed <= -ChangeWtoR)
			{
				if (m_ptGradient.x >= 0.8f)
					Anim->PlayAnimation(L"rightrun1");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"rightrun_1");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"rightrun_2");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"rightrun_3");

				else if (m_ptGradient.x <= -0.8f)
					Anim->PlayAnimation(L"rightrun_4");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"rightrun_5");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"rightrun_6");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"rightrun_7");
			}
			break;
		}
		
		else if (m_bDir != DIR_RIGHT)
		{
			if (m_fSpeed < 200 && m_fSpeed > -200)
			{
				if (m_ptGradient.x >= 0.8f)
					Anim->PlayAnimation(L"leftwalk");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_L7");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_L6");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_L5");

				else if (m_ptGradient.x <= -0.8f)
					Anim->PlayAnimation(L"walk_L4");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L3");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L2");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L1");
			}
			else if ((m_fSpeed >= 200 && m_fSpeed < 300) || (m_fSpeed <-200 && m_fSpeed >= -300))
			{
				if (m_ptGradient.x >= 0.8f)
					Anim->PlayAnimation(L"leftwalk1");

				else if (m_ptGradient.x > 0.3 && m_ptGradient.x <= 0.8 && m_ptGradient.y > 0)
					Anim->PlayAnimation(L"walk_L7_1");

				else if (m_ptGradient.x > -0.3 && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0)
					Anim->PlayAnimation(L"walk_L6_1");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_L5_1");

				else if (m_ptGradient.x <= -0.8f)
					Anim->PlayAnimation(L"walk_L4_1");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L3_1");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L2_1");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L1_1");
			}

			else if ((m_fSpeed >= 300 && m_fSpeed < 400) || (m_fSpeed <-300 && m_fSpeed >= -400))
			{
				if (m_ptGradient.x >= 0.8f)
					Anim->PlayAnimation(L"leftwalk2");

				else if (m_ptGradient.x > 0.3 && m_ptGradient.x <= 0.8 && m_ptGradient.y > 0)
					Anim->PlayAnimation(L"walk_L7_2");

				else if (m_ptGradient.x > -0.3 && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0)
					Anim->PlayAnimation(L"walk_L6_2");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_L5_2");

				else if (m_ptGradient.x <= -0.8f)
					Anim->PlayAnimation(L"walk_L4_2");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L3_2");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L2_2");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L1_2");
			}

			else if ((m_fSpeed >= 400 && m_fSpeed < ChangeWtoR) || (m_fSpeed < -400 && m_fSpeed > -ChangeWtoR))
			{
				if (m_ptGradient.x >= 0.8f)
					Anim->PlayAnimation(L"leftwalk3");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_L7_3");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_L6_3");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"walk_L5_3");

				else if (m_ptGradient.x <= -0.8f)
					Anim->PlayAnimation(L"walk_L4_3");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L3_3");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L2_3");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"walk_L1_3");

			}
			else if (m_fSpeed >= ChangeWtoR || m_fSpeed <= -ChangeWtoR)
			{
				if (m_ptGradient.x >= 0.8f)
					Anim->PlayAnimation(L"leftrun1");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"leftrun_7");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"leftrun_6");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
					Anim->PlayAnimation(L"leftrun_5");

				else if (m_ptGradient.x <= -0.8f)
					Anim->PlayAnimation(L"leftrun_4");

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"leftrun_3");

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"leftrun_2");

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
					Anim->PlayAnimation(L"leftrun_1");
			}
			break;
		}
		

	case ANI_BREAK:
		if (m_eOldAnimation != ANI_BREAK)
		{
			if (m_bDir == DIR_RIGHT)
				Anim->PlayAnimation(L"rightbreak", 0);
			else
				Anim->PlayAnimation(L"leftbreak", 0);
		}
		break;

	case ANI_SPIN:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightspin");
		else
			Anim->PlayAnimation(L"leftspin");
		break;

	case ANI_SPINING:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"spiningright");
		else
			Anim->PlayAnimation(L"spiningleft");
		break;
	case ANI_SPiNINGTURN_00:
		Anim->PlayAnimation(L"spining_turn_00");
		break;
	case ANI_SPiNINGTURN_01:
		Anim->PlayAnimation(L"spining_turn_01");
		break;
	case ANI_SPiNINGTURN_02:
		Anim->PlayAnimation(L"spining_turn_02");
		break;
	case ANI_CLIMB:
		if (m_bDir == DIR_RIGHT)
		{
			if (m_AccTime >= 0 && m_AccTime <1)
				Anim->PlayAnimation(L"rightclimb_00");
			if (m_AccTime >= 1 && m_AccTime <2)
				Anim->PlayAnimation(L"rightclimb_01");
			if (m_AccTime >= 2 && m_AccTime <3)
				Anim->PlayAnimation(L"rightclimb_02");
			if (m_AccTime >= 3 && m_AccTime <4)
				Anim->PlayAnimation(L"rightclimb_03");
			if (m_AccTime >= 4 && m_AccTime <5)
				Anim->PlayAnimation(L"rightclimb_04");
			if (m_AccTime >= 5 && m_AccTime <=6)
				Anim->PlayAnimation(L"rightclimb_05");
		}
			
		else
		{
			if (m_AccTime >= 0 && m_AccTime <1)
				Anim->PlayAnimation(L"leftclimb_00");
			if (m_AccTime >= 1 && m_AccTime <2)
				Anim->PlayAnimation(L"leftclimb_01");
			if (m_AccTime >= 2 && m_AccTime <3)
				Anim->PlayAnimation(L"leftclimb_02");
			if (m_AccTime >= 3 && m_AccTime <4)
				Anim->PlayAnimation(L"leftclimb_03");
			if (m_AccTime >= 4 && m_AccTime <5)
				Anim->PlayAnimation(L"leftclimb_04");
			if (m_AccTime >= 5 && m_AccTime <= 6)
				Anim->PlayAnimation(L"leftclimb_05");
		}
		break;
	case ANI_DROP:
		if (m_eOldAnimation != ANI_DROP)
		{
			if(m_bDir == DIR_RIGHT)
				Anim->PlayAnimation(L"rightdrop",0);

			else
				Anim->PlayAnimation(L"leftdrop", 0);
		}
		break;

	case ANI_PUSH:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightpush");

		else
			Anim->PlayAnimation(L"leftpush");
		break;

	case ANI_ENDCLIMB:
		if (m_bDir == DIR_RIGHT)
		{
			if(m_fEndClimbTime >= 0 && m_fEndClimbTime < 1)
				Anim->PlayAnimation(L"EndRClimb_01");
			else if(m_fEndClimbTime >= 1 && m_fEndClimbTime < 2)
				Anim->PlayAnimation(L"EndRClimb_02");
			else if (m_fEndClimbTime >= 2 && m_fEndClimbTime < 3)
				Anim->PlayAnimation(L"EndRClimb_03");
		}

		else
		{
			if (m_fEndClimbTime >= 0 && m_fEndClimbTime < 1)
				Anim->PlayAnimation(L"EndLClimb_01");
			else if (m_fEndClimbTime >= 1 && m_fEndClimbTime < 2)
				Anim->PlayAnimation(L"EndLClimb_02");
			else if (m_fEndClimbTime >= 2 && m_fEndClimbTime < 3)
				Anim->PlayAnimation(L"EndLClimb_03");
		}
		break;

	case ANI_SPRINGJUMP:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"SpringRjump");
		}

		else
		{
			Anim->PlayAnimation(L"SpringLjump");
		}
		break;

	case ANI_HITTED:
		if (m_eOldAnimation != ANI_HITTED)
		{
			if (m_bDir == DIR_RIGHT)
			{
				Anim->PlayAnimation(L"righthit", 0);
			}

			else if (m_bDir == DIR_LEFT)
			{
				Anim->PlayAnimation(L"lefthit", 0);
			}
		}
		break;

	case ANI_VICTORY:
		Anim->PlayAnimation(L"victory");
		break;
	case ANI_END:
		break;
	default:
		break;
	}
}

void Player::InvincibleTime()
{
	m_fInvincibleTime += DT;
	m_fAccRender += 10 * DT;

	if (m_fAccRender >= 0 && m_fAccRender < 1)
	{
		m_bRenderOn = false;
	}

	else if (m_fAccRender >= 1 && m_fAccRender < 2)
	{
		m_bRenderOn = true;
	}

	else if (m_fAccRender >= 2)
	{
		m_fAccRender = 0;
	}

	if (m_fInvincibleTime >= 3)
	{
		m_bInvincible = false;
		m_fInvincibleTime = 0;
		m_fAccRender = 0;
		m_bRenderOn = true;
	}
}

void Player::adjustCol()
{
	if (m_Animation == ANI_STOP)
	{
		size.y = KnuckleSizeY;
	}

	else if (m_Animation == ANI_SIT)
	{
		size.y = KnuckleSitSizeY;
	}

	else if (m_Animation == ANI_ROLL || m_Animation == ANI_JUMP)
	{
		size.y = KnuckleRollSizeY;
	}

	else if (m_Animation == ANI_WALK)
	{
		size.y = KnuckleWalkSizeY;
	}

	else if (m_Animation == ANI_CLIMB)
	{
		size.y = KnuckleClimbSizeY;
	}

}

void Player::MoveXPos(float _speed)
{
	 pos.x += _speed * DT; 
}

void Player::render(HDC _dc)
{
	if (DEBUGRENDER == true)
	{
		fPOINT CamPos = Camera::Cam().GetCamMousePos(fPOINT{ 0,200 });
		BitBlt(_dc, 0, 0, WindowSizeX, WindowSizeY, Col_DC, (int)CamPos.x, (int)CamPos.y, SRCCOPY);
		
		collider->render(_dc);
		char test[255] = {};

		sprintf_s(test, "x값 : %f", pos.x);
		TextOutA(_dc, 300, 20, test, (int)strlen(test));
		sprintf_s(test, "y값 : %f", pos.y);
		TextOutA(_dc, 300, 40, test, (int)strlen(test));
		sprintf_s(test, "Speed값 : %f", m_fSpeed);
		TextOutA(_dc, 300, 60, test, (int)strlen(test));
		sprintf_s(test, "중력값 : %f", m_ptGravity.y);
		TextOutA(_dc, 300, 80, test, (int)strlen(test));
		sprintf_s(test, "gradient.x값 : %f", m_ptGradient.x);
		TextOutA(_dc, 300, 100, test, (int)strlen(test));
		sprintf_s(test, "gradient.y값 : %f", m_ptGradient.y);
		TextOutA(_dc, 300, 120, test, (int)strlen(test));
		sprintf_s(test, "m_fAccSpeed값 : %f", m_fAccSpeed);
		TextOutA(_dc, 300, 140, test, (int)strlen(test));
		sprintf_s(test, "m_fJumpSpeed값 : %f", m_fJumpSpeed);
		TextOutA(_dc, 300, 160, test, (int)strlen(test));
		sprintf_s(test, "SpringJump값 : %f", m_fSpringSpeed);
		TextOutA(_dc, 300, 180, test, (int)strlen(test));
		sprintf_s(test, "JumpGradient.x값 : %f", m_ptJumpGradient.x);
		TextOutA(_dc, 300, 200, test, (int)strlen(test));
		sprintf_s(test, "JumpGradient.y값 : %f", m_ptJumpGradient.y);
		TextOutA(_dc, 300, 220, test, (int)strlen(test));
		sprintf_s(test, "m_bOnGround : %d", m_bOnGround);
		TextOutA(_dc, 300, 240, test, (int)strlen(test));
		sprintf_s(test, "m_bCanJump : %d", m_bCanJump);
		TextOutA(_dc, 300, 260, test, (int)strlen(test));
		sprintf_s(test, "m_fRingCnt : %d", m_iRingCnt);
		TextOutA(_dc, 300, 280, test, (int)strlen(test));
		sprintf_s(test, "m_fBreakSpeed : %f", m_fBreakSpeed);
		TextOutA(_dc, 300, 300, test, (int)strlen(test));

		fPOINT campos2 = Camera::Cam().GetCamPos(fPOINT{ x1, y1 });
		fPOINT campos3 = Camera::Cam().GetCamPos(fPOINT{ x2, y2 });
		fPOINT campos4 = Camera::Cam().GetCamPos(fPOINT{ r1, t1 });
		fPOINT campos5 = Camera::Cam().GetCamPos(fPOINT{ r2, t2 });
		fPOINT campos6 = Camera::Cam().GetCamPos(fPOINT{ i1, j1 });
		fPOINT campos7 = Camera::Cam().GetCamPos(fPOINT{ i2, j2 });
		fPOINT campos8 = Camera::Cam().GetCamPos(fPOINT{ p1, q1 });
		fPOINT campos9 = Camera::Cam().GetCamPos(fPOINT{ p2, q2 });

		Ellipse(_dc, (int)campos.x - 3, (int)campos.y - 3, (int)campos.x + 3, (int)campos.y + 3);
		Ellipse(_dc, (int)campos2.x - 3, (int)campos2.y - 3, (int)campos2.x + 3, (int)campos2.y + 3);
		Ellipse(_dc, (int)campos3.x - 3, (int)campos3.y - 3, (int)campos3.x + 3, (int)campos3.y + 3);

		Ellipse(_dc, (int)campos.x - 3, (int)campos.y - (int)size.y * 2 - 3, (int)campos.x + 3, (int)campos.y - (int)size.y * 2 + 3);
		Ellipse(_dc, (int)campos4.x - 3, (int)campos4.y - 3, (int)campos4.x + 3, (int)campos4.y + 3);
		Ellipse(_dc, (int)campos5.x - 3, (int)campos5.y - 3, (int)campos5.x + 3, (int)campos5.y + 3);

		Ellipse(_dc, (int)campos.x + (int)size.x - 3, (int)campos.y - (int)size.y - 3, (int)campos.x + (int)size.x + 3, (int)campos.y - (int)size.y + 3);
		Ellipse(_dc, (int)campos6.x - 3, (int)campos6.y - 3, (int)campos6.x + 3, (int)campos6.y + 3);
		Ellipse(_dc, (int)campos7.x - 3, (int)campos7.y - 3, (int)campos7.x + 3, (int)campos7.y + 3);

		Ellipse(_dc, (int)campos.x - (int)size.x - 3, (int)campos.y - (int)size.y - 3, (int)campos.x - (int)size.x + 3, (int)campos.y - (int)size.y + 3);
		Ellipse(_dc, (int)campos8.x - 3, (int)campos8.y - 3, (int)campos8.x + 3, (int)campos8.y + 3);
		Ellipse(_dc, (int)campos9.x - 3, (int)campos9.y - 3, (int)campos9.x + 3, (int)campos9.y + 3);

		MoveToEx(_dc, (int)campos.x, (int)campos.y, NULL);
		LineTo(_dc, (int)campos.x + (int)(m_ptGradient.x * m_fSpeed), (int)campos.y - (int)(m_ptGradient.y * m_fSpeed));
		

	}

	fPOINT diff = Camera::Cam().GetDiff();
	campos.x = pos.x - diff.x;
	campos.y = pos.y - diff.y;

	if (m_bRenderOn == true)
	{
		Anim->render(_dc, pos);
	}
}

void Player::init(STAGE_TYPE _type)
{
	m_eCurStage = _type;

	m_eOBJ_TYPE = Obj_PLAYER;

	if (STAGE_START == _type)
	{
		pTex_Col = ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Test\\TileMap_Col.bmp", L"Stage_Col");
		Col_DC = pTex_Col->GetTexDC();
	}

	else if (STAGE_00 == _type)
	{
		pTex_Col = ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_00\\Stage_00_Col.bmp", L"Stage_00_Col");
		Col_DC = pTex_Col->GetTexDC();
	}

	else if (STAGE_01 == _type)
	{
		pTex_Col = ResManager::Manager().LoadTexture(L"\\Map\\Stage\\Stage_01\\Stage_01_Col.bmp", L"Stage_01_Col");
		Col_DC = pTex_Col->GetTexDC();
	}
}

void Player::GravityON()
{

	if (state == PLAYER_SPINNING || m_bClimbOn == true || m_Animation == ANI_TRANSFORM || m_eCurStage == STAGE_FINAL)
		return;

	if (m_bOnGround == false)
	{
		m_ptGravity.y += 1700 * DT;
		pos.y += m_ptGravity.y * DT;

		if((m_fSpeed > 0 && m_fSpeed <= 500) || m_fSpeed >= 800)
			m_fSpeed -= m_ptGradient.y * m_ptGravity.y * DT;

		else if ((m_fSpeed < 0 && m_fSpeed >= -500) || m_fSpeed <= -800)
			m_fSpeed -= m_ptGradient.y * m_ptGravity.y * DT;
	}
	
	else if (m_bOnGround == true)
	{
		
	}

	//마찰력
	if (m_bCanJump == false)
		return;

	if (m_ptGradient.x >= 0.8f)
	{
		if (m_fSpeed >= 0)
		{
			m_fSpeed -= 300 * DT;

			if (m_fSpeed <= 0)
				m_fSpeed = 0;
		}
			

		if (m_fSpeed <= 0)
		{
			m_fSpeed += 300 * DT;

			if (m_fSpeed >= 0)
				m_fSpeed = 0;
		}
			
	}

	else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
	{
		m_fSpeed -= 350 * DT;
	}

	else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
	{
		m_fSpeed -= 600 * DT;
	}

	else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
	{
		m_fSpeed -= 600 * DT;
	}

	else if (m_ptGradient.x <= -0.8f)
	{
		m_fSpeed -= -600 * DT;
	}

	else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
	{
		m_fSpeed += 600 * DT;
	}

	else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
	{
		m_fSpeed += 600 * DT;
	}

	else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
	{
		m_fSpeed += 400 * DT;
	}
}

void Player::ShieldON()
{
	if (m_eShield == SHIELD_END)
		return;

	if (m_eShield == SHIELD_FIRE)
	{
		if (m_eOldShield == SHIELD_FIRE)
			return;

		FireShield* shield_fire = new FireShield;
		shield_fire->init(this);
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_SHIELD).push_back(shield_fire);

		FireShield_Back* shield_fire_back = new FireShield_Back;
		shield_fire_back->init(this);
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_FIRE).push_back(shield_fire_back);
	}

	else if (m_eShield == SHIELD_WATER)
	{
		if (m_eOldShield == SHIELD_WATER)
			return;

		WaterShield* shield_water = new WaterShield;
		shield_water->init(this);
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_SHIELD).push_back(shield_water);
	}

	else if (m_eShield == SHIELD_THUNDER)
	{
		if (m_eOldShield == SHIELD_THUNDER)
			return;

		ThunderShield* shield_thunder = new ThunderShield;
		shield_thunder->init(this);
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_SHIELD).push_back(shield_thunder);
	}
}


float Player::getRandomNumber(float min, float max)
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_real_distribution<float> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}

void Player::SpitOutRing()
{
	for (int i = 0; i < m_iRingCnt; ++i)
	{
		Ring* pRing = new Ring(true, getRandomNumber(0, (float)M_PI)
			, StageManager::Manager().GetCurStage()->GetFloorColor()
			, StageManager::Manager().GetCurStage()->GetWallColor()
			, StageManager::Manager().GetCurStageType());

		pRing->init(fPOINT{ pos.x, pos.y });
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_RING).push_back(pRing);
	}
}