#include "stdafx.h"
#include "Tail.h"
#include "ResManager.h"
#include "Animation.h"
#include "Animator.h"
#include "Camera.h"
#include "Collider.h"
#include "Texture.h"
#include "TimeManager.h"
#include "KeyManager.h"


Tail::Tail()
{
}

Tail::~Tail()
{
}



void Tail::render(HDC _dc)
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
		if (m_Animation != ANI_JUMP)
		{
			Anim->render(_dc, pos);
		}

		else
		{
			Anim->render(_dc, pos);
		}

		/*else if (m_Animation == ANI_JUMP)
		{
			if (m_ptOldPos.y >= pos.y)
			{
				Anim->render(_dc, fPOINT{ pos.x , pos.y + 40});
			}

			else
			{
				Anim->render(_dc, pos);
			}
		}*/
	}

}

void Tail::update()
{
	Camera::Cam().FollowPoint(pos);
	collider->update();

	m_ptOldPos = pos;
	m_ptOldGradient = m_ptGradient;
	m_eOldAnimation = m_Animation;

	Player::CharactorMove();

	switch (state)
	{
	case PLAYER_STOP:
		Player_Stop();
		break;
	//case PLAYER_iDLE:
	//	Player_Idle();
	//	break;
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
	case PLAYER_FLYING:
		Player_Flying();
		break;
	case PLAYER_RIGHTPUSH:
		Player_RightPush();
		break;
	case PLAYER_LEFTPUSH:
		Player_LeftPush();
		break;

	case PLAYER_SPRINGJUMP:
		Player_SpringJump();
		break;
	case PLAYER_HITTED:
		Player_Hitted();
		break;
	case PLAYER_FINISH:
		Player_Finish();
		break;
	case PLAYER_END:
		break;
	default:
		break;
	}


	Jump_Move();

	Player::Spring_Jump();

	Player::GravityON();

	Player::CheckPixel();

	if (state != PLAYER_JUMP)
		Player::CheckGradient();

	Player::Limit();

	adjustCol();

	Tail::SwitchAnimation();

	Player::CheckWall();

	Player::ChangeLayer();

	Player::ShieldON();

	if (m_Animation != m_eOldAnimation)
	{
		m_AccTime = 0;
	}
	if (m_bInvincible == true)
	{
		Player::InvincibleTime();
	}

	m_eOldShield = m_eShield;
}

void Tail::init(fPOINT _pos, STAGE_TYPE _type)
{
	Player::init(_type);

	pos = _pos;
	size = fPOINT{ 32 , 20 };

	m_ptOldPos = pos;
	gravity = 9.85f;
	m_AccTime = 0;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	//IDLE
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Idle\\Idle_Right.bmp", L"Tail_RightIdle");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Idle\\Idle_Left.bmp", L"Tail_LeftIdle");

	//WALK
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Right\\Right_Walk.bmp", L"Tail_RightWalk");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Left\\Left_Walk.bmp", L"Tail_LeftWalk");


	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Right\\Walk_1.bmp", L"Tail_Walk_R1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Right\\Walk_2.bmp", L"Tail_Walk_R2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Right\\Walk_3.bmp", L"Tail_Walk_R3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Right\\Walk_4.bmp", L"Tail_Walk_R4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Right\\Walk_5.bmp", L"Tail_Walk_R5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Right\\Walk_6.bmp", L"Tail_Walk_R6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Right\\Walk_7.bmp", L"Tail_Walk_R7");
													 

	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Left\\Walk_1.bmp", L"Tail_Walk_L1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Left\\Walk_2.bmp", L"Tail_Walk_L2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Left\\Walk_3.bmp", L"Tail_Walk_L3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Left\\Walk_4.bmp", L"Tail_Walk_L4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Left\\Walk_5.bmp", L"Tail_Walk_L5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Left\\Walk_6.bmp", L"Tail_Walk_L6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Walk\\Left\\Walk_7.bmp", L"Tail_Walk_L7");


	//RUN

	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Right\\RightRun.bmp", L"Tail_RightRun");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Left\\LeftRun.bmp", L"Tail_LeftRun");


	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Right\\Run_1.bmp", L"Tail_RightRun_1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Right\\Run_2.bmp", L"Tail_RightRun_2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Right\\Run_3.bmp", L"Tail_RightRun_3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Right\\Run_4.bmp", L"Tail_RightRun_4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Right\\Run_5.bmp", L"Tail_RightRun_5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Right\\Run_6.bmp", L"Tail_RightRun_6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Right\\Run_7.bmp", L"Tail_RightRun_7");


	////////////////////////////////////
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Left\\Run_1.bmp", L"Tail_LeftRun_1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Left\\Run_2.bmp", L"Tail_LeftRun_2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Left\\Run_3.bmp", L"Tail_LeftRun_3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Left\\Run_4.bmp", L"Tail_LeftRun_4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Left\\Run_5.bmp", L"Tail_LeftRun_5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Left\\Run_6.bmp", L"Tail_LeftRun_6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Run\\Left\\Run_7.bmp", L"Tail_LeftRun_7");


	//BREAK
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Break\\Right_Break.bmp", L"Tail_RightBreak");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Break\\Left_Break.bmp", L"Tail_LeftBreak");

	//JUMP
	/*ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Jump\\Up\\Right_Jump.bmp", L"Tail_RightJump");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Jump\\Up\\Left_Jump.bmp", L"Tail_LeftJump");
	
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Jump\\Up\\Right_Jump_01.bmp", L"Tail_RightJump_01");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Jump\\Up\\Left_Jump_01.bmp", L"Tail_LeftJump_01");

	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Jump\\Down\\Right_Jump_Down.bmp", L"Tail_RightJump_Down");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Jump\\Down\\Left_Jump_Down.bmp", L"Tail_LeftJump_Down");*/

	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Jump\\Jump_Up.bmp", L"Tail_Jump_up");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Jump\\Jump_Down.bmp", L"Tail_Jump_down");

	//CROUCH
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Crouch\\Right_Crouch.bmp", L"Tail_Right_Crouch");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Crouch\\Left_Crouch.bmp", L"Tail_Left_Crouch");

	//SPIN
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Spin\\Right_Spin.bmp", L"Tail_Right_Spin");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Spin\\Left_Spin.bmp", L"Tail_Left_Spin");

	//ROLL
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Roll\\Right_Roll.bmp", L"Tail_Right_Roll");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Roll\\Left_Roll.bmp", L"Tail_Left_Roll");

	//PUSH
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Push\\Right_Push.bmp", L"Tail_Right_Push");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Push\\Left_Push.bmp", L"Tail_Left_Push");

	//SPRING
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\SpringJump\\Right_Spring_Jump.bmp", L"Tail_Right_SpringJump");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\SpringJump\\Left_Spring_Jump.bmp", L"Tail_Left_SpringJump");

	//FLY
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Fly\\Right_Fly.bmp", L"Tail_Right_Fly");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Fly\\Left_Fly.bmp", L"Tail_Left_Fly");

	//HITTED
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Hitted\\RightHitted.bmp", L"Tail_RightHit");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Hitted\\LeftHitted.bmp", L"Tail_LeftHit");

	//LOOKUP
	//LOOKUP
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\LookUp\\Right_Lookup.bmp", L"Tail_RightLookup");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\LookUp\\Left_Lookup.bmp", L"Tail_LeftLookup");

	//Victory
	ResManager::Manager().LoadTexture(L"\\Charactor\\Tail\\Victory\\Victory.bmp", L"Tail_Victory");

	Anim = new Animator;
	//IDLE

	//idle right
	Anim->AddAnimation(L"rightidle1", ResManager::Manager().FindTexture(L"Tail_RightIdle"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightidle2", ResManager::Manager().FindTexture(L"Tail_RightIdle"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 7, 0.2f, RGB(255, 0, 255), 0);
	//idle left;
	Anim->AddAnimation(L"leftidle1", ResManager::Manager().FindTexture(L"Tail_LeftIdle"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 7, 1000.f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftidle2", ResManager::Manager().FindTexture(L"Tail_LeftIdle"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 7, 0.2f, RGB(255, 0, 255), 0);

	//WALK
	Anim->AddAnimation(L"rightwalk", ResManager::Manager().FindTexture(L"Tail_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk", ResManager::Manager().FindTexture(L"Tail_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightwalk1", ResManager::Manager().FindTexture(L"Tail_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk1", ResManager::Manager().FindTexture(L"Tail_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightwalk2", ResManager::Manager().FindTexture(L"Tail_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk2", ResManager::Manager().FindTexture(L"Tail_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightwalk3", ResManager::Manager().FindTexture(L"Tail_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk3", ResManager::Manager().FindTexture(L"Tail_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	//속도0
	Anim->AddAnimation(L"walk_R1", ResManager::Manager().FindTexture(L"Tail_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2", ResManager::Manager().FindTexture(L"Tail_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3", ResManager::Manager().FindTexture(L"Tail_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4", ResManager::Manager().FindTexture(L"Tail_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5", ResManager::Manager().FindTexture(L"Tail_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6", ResManager::Manager().FindTexture(L"Tail_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7", ResManager::Manager().FindTexture(L"Tail_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	//속도1
	Anim->AddAnimation(L"walk_R1_1", ResManager::Manager().FindTexture(L"Tail_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2_1", ResManager::Manager().FindTexture(L"Tail_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3_1", ResManager::Manager().FindTexture(L"Tail_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4_1", ResManager::Manager().FindTexture(L"Tail_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5_1", ResManager::Manager().FindTexture(L"Tail_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6_1", ResManager::Manager().FindTexture(L"Tail_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7_1", ResManager::Manager().FindTexture(L"Tail_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	//속도2					 	   
	Anim->AddAnimation(L"walk_R1_2", ResManager::Manager().FindTexture(L"Tail_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2_2", ResManager::Manager().FindTexture(L"Tail_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3_2", ResManager::Manager().FindTexture(L"Tail_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4_2", ResManager::Manager().FindTexture(L"Tail_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5_2", ResManager::Manager().FindTexture(L"Tail_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6_2", ResManager::Manager().FindTexture(L"Tail_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7_2", ResManager::Manager().FindTexture(L"Tail_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	//속도3					  		   
	Anim->AddAnimation(L"walk_R1_3", ResManager::Manager().FindTexture(L"Tail_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2_3", ResManager::Manager().FindTexture(L"Tail_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3_3", ResManager::Manager().FindTexture(L"Tail_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4_3", ResManager::Manager().FindTexture(L"Tail_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5_3", ResManager::Manager().FindTexture(L"Tail_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6_3", ResManager::Manager().FindTexture(L"Tail_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7_3", ResManager::Manager().FindTexture(L"Tail_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	/////////////////////left
	//속도0

	Anim->AddAnimation(L"walk_L1", ResManager::Manager().FindTexture(L"Tail_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2", ResManager::Manager().FindTexture(L"Tail_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3", ResManager::Manager().FindTexture(L"Tail_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4", ResManager::Manager().FindTexture(L"Tail_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5", ResManager::Manager().FindTexture(L"Tail_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6", ResManager::Manager().FindTexture(L"Tail_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7", ResManager::Manager().FindTexture(L"Tail_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	//속도1
	Anim->AddAnimation(L"walk_L1_1", ResManager::Manager().FindTexture(L"Tail_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2_1", ResManager::Manager().FindTexture(L"Tail_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3_1", ResManager::Manager().FindTexture(L"Tail_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4_1", ResManager::Manager().FindTexture(L"Tail_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5_1", ResManager::Manager().FindTexture(L"Tail_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6_1", ResManager::Manager().FindTexture(L"Tail_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7_1", ResManager::Manager().FindTexture(L"Tail_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	//속도2													 
	Anim->AddAnimation(L"walk_L1_2", ResManager::Manager().FindTexture(L"Tail_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2_2", ResManager::Manager().FindTexture(L"Tail_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3_2", ResManager::Manager().FindTexture(L"Tail_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4_2", ResManager::Manager().FindTexture(L"Tail_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5_2", ResManager::Manager().FindTexture(L"Tail_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6_2", ResManager::Manager().FindTexture(L"Tail_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7_2", ResManager::Manager().FindTexture(L"Tail_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
																		 
	//속도3													 			 
	Anim->AddAnimation(L"walk_L1_3", ResManager::Manager().FindTexture(L"Tail_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2_3", ResManager::Manager().FindTexture(L"Tail_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3_3", ResManager::Manager().FindTexture(L"Tail_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4_3", ResManager::Manager().FindTexture(L"Tail_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5_3", ResManager::Manager().FindTexture(L"Tail_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6_3", ResManager::Manager().FindTexture(L"Tail_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7_3", ResManager::Manager().FindTexture(L"Tail_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	//RUN
	Anim->AddAnimation(L"rightrun1", ResManager::Manager().FindTexture(L"Tail_RightRun"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 5, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun1", ResManager::Manager().FindTexture(L"Tail_LeftRun"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 5, 0.025f, RGB(255, 0, 255), 0);

	/////////////////////
	Anim->AddAnimation(L"rightrun_1", ResManager::Manager().FindTexture(L"Tail_RightRun_1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 6, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_2", ResManager::Manager().FindTexture(L"Tail_RightRun_2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 5, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_3", ResManager::Manager().FindTexture(L"Tail_RightRun_3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 6, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_4", ResManager::Manager().FindTexture(L"Tail_RightRun_4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 5, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_5", ResManager::Manager().FindTexture(L"Tail_RightRun_5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 6, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_6", ResManager::Manager().FindTexture(L"Tail_RightRun_6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 5, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_7", ResManager::Manager().FindTexture(L"Tail_RightRun_7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 6, 0.025f, RGB(255, 0, 255), 0);

	//////////////////////////////////////
	Anim->AddAnimation(L"leftrun_1", ResManager::Manager().FindTexture(L"Tail_LeftRun_1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 6, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_2", ResManager::Manager().FindTexture(L"Tail_LeftRun_2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 5, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_3", ResManager::Manager().FindTexture(L"Tail_LeftRun_3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 6, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_4", ResManager::Manager().FindTexture(L"Tail_LeftRun_4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 5, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_5", ResManager::Manager().FindTexture(L"Tail_LeftRun_5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 6, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_6", ResManager::Manager().FindTexture(L"Tail_LeftRun_6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 5, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_7", ResManager::Manager().FindTexture(L"Tail_LeftRun_7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 6, 0.025f, RGB(255, 0, 255), 0);

	//BREAK
	Anim->AddAnimation(L"rightbreak", ResManager::Manager().FindTexture(L"Tail_RightBreak"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.1f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"leftbreak", ResManager::Manager().FindTexture(L"Tail_LeftBreak"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.1f, RGB(255, 0, 255), 1);

	//JUMP
	/*Anim->AddAnimation(L"rightjump", ResManager::Manager().FindTexture(L"Tail_RightJump"), fPOINT{ 0,40 }, 1, fPOINT{ 100,100 }, 12, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftjump", ResManager::Manager().FindTexture(L"Tail_LeftJump"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 12, 0.05f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightjump_01", ResManager::Manager().FindTexture(L"Tail_RightJump_01"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 12, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftjump_01", ResManager::Manager().FindTexture(L"Tail_LeftJump_01"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 12, 0.05f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightjump_down", ResManager::Manager().FindTexture(L"Tail_RightJump_Down"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 12, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftjump_down", ResManager::Manager().FindTexture(L"Tail_LeftJump_Down"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 12, 0.05f, RGB(255, 0, 255), 0);
*/

	Anim->AddAnimation(L"jump_up", ResManager::Manager().FindTexture(L"Tail_Jump_up"), fPOINT{ 0,40 }, 1, fPOINT{ 100,100 }, 12, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"jump_down", ResManager::Manager().FindTexture(L"Tail_Jump_down"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 12, 0.05f, RGB(255, 0, 255), 0);

	//CROUCH
	Anim->AddAnimation(L"rightcrouch", ResManager::Manager().FindTexture(L"Tail_Right_Crouch"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 5, 0.08f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftcrouch", ResManager::Manager().FindTexture(L"Tail_Left_Crouch"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 5, 0.08f, RGB(255, 0, 255), 0);

	//SPIN
	Anim->AddAnimation(L"rightspin", ResManager::Manager().FindTexture(L"Tail_Right_Spin"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 5, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftspin", ResManager::Manager().FindTexture(L"Tail_Left_Spin"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 5, 0.05f, RGB(255, 0, 255), 0);

	//ROLL
	Anim->AddAnimation(L"rightroll", ResManager::Manager().FindTexture(L"Tail_Right_Roll"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 3, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftroll", ResManager::Manager().FindTexture(L"Tail_Left_Roll"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 3, 0.05f, RGB(255, 0, 255), 0);

	//PUSH
	Anim->AddAnimation(L"rightpush", ResManager::Manager().FindTexture(L"Tail_Right_Push"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 12, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftpush", ResManager::Manager().FindTexture(L"Tail_Left_Push"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 12, 0.1f, RGB(255, 0, 255), 0);

	//SPRINGJUMP
	Anim->AddAnimation(L"SpringRjump", ResManager::Manager().FindTexture(L"Tail_Right_SpringJump"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 12, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"SpringLjump", ResManager::Manager().FindTexture(L"Tail_Left_SpringJump"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 12, 0.1f, RGB(255, 0, 255), 0);

	//FLY
	Anim->AddAnimation(L"rightfly", ResManager::Manager().FindTexture(L"Tail_Right_Fly"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftfly", ResManager::Manager().FindTexture(L"Tail_Left_Fly"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);

	//HITTED
	Anim->AddAnimation(L"righthit", ResManager::Manager().FindTexture(L"Tail_RightHit"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.08f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"lefthit", ResManager::Manager().FindTexture(L"Tail_LeftHit"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.08f, RGB(255, 0, 255), 1);

	//LOOKUP
	Anim->AddAnimation(L"rightlookup", ResManager::Manager().FindTexture(L"Tail_RightLookup"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 5, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftlookup", ResManager::Manager().FindTexture(L"Tail_LeftLookup"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 5, 0.1f, RGB(255, 0, 255), 0);

	//Victory
	Anim->AddAnimation(L"victory", ResManager::Manager().FindTexture(L"Tail_Victory"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 3, 0.2f, RGB(255, 0, 255), 1);


	Anim->PlayAnimation(L"rightidle1");
}



void Tail::SwitchAnimation()
{
	switch (m_Animation)
	{
	case ANI_STOP:
		if (m_bDir == DIR_RIGHT)
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


	case ANI_JUMP:

		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightroll");
		else
			Anim->PlayAnimation(L"leftroll");
		break;


	/*	if (m_ptOldPos.y >= pos.y)
		{
			Anim->PlayAnimation(L"jump_up");
		}

		else if (m_ptOldPos.y < pos.y)
		{
			Anim->PlayAnimation(L"jump_down");
		}

		break;*/
			
	/*case ANI_RIGHTJUMP:
		Anim->PlayAnimation(L"rightjump_01");			
		break;

	case ANI_LEFTJUMP:
		Anim->PlayAnimation(L"leftjump_01");
		break;*/

	case ANI_CROUCH:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightcrouch");
		else
			Anim->PlayAnimation(L"leftcrouch");
		break;
	case ANI_SIT:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightcrouch");
		else
			Anim->PlayAnimation(L"leftcrouch");
		break;

	case ANI_ROLL:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightroll");
		else
			Anim->PlayAnimation(L"leftroll");
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



	case ANI_PUSH:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"rightpush");

		else
			Anim->PlayAnimation(L"leftpush");
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

	case ANI_FLY:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"rightfly");
		}

		else
		{
			Anim->PlayAnimation(L"leftfly");
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

void Tail::adjustCol()
{
	if (m_Animation == ANI_STOP)
	{
		size.y = TailSize;
	}

	if (m_Animation == ANI_SIT)
	{
		size.y = TailCrouchSize;
	}



}

void Tail::Jump_Move()
{
	if (state != PLAYER_JUMP && state != PLAYER_HITTED && state != PLAYER_FLYING)
		return;

	pos.x += m_ptJumpGradient.x * m_fJumpSpeed * DT;
	pos.y -= m_ptJumpGradient.y * m_fJumpSpeed * DT;

}

void Tail::Player_Jump()
{
	m_Animation = ANI_JUMP;

	if (true == m_bRightWallOn || true == m_bLeftWallOn)
	{
		m_fSpeed = 0.f;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
	{
		//m_Animation = ANI_RIGHTJUMP;
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
		//m_Animation = ANI_LEFTJUMP;
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

	if (m_bOnGround == true)
	{
		m_fSpeed = m_ptJumpGradient.x * m_fJumpSpeed + m_ptGradient.x * m_fSpeed;
		m_fJumpSpeed = 0;

		state = PLAYER_STOP;

		return;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB))
	{
		m_ptGravity.y = 0;
		m_ptGradient.x = 1.f;
		m_ptGradient.y = 0.f;
		m_fJumpSpeed = 350;
		state = PLAYER_FLYING;
		m_bOnGround = false;
	}
}

void Tail::Player_Flying()
{
	m_Animation = ANI_FLY;
	
	if (true == KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB))
	{
		m_ptGravity.y = 0;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
	{
		m_bDir = DIR_RIGHT;
		m_fSpeed += 200 * DT;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
	{
		m_bDir = DIR_LEFT;
		m_fSpeed -= 300 * DT;
	}

	if (m_bOnGround == true)
	{
		state = PLAYER_STOP;
	}
}

