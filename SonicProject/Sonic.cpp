#include "stdafx.h"
#include "Sonic.h"
#include "ResManager.h"
#include "Animation.h"
#include "Animator.h"
#include "Camera.h"
#include "Collider.h"
#include "Texture.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "Effect_Fire.h"
#include "StageManager.h"
#include "Stage.h"
#include "Shield.h"
#include "FireShield.h"
#include "FireShield_Back.h"
#include "WaterShield.h"
#include "SoundManager.h"

Sonic::Sonic()
	:m_WhiteAnim(NULL)
	, m_fAccRender(0.f)
	, m_bRenderChange(false)
	, m_SuperEffect(NULL)
	, m_fSuperHittedTime(0.f)
	, m_fSuperDashTime(0.f)
	, m_fSuperSonicTime(0.f)
	, m_bSuperDashOn(false)
{
}


Sonic::~Sonic()
{
	if (m_WhiteAnim != NULL)
	{
		delete m_WhiteAnim;
	}

	if (m_SuperEffect != NULL)
	{
		delete m_SuperEffect;
	}
}

void Sonic::Player_FireSkill()
{
	m_ptGradient.x = 1;
	m_ptGradient.y = 0;

	if (m_bDir == DIR_RIGHT)
	{
		m_fSpeed = 1000;
	}

	else if (m_bDir == DIR_LEFT)
	{
		m_fSpeed = -1000;
	}

	if (m_bOnGround == true)
	{
		state = PLAYER_STOP;
	}

	if (m_bRightWallOn == true || m_bLeftWallOn == true)
	{
		state = PLAYER_STOP;
	}
}

void Sonic::Player_WaterSkill()
{
	if (m_bOnGround == true)
	{
		state = PLAYER_JUMP;

		m_fJumpSpeed = 900;
		m_ptGravity.y = 0;
	}

}

void Sonic::Player_ThunderSkill()
{
}

void Sonic::RanderChange()
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



void Sonic::render(HDC _dc)
{
	if (m_bSuperSonic == false)
	{
		Player::render(_dc);
	}

	else if (m_bSuperSonic == true)
	{
		if(m_fSpeed >= 500 || m_fSpeed <= -500 || state == PLAYER_JUMP || state == PLAYER_SPRINGJUMP)
			RendAfterImage(_dc);
			
		if (m_bRenderChange == true)
		{
			Player::render(_dc);
			m_WhiteAnim->render(_dc, pos);
		}

		else if (m_bRenderChange == false)
		{
			m_WhiteAnim->render(_dc, pos);
			Player::render(_dc);
		}
		m_SuperEffect->render(_dc, fPOINT{pos.x, pos.y + 60});
	}
}

void Sonic::update()
{
	Camera::Cam().FollowPoint(pos);
	collider->update();

	SetOldPos();

	m_ptOldGradient = m_ptGradient;

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
	case PLAYER_FIRESKILL:
		Player_FireSkill();
		break;
	case PLAYER_THUNDERSKILL:
		Player_ThunderSkill();
		break;
	case PLAYER_WATERSKILL:
		Player_WaterSkill();
		break;
	case PLAYER_FINISH:
		Player_Finish();
		break;
	case PLAYER_TRANSFORM:
		Player_TransForm();
		break;
	case PLAYER_FINALSTAGE:
		Player_FinalStage();
		break;
	case PLAYER_END:
		break;
	default:
		break;
	}

	Jump_Move();

	Spring_Jump();

	GravityON();

	CheckPixel();

	if (state != PLAYER_JUMP)
		CheckGradient();

	Limit();

	CharactorMove();

	adjustCol();

	if (m_bSuperSonic == false)
		SwitchAnimation();

	else if (m_bSuperSonic == true)
		SwitchSuperAnimation();

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

	RanderChange();

	if(m_bSuperSonic == true)
		CheckSuperSonicTime();

	m_eOldAnimation = m_Animation;

	m_eOldShield = m_eShield;
}

void Sonic::init(fPOINT _pos, STAGE_TYPE _type)
{
	Player::init(_type);

	pos = _pos;
	size = fPOINT{ 32 , 40 };

	m_ptOldPos = pos;
	gravity = 9.85f;
	m_AccTime = 0;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	//이펙트 로드
	m_SuperEffect = new Animator;
	ResManager::Manager().LoadTexture(L"\\Effect\\Super_Effect.bmp", L"SuperSonic_Effect");

	m_SuperEffect->AddAnimation(L"Super_Effect", ResManager::Manager().FindTexture(L"SuperSonic_Effect"), fPOINT{ 0,0 }, 1, fPOINT{ 200,200 }, 2, 0.05f, RGB(255, 0, 255), 0);
	m_SuperEffect->PlayAnimation(L"Super_Effect");


	//IDLE
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Idle\\Idle_Right.bmp", L"Sonic_RightIdle");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Idle\\Idle_Left.bmp", L"Sonic_LeftIdle");

	//WALK
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Right\\Right_Walk.bmp", L"Sonic_RightWalk");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Left\\Left_Walk.bmp", L"Sonic_LeftWalk");


	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Right\\Walk_1.bmp", L"Sonic_Walk_R1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Right\\Walk_2.bmp", L"Sonic_Walk_R2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Right\\Walk_3.bmp", L"Sonic_Walk_R3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Right\\Walk_4.bmp", L"Sonic_Walk_R4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Right\\Walk_5.bmp", L"Sonic_Walk_R5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Right\\Walk_6.bmp", L"Sonic_Walk_R6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Right\\Walk_7.bmp", L"Sonic_Walk_R7");


	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Left\\Walk_1.bmp", L"Sonic_Walk_L1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Left\\Walk_2.bmp", L"Sonic_Walk_L2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Left\\Walk_3.bmp", L"Sonic_Walk_L3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Left\\Walk_4.bmp", L"Sonic_Walk_L4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Left\\Walk_5.bmp", L"Sonic_Walk_L5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Left\\Walk_6.bmp", L"Sonic_Walk_L6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Walk\\Left\\Walk_7.bmp", L"Sonic_Walk_L7");


	//RUN
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Right\\RightRun.bmp", L"Sonic_RightRun");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Left\\LeftRun.bmp", L"Sonic_LeftRun");


	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Right\\Run_1.bmp", L"Sonic_RightRun_1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Right\\Run_2.bmp", L"Sonic_RightRun_2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Right\\Run_3.bmp", L"Sonic_RightRun_3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Right\\Run_4.bmp", L"Sonic_RightRun_4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Right\\Run_5.bmp", L"Sonic_RightRun_5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Right\\Run_6.bmp", L"Sonic_RightRun_6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Right\\Run_7.bmp", L"Sonic_RightRun_7");


	////////////////////////////////////
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Left\\Run_1.bmp", L"Sonic_LeftRun_1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Left\\Run_2.bmp", L"Sonic_LeftRun_2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Left\\Run_3.bmp", L"Sonic_LeftRun_3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Left\\Run_4.bmp", L"Sonic_LeftRun_4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Left\\Run_5.bmp", L"Sonic_LeftRun_5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Left\\Run_6.bmp", L"Sonic_LeftRun_6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Run\\Left\\Run_7.bmp", L"Sonic_LeftRun_7");


	//BREAK
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Break\\Right_Break.bmp", L"Sonic_RightBreak");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Break\\Left_Break.bmp", L"Sonic_LeftBreak");

	//JUMP
	
	//ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Roll\\Right_Roll.bmp", L"Sonic_Right_Roll");
	//ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Roll\\Left_Roll.bmp", L"Sonic_Left_Roll");

	//CROUCH
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Crouch\\Right_Crouch.bmp", L"Sonic_Right_Crouch");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Crouch\\Left_Crouch.bmp", L"Sonic_Left_Crouch");

	//SPIN
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Spin\\Right_Spin.bmp", L"Sonic_Right_Spin");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Spin\\Left_Spin.bmp", L"Sonic_Left_Spin");

	//ROLL
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Roll\\Right_Roll.bmp", L"Sonic_Right_Roll");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Roll\\Left_Roll.bmp", L"Sonic_Left_Roll");

	//PUSH
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Push\\Right_Push.bmp", L"Sonic_Right_Push");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Push\\Left_Push.bmp", L"Sonic_Left_Push");

	//SPRING
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\SpringJump\\Right_Spring_Jump.bmp", L"Sonic_Right_SpringJump");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\SpringJump\\Left_Spring_Jump.bmp", L"Sonic_Left_SpringJump");

	//LOOKUP
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\LookUp\\Right_Lookup.bmp", L"Sonic_RightLookup");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\LookUp\\Left_Lookup.bmp", L"Sonic_LeftLookup");

	//HITTED
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Hitted\\RightHitted.bmp", L"Sonic_RightHit");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Hitted\\LeftHitted.bmp", L"Sonic_LeftHit");

	//Victory
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\Victory\\Victory.bmp", L"Sonic_Victory");

	//TransForm
	ResManager::Manager().LoadTexture(L"\\Charactor\\Sonic\\TransForm\\TransForm.bmp", L"Sonic_TransForm");


	Anim = new Animator;

	//TransForm
	Anim->AddAnimation(L"TransForm", ResManager::Manager().FindTexture(L"Sonic_TransForm"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 6, 0.1f, RGB(255, 0, 255), 1);

	//IDLE

	//idle right
	Anim->AddAnimation(L"rightidle1", ResManager::Manager().FindTexture(L"Sonic_RightIdle"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.2f, RGB(255, 0, 255), 0);
	
	//idle left;
	Anim->AddAnimation(L"leftidle1", ResManager::Manager().FindTexture(L"Sonic_LeftIdle"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 1000.f, RGB(255, 0, 255), 0);
	

	//WALK
	Anim->AddAnimation(L"rightwalk", ResManager::Manager().FindTexture(L"Sonic_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk", ResManager::Manager().FindTexture(L"Sonic_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightwalk1", ResManager::Manager().FindTexture(L"Sonic_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk1", ResManager::Manager().FindTexture(L"Sonic_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightwalk2", ResManager::Manager().FindTexture(L"Sonic_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk2", ResManager::Manager().FindTexture(L"Sonic_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightwalk3", ResManager::Manager().FindTexture(L"Sonic_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk3", ResManager::Manager().FindTexture(L"Sonic_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	//속도0
	Anim->AddAnimation(L"walk_R1", ResManager::Manager().FindTexture(L"Sonic_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2", ResManager::Manager().FindTexture(L"Sonic_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3", ResManager::Manager().FindTexture(L"Sonic_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4", ResManager::Manager().FindTexture(L"Sonic_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5", ResManager::Manager().FindTexture(L"Sonic_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6", ResManager::Manager().FindTexture(L"Sonic_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7", ResManager::Manager().FindTexture(L"Sonic_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	//속도1
	Anim->AddAnimation(L"walk_R1_1", ResManager::Manager().FindTexture(L"Sonic_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2_1", ResManager::Manager().FindTexture(L"Sonic_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3_1", ResManager::Manager().FindTexture(L"Sonic_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4_1", ResManager::Manager().FindTexture(L"Sonic_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5_1", ResManager::Manager().FindTexture(L"Sonic_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6_1", ResManager::Manager().FindTexture(L"Sonic_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7_1", ResManager::Manager().FindTexture(L"Sonic_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	//속도2					 	   
	Anim->AddAnimation(L"walk_R1_2", ResManager::Manager().FindTexture(L"Sonic_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2_2", ResManager::Manager().FindTexture(L"Sonic_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3_2", ResManager::Manager().FindTexture(L"Sonic_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4_2", ResManager::Manager().FindTexture(L"Sonic_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5_2", ResManager::Manager().FindTexture(L"Sonic_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6_2", ResManager::Manager().FindTexture(L"Sonic_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7_2", ResManager::Manager().FindTexture(L"Sonic_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	//속도3					  		   
	Anim->AddAnimation(L"walk_R1_3", ResManager::Manager().FindTexture(L"Sonic_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2_3", ResManager::Manager().FindTexture(L"Sonic_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3_3", ResManager::Manager().FindTexture(L"Sonic_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4_3", ResManager::Manager().FindTexture(L"Sonic_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5_3", ResManager::Manager().FindTexture(L"Sonic_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6_3", ResManager::Manager().FindTexture(L"Sonic_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7_3", ResManager::Manager().FindTexture(L"Sonic_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	/////////////////////left
	//속도0

	Anim->AddAnimation(L"walk_L1", ResManager::Manager().FindTexture(L"Sonic_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2", ResManager::Manager().FindTexture(L"Sonic_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3", ResManager::Manager().FindTexture(L"Sonic_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4", ResManager::Manager().FindTexture(L"Sonic_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5", ResManager::Manager().FindTexture(L"Sonic_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6", ResManager::Manager().FindTexture(L"Sonic_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7", ResManager::Manager().FindTexture(L"Sonic_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	//속도1
	Anim->AddAnimation(L"walk_L1_1", ResManager::Manager().FindTexture(L"Sonic_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2_1", ResManager::Manager().FindTexture(L"Sonic_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3_1", ResManager::Manager().FindTexture(L"Sonic_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4_1", ResManager::Manager().FindTexture(L"Sonic_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5_1", ResManager::Manager().FindTexture(L"Sonic_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6_1", ResManager::Manager().FindTexture(L"Sonic_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7_1", ResManager::Manager().FindTexture(L"Sonic_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
																		
	//속도2													 			
	Anim->AddAnimation(L"walk_L1_2", ResManager::Manager().FindTexture(L"Sonic_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2_2", ResManager::Manager().FindTexture(L"Sonic_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3_2", ResManager::Manager().FindTexture(L"Sonic_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4_2", ResManager::Manager().FindTexture(L"Sonic_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5_2", ResManager::Manager().FindTexture(L"Sonic_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6_2", ResManager::Manager().FindTexture(L"Sonic_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7_2", ResManager::Manager().FindTexture(L"Sonic_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	//속도3													 			 
	Anim->AddAnimation(L"walk_L1_3", ResManager::Manager().FindTexture(L"Sonic_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2_3", ResManager::Manager().FindTexture(L"Sonic_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3_3", ResManager::Manager().FindTexture(L"Sonic_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4_3", ResManager::Manager().FindTexture(L"Sonic_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5_3", ResManager::Manager().FindTexture(L"Sonic_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6_3", ResManager::Manager().FindTexture(L"Sonic_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7_3", ResManager::Manager().FindTexture(L"Sonic_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	//RUN
	Anim->AddAnimation(L"rightrun1", ResManager::Manager().FindTexture(L"Sonic_RightRun"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun1", ResManager::Manager().FindTexture(L"Sonic_LeftRun"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);

	/////////////////////
	Anim->AddAnimation(L"rightrun_1", ResManager::Manager().FindTexture(L"Sonic_RightRun_1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_2", ResManager::Manager().FindTexture(L"Sonic_RightRun_2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_3", ResManager::Manager().FindTexture(L"Sonic_RightRun_3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_4", ResManager::Manager().FindTexture(L"Sonic_RightRun_4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_5", ResManager::Manager().FindTexture(L"Sonic_RightRun_5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_6", ResManager::Manager().FindTexture(L"Sonic_RightRun_6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_7", ResManager::Manager().FindTexture(L"Sonic_RightRun_7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);

	//////////////////////////////////////
	Anim->AddAnimation(L"leftrun_1", ResManager::Manager().FindTexture(L"Sonic_LeftRun_1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_2", ResManager::Manager().FindTexture(L"Sonic_LeftRun_2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_3", ResManager::Manager().FindTexture(L"Sonic_LeftRun_3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_4", ResManager::Manager().FindTexture(L"Sonic_LeftRun_4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_5", ResManager::Manager().FindTexture(L"Sonic_LeftRun_5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_6", ResManager::Manager().FindTexture(L"Sonic_LeftRun_6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_7", ResManager::Manager().FindTexture(L"Sonic_LeftRun_7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.025f, RGB(255, 0, 255), 0);

	//BREAK
	Anim->AddAnimation(L"rightbreak", ResManager::Manager().FindTexture(L"Sonic_RightBreak"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.1f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"leftbreak", ResManager::Manager().FindTexture(L"Sonic_LeftBreak"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.1f, RGB(255, 0, 255), 1);

	//CROUCH
	Anim->AddAnimation(L"rightcrouch", ResManager::Manager().FindTexture(L"Sonic_Right_Crouch"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.1f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"leftcrouch", ResManager::Manager().FindTexture(L"Sonic_Left_Crouch"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.1f, RGB(255, 0, 255), 1);

	//SPIN
	Anim->AddAnimation(L"rightspin", ResManager::Manager().FindTexture(L"Sonic_Right_Spin"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 6, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftspin", ResManager::Manager().FindTexture(L"Sonic_Left_Spin"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 6, 0.05f, RGB(255, 0, 255), 0);

	//ROLL
	Anim->AddAnimation(L"rightroll", ResManager::Manager().FindTexture(L"Sonic_Right_Roll"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftroll", ResManager::Manager().FindTexture(L"Sonic_Left_Roll"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);

	//PUSH
	Anim->AddAnimation(L"rightpush", ResManager::Manager().FindTexture(L"Sonic_Right_Push"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.4f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftpush", ResManager::Manager().FindTexture(L"Sonic_Left_Push"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.4f, RGB(255, 0, 255), 0);

	//SPRINGJUMP
	Anim->AddAnimation(L"SpringRjump", ResManager::Manager().FindTexture(L"Sonic_Right_SpringJump"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 11, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"SpringLjump", ResManager::Manager().FindTexture(L"Sonic_Left_SpringJump"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 11, 0.1f, RGB(255, 0, 255), 0);

	//LOOKUP
	Anim->AddAnimation(L"rightlookup", ResManager::Manager().FindTexture(L"Sonic_RightLookup"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftlookup", ResManager::Manager().FindTexture(L"Sonic_LeftLookup"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.2f, RGB(255, 0, 255), 0);

	//HITTED
	Anim->AddAnimation(L"righthit", ResManager::Manager().FindTexture(L"Sonic_RightHit"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.08f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"lefthit", ResManager::Manager().FindTexture(L"Sonic_LeftHit"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.08f, RGB(255, 0, 255), 1);

	//Victory
	Anim->AddAnimation(L"victory", ResManager::Manager().FindTexture(L"Sonic_Victory"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.2f, RGB(255, 0, 255), 1);


	Anim->PlayAnimation(L"rightidle1");

	////////////////////////////////////////////////
	///////////////////////////////////////////////
	//SUPER SONIC
	//IDLE
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Idle\\Idle_Right.bmp", L"SuperSonic_RightIdle");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Idle\\Idle_Left.bmp", L"SuperSonic_LeftIdle");

	//WALK
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Right_Walk.bmp", L"SuperSonic_RightWalk");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Left_Walk.bmp", L"SuperSonic_LeftWalk");


	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_1.bmp", L"SuperSonic_Walk_R1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_2.bmp", L"SuperSonic_Walk_R2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_3.bmp", L"SuperSonic_Walk_R3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_4.bmp", L"SuperSonic_Walk_R4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_5.bmp", L"SuperSonic_Walk_R5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_6.bmp", L"SuperSonic_Walk_R6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_7.bmp", L"SuperSonic_Walk_R7");


	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_1.bmp", L"SuperSonic_Walk_L1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_2.bmp", L"SuperSonic_Walk_L2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_3.bmp", L"SuperSonic_Walk_L3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_4.bmp", L"SuperSonic_Walk_L4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_5.bmp", L"SuperSonic_Walk_L5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_6.bmp", L"SuperSonic_Walk_L6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_7.bmp", L"SuperSonic_Walk_L7");


	//RUN
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\RightRun.bmp", L"SuperSonic_RightRun");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\LeftRun.bmp", L"SuperSonic_LeftRun");


	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_1.bmp", L"SuperSonic_RightRun_1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_2.bmp", L"SuperSonic_RightRun_2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_3.bmp", L"SuperSonic_RightRun_3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_4.bmp", L"SuperSonic_RightRun_4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_5.bmp", L"SuperSonic_RightRun_5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_6.bmp", L"SuperSonic_RightRun_6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_7.bmp", L"SuperSonic_RightRun_7");


	////////////////////////////////////
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_1.bmp", L"SuperSonic_LeftRun_1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_2.bmp", L"SuperSonic_LeftRun_2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_3.bmp", L"SuperSonic_LeftRun_3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_4.bmp", L"SuperSonic_LeftRun_4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_5.bmp", L"SuperSonic_LeftRun_5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_6.bmp", L"SuperSonic_LeftRun_6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_7.bmp", L"SuperSonic_LeftRun_7");


	//BREAK
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Break\\Right_Break.bmp", L"SuperSonic_RightBreak");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Break\\Left_Break.bmp", L"SuperSonic_LeftBreak");


	//CROUCH
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Crouch\\Right_Crouch.bmp", L"SuperSonic_Right_Crouch");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Crouch\\Left_Crouch.bmp", L"SuperSonic_Left_Crouch");

	//SPIN
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Spin\\Right_Spin.bmp", L"SuperSonic_Right_Spin");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Spin\\Left_Spin.bmp", L"SuperSonic_Left_Spin");

	//ROLL
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Roll\\Right_Roll.bmp", L"SuperSonic_Right_Roll");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Roll\\Left_Roll.bmp", L"SuperSonic_Left_Roll");

	//PUSH
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Push\\Right_Push.bmp", L"SuperSonic_Right_Push");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Push\\Left_Push.bmp", L"SuperSonic_Left_Push");

	//SPRING
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\SpringJump\\Right_Spring_Jump.bmp", L"SuperSonic_Right_SpringJump");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\SpringJump\\Left_Spring_Jump.bmp", L"SuperSonic_Left_SpringJump");

	//LOOKUP
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\LookUp\\Right_Lookup.bmp", L"SuperSonic_RightLookup");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\LookUp\\Left_Lookup.bmp", L"SuperSonic_LeftLookup");

	//HITTED
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Hitted\\RightHitted.bmp", L"SuperSonic_RightHit");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Hitted\\LeftHitted.bmp", L"SuperSonic_LeftHit");

	////////////////
	/////// 애니메이션 등록


	//idle right
	Anim->AddAnimation(L"Super_rightidle1", ResManager::Manager().FindTexture(L"SuperSonic_RightIdle"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.2f, RGB(255, 0, 255), 0);

	//idle left;
	Anim->AddAnimation(L"Super_leftidle1", ResManager::Manager().FindTexture(L"SuperSonic_LeftIdle"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 1000.f, RGB(255, 0, 255), 0);


	//WALK
	Anim->AddAnimation(L"Super_rightwalk", ResManager::Manager().FindTexture(L"SuperSonic_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftwalk", ResManager::Manager().FindTexture(L"SuperSonic_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"Super_rightwalk1", ResManager::Manager().FindTexture(L"SuperSonic_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftwalk1", ResManager::Manager().FindTexture(L"SuperSonic_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"Super_rightwalk2", ResManager::Manager().FindTexture(L"SuperSonic_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftwalk2", ResManager::Manager().FindTexture(L"SuperSonic_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"Super_rightwalk3", ResManager::Manager().FindTexture(L"SuperSonic_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftwalk3", ResManager::Manager().FindTexture(L"SuperSonic_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	//속도0
	Anim->AddAnimation(L"Super_walk_R1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R4", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R5", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R6", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R7", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	//속도1
	Anim->AddAnimation(L"Super_walk_R1_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R2_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R3_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R4_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R5_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R6_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R7_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	//속도2					 	   
	Anim->AddAnimation(L"Super_walk_R1_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R2_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R3_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R4_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R5_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R6_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R7_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	//속도3					  		   
	Anim->AddAnimation(L"Super_walk_R1_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R2_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R3_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R4_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R5_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R6_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_R7_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	/////////////////////left
	//속도0

	Anim->AddAnimation(L"Super_walk_L1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L4", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L5", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L6", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L7", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	//속도1
	Anim->AddAnimation(L"Super_walk_L1_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L2_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L3_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L4_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L5_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L6_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L7_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	//속도2													 			
	Anim->AddAnimation(L"Super_walk_L1_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L2_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L3_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L4_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L5_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L6_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L7_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	//속도3													 			 
	Anim->AddAnimation(L"Super_walk_L1_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L2_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L3_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L4_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L5_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L6_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_walk_L7_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	//RUN
	Anim->AddAnimation(L"Super_rightrun1", ResManager::Manager().FindTexture(L"SuperSonic_RightRun"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftrun1", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);

	/////////////////////
	Anim->AddAnimation(L"Super_rightrun_1", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_rightrun_2", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_rightrun_3", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_rightrun_4", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_rightrun_5", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_rightrun_6", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_rightrun_7", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);

	//////////////////////////////////////
	Anim->AddAnimation(L"Super_leftrun_1", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftrun_2", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftrun_3", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftrun_4", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftrun_5", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftrun_6", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftrun_7", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);

	//BREAK
	Anim->AddAnimation(L"Super_rightbreak", ResManager::Manager().FindTexture(L"SuperSonic_RightBreak"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.1f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"Super_leftbreak", ResManager::Manager().FindTexture(L"SuperSonic_LeftBreak"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.1f, RGB(255, 0, 255), 1);

	//CROUCH
	Anim->AddAnimation(L"Super_rightcrouch", ResManager::Manager().FindTexture(L"SuperSonic_Right_Crouch"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"Super_leftcrouch", ResManager::Manager().FindTexture(L"SuperSonic_Left_Crouch"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 1);

	//SPIN
	Anim->AddAnimation(L"Super_rightspin", ResManager::Manager().FindTexture(L"SuperSonic_Right_Spin"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 6, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftspin", ResManager::Manager().FindTexture(L"SuperSonic_Left_Spin"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 6, 0.05f, RGB(255, 0, 255), 0);

	//ROLL
	Anim->AddAnimation(L"Super_rightroll", ResManager::Manager().FindTexture(L"SuperSonic_Right_Roll"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 5, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftroll", ResManager::Manager().FindTexture(L"SuperSonic_Left_Roll"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 5, 0.05f, RGB(255, 0, 255), 0);

	//PUSH
	Anim->AddAnimation(L"Super_rightpush", ResManager::Manager().FindTexture(L"SuperSonic_Right_Push"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 3, 0.4f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftpush", ResManager::Manager().FindTexture(L"SuperSonic_Left_Push"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 3, 0.4f, RGB(255, 0, 255), 0);

	//SPRINGJUMP
	Anim->AddAnimation(L"Super_SpringRjump", ResManager::Manager().FindTexture(L"SuperSonic_Right_SpringJump"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 11, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_SpringLjump", ResManager::Manager().FindTexture(L"SuperSonic_Left_SpringJump"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 11, 0.1f, RGB(255, 0, 255), 0);

	//LOOKUP
	Anim->AddAnimation(L"Super_rightlookup", ResManager::Manager().FindTexture(L"SuperSonic_RightLookup"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Super_leftlookup", ResManager::Manager().FindTexture(L"SuperSonic_LeftLookup"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.2f, RGB(255, 0, 255), 0);

	//HITTED
	Anim->AddAnimation(L"Super_righthit", ResManager::Manager().FindTexture(L"SuperSonic_RightHit"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.08f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"Super_lefthit", ResManager::Manager().FindTexture(L"SuperSonic_LeftHit"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.08f, RGB(255, 0, 255), 1);


	////////////////////////
	//SUPERSONIC_WHITE

	//IDLE
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Idle\\Idle_Right_White.bmp", L"SuperSonic_RightIdle_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Idle\\Idle_Left_White.bmp", L"SuperSonic_LeftIdle_White");

	//WALK
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Right_Walk_White.bmp", L"SuperSonic_RightWalk_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Left_Walk_White.bmp", L"SuperSonic_LeftWalk_White");


	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_1_White.bmp", L"SuperSonic_Walk_R1_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_2_White.bmp", L"SuperSonic_Walk_R2_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_3_White.bmp", L"SuperSonic_Walk_R3_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_4_White.bmp", L"SuperSonic_Walk_R4_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_5_White.bmp", L"SuperSonic_Walk_R5_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_6_White.bmp", L"SuperSonic_Walk_R6_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Right\\Walk_7_White.bmp", L"SuperSonic_Walk_R7_White");


	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_1_White.bmp", L"SuperSonic_Walk_L1_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_2_White.bmp", L"SuperSonic_Walk_L2_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_3_White.bmp", L"SuperSonic_Walk_L3_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_4_White.bmp", L"SuperSonic_Walk_L4_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_5_White.bmp", L"SuperSonic_Walk_L5_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_6_White.bmp", L"SuperSonic_Walk_L6_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Walk\\Left\\Walk_7_White.bmp", L"SuperSonic_Walk_L7_White");


	//RUN
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\RightRun_White.bmp", L"SuperSonic_RightRun_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\LeftRun_White.bmp", L"SuperSonic_LeftRun_White");


	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_1_White.bmp", L"SuperSonic_RightRun_1_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_2_White.bmp", L"SuperSonic_RightRun_2_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_3_White.bmp", L"SuperSonic_RightRun_3_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_4_White.bmp", L"SuperSonic_RightRun_4_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_5_White.bmp", L"SuperSonic_RightRun_5_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_6_White.bmp", L"SuperSonic_RightRun_6_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Right\\Run_7_White.bmp", L"SuperSonic_RightRun_7_White");


	////////////////////////////////////
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_1_White.bmp", L"SuperSonic_LeftRun_1_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_2_White.bmp", L"SuperSonic_LeftRun_2_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_3_White.bmp", L"SuperSonic_LeftRun_3_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_4_White.bmp", L"SuperSonic_LeftRun_4_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_5_White.bmp", L"SuperSonic_LeftRun_5_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_6_White.bmp", L"SuperSonic_LeftRun_6_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Run\\Left\\Run_7_White.bmp", L"SuperSonic_LeftRun_7_White");


	//BREAK
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Break\\Right_Break_White.bmp", L"SuperSonic_RightBreak_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Break\\Left_Break_White.bmp", L"SuperSonic_LeftBreak_White");


	//CROUCH
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Crouch\\Right_Crouch_White.bmp", L"SuperSonic_Right_Crouch_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Crouch\\Left_Crouch_White.bmp", L"SuperSonic_Left_Crouch_White");

	//SPIN
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Spin\\Right_Spin_White.bmp", L"SuperSonic_Right_Spin_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Spin\\Left_Spin_White.bmp", L"SuperSonic_Left_Spin_White");

	//ROLL
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Roll\\Right_Roll_White.bmp", L"SuperSonic_Right_Roll_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Roll\\Left_Roll_White.bmp", L"SuperSonic_Left_Roll_White");

	//PUSH
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Push\\Right_Push_White.bmp", L"SuperSonic_Right_Push_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Push\\Left_Push_White.bmp", L"SuperSonic_Left_Push_White");

	//SPRING
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\SpringJump\\Right_Spring_Jump_White.bmp", L"SuperSonic_Right_SpringJump_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\SpringJump\\Left_Spring_Jump_White.bmp", L"SuperSonic_Left_SpringJump_White");

	//LOOKUP
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\LookUp\\Right_Lookup_White.bmp", L"SuperSonic_RightLookup_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\LookUp\\Left_Lookup_White.bmp", L"SuperSonic_LeftLookup_White");

	//HITTED
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Hitted\\RightHitted_White.bmp", L"SuperSonic_RightHit_White");
	ResManager::Manager().LoadTexture(L"\\Charactor\\SuperSonic\\Hitted\\LeftHitted_White.bmp", L"SuperSonic_LeftHit_White");


	m_WhiteAnim = new Animator;

	//idle right
	m_WhiteAnim->AddAnimation(L"Super_rightidle1", ResManager::Manager().FindTexture(L"SuperSonic_RightIdle_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.2f, RGB(255, 0, 255), 0);

	//idle left;
	m_WhiteAnim->AddAnimation(L"Super_leftidle1", ResManager::Manager().FindTexture(L"SuperSonic_LeftIdle_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 1000.f, RGB(255, 0, 255), 0);


	//WALK
	m_WhiteAnim->AddAnimation(L"Super_rightwalk", ResManager::Manager().FindTexture(L"SuperSonic_RightWalk_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftwalk", ResManager::Manager().FindTexture(L"SuperSonic_LeftWalk_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	m_WhiteAnim->AddAnimation(L"Super_rightwalk1", ResManager::Manager().FindTexture(L"SuperSonic_RightWalk_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftwalk1", ResManager::Manager().FindTexture(L"SuperSonic_LeftWalk_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	m_WhiteAnim->AddAnimation(L"Super_rightwalk2", ResManager::Manager().FindTexture(L"SuperSonic_RightWalk_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftwalk2", ResManager::Manager().FindTexture(L"SuperSonic_LeftWalk_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	m_WhiteAnim->AddAnimation(L"Super_rightwalk3", ResManager::Manager().FindTexture(L"SuperSonic_RightWalk_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftwalk3", ResManager::Manager().FindTexture(L"SuperSonic_LeftWalk_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	//속도0
	m_WhiteAnim->AddAnimation(L"Super_walk_R1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R1_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R2_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R3_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R4", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R4_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R5", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R5_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R6", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R6_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R7", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R7_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	//속도1
	m_WhiteAnim->AddAnimation(L"Super_walk_R1_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R1_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R2_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R2_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R3_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R3_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R4_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R4_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R5_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R5_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R6_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R6_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R7_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R7_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	//속도2					 	   
	m_WhiteAnim->AddAnimation(L"Super_walk_R1_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R1_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R2_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R2_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R3_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R3_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R4_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R4_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R5_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R5_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R6_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R6_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R7_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R7_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	//속도3					  		   
	m_WhiteAnim->AddAnimation(L"Super_walk_R1_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R1_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R2_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R2_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R3_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R3_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R4_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R4_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R5_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R5_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R6_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R6_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_R7_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_R7_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	/////////////////////left
	//속도0

	m_WhiteAnim->AddAnimation(L"Super_walk_L1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L1_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L2_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L3_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L4", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L4_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L5", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L5_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L6", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L6_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L7", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L7_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	//속도1
	m_WhiteAnim->AddAnimation(L"Super_walk_L1_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L1_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L2_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L2_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L3_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L3_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L4_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L4_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L5_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L5_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L6_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L6_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L7_1", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L7_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	//속도2													 			
	m_WhiteAnim->AddAnimation(L"Super_walk_L1_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L1_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L2_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L2_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L3_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L3_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L4_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L4_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L5_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L5_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L6_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L6_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L7_2", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L7_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	//속도3													 			 
	m_WhiteAnim->AddAnimation(L"Super_walk_L1_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L1_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L2_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L2_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L3_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L3_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L4_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L4_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L5_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L5_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L6_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L6_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_walk_L7_3", ResManager::Manager().FindTexture(L"SuperSonic_Walk_L7_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	//RUN
	m_WhiteAnim->AddAnimation(L"Super_rightrun1", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftrun1", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);

	/////////////////////
	m_WhiteAnim->AddAnimation(L"Super_rightrun_1", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_1_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_rightrun_2", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_2_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_rightrun_3", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_3_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_rightrun_4", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_4_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_rightrun_5", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_5_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_rightrun_6", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_6_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_rightrun_7", ResManager::Manager().FindTexture(L"SuperSonic_RightRun_7_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);

	//////////////////////////////////////
	m_WhiteAnim->AddAnimation(L"Super_leftrun_1", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_1_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftrun_2", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_2_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftrun_3", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_3_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftrun_4", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_4_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftrun_5", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_5_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftrun_6", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_6_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftrun_7", ResManager::Manager().FindTexture(L"SuperSonic_LeftRun_7_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.025f, RGB(255, 0, 255), 0);

	//BREAK
	m_WhiteAnim->AddAnimation(L"Super_rightbreak", ResManager::Manager().FindTexture(L"SuperSonic_RightBreak_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.1f, RGB(255, 0, 255), 1);
	m_WhiteAnim->AddAnimation(L"Super_leftbreak", ResManager::Manager().FindTexture(L"SuperSonic_LeftBreak_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.1f, RGB(255, 0, 255), 1);

	//CROUCH
	m_WhiteAnim->AddAnimation(L"Super_rightcrouch", ResManager::Manager().FindTexture(L"SuperSonic_Right_Crouch_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 1);
	m_WhiteAnim->AddAnimation(L"Super_leftcrouch", ResManager::Manager().FindTexture(L"SuperSonic_Left_Crouch_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 1);

	//SPIN
	m_WhiteAnim->AddAnimation(L"Super_rightspin", ResManager::Manager().FindTexture(L"SuperSonic_Right_Spin_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 6, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftspin", ResManager::Manager().FindTexture(L"SuperSonic_Left_Spin_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 6, 0.05f, RGB(255, 0, 255), 0);

	//ROLL
	m_WhiteAnim->AddAnimation(L"Super_rightroll", ResManager::Manager().FindTexture(L"SuperSonic_Right_Roll_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 5, 0.05f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftroll", ResManager::Manager().FindTexture(L"SuperSonic_Left_Roll_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 5, 0.05f, RGB(255, 0, 255), 0);

	//PUSH
	m_WhiteAnim->AddAnimation(L"Super_rightpush", ResManager::Manager().FindTexture(L"SuperSonic_Right_Push_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 3, 0.4f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftpush", ResManager::Manager().FindTexture(L"SuperSonic_Left_Push_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 3, 0.4f, RGB(255, 0, 255), 0);

	//SPRINGJUMP
	m_WhiteAnim->AddAnimation(L"Super_SpringRjump", ResManager::Manager().FindTexture(L"SuperSonic_Right_SpringJump_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 11, 0.1f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_SpringLjump", ResManager::Manager().FindTexture(L"SuperSonic_Left_SpringJump_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 11, 0.1f, RGB(255, 0, 255), 0);

	//LOOKUP
	m_WhiteAnim->AddAnimation(L"Super_rightlookup", ResManager::Manager().FindTexture(L"SuperSonic_RightLookup_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.2f, RGB(255, 0, 255), 0);
	m_WhiteAnim->AddAnimation(L"Super_leftlookup", ResManager::Manager().FindTexture(L"SuperSonic_LeftLookup_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.2f, RGB(255, 0, 255), 0);

	//HITTED
	m_WhiteAnim->AddAnimation(L"Super_righthit", ResManager::Manager().FindTexture(L"SuperSonic_RightHit_White"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.08f, RGB(255, 0, 255), 1);
	m_WhiteAnim->AddAnimation(L"Super_lefthit", ResManager::Manager().FindTexture(L"SuperSonic_LeftHit_White"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.08f, RGB(255, 0, 255), 1);


	//Victory
	m_WhiteAnim->AddAnimation(L"victory", ResManager::Manager().FindTexture(L"Sonic_Victory"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.2f, RGB(255, 0, 255), 1);

}

void Sonic::RendAfterImage(HDC _dc)
{
	//Anim->render(_dc, m_ptOldPos_15);

	Anim->render(_dc, m_ptOldPos_11);

	Anim->render(_dc, m_ptOldPos_07);

	Anim->render(_dc, m_ptOldPos_03);
}

void Sonic::CheckSuperSonicTime()
{
	m_fSuperSonicTime += DT;

	if (m_fSuperSonicTime >= 1)
	{
		if(m_iRingCnt >=1)
			m_iRingCnt -= 1;
		
		m_fSuperSonicTime = 0.f;
	}

	if (m_iRingCnt <= 0 && StageManager::Manager().GetCurStageType() != STAGE_FINAL)
	{
		m_bSuperSonic = false;

		if (StageManager::Manager().GetCurStageType() == STAGE_START)
		{
			SoundManager::Manager()->PlayBGM(L"BGM_STAGE_START");
		}
		else if (StageManager::Manager().GetCurStageType() == STAGE_START)
		{
			SoundManager::Manager()->PlayBGM(L"BGM_STAGE_00");
		}
	}
}

void Sonic::Player_Jump()
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
		//m_ptGravity.y = 0;
		if (m_eShield == SHIELD_FIRE)
		{
			((FireShield_Back*)(StageManager::Manager().GetCurStage()->GetListObj(OBJ_FIRE)[0]))->SetRendOn(false);
			if (m_bDir == DIR_RIGHT)
			{
				((FireShield*)(StageManager::Manager().GetCurStage()->GetListObj(OBJ_SHIELD)[0]))->PlayAnimation(L"Fire_Effect");
				SoundManager::Manager()->PlaySoundW(L"Sound_Fire", false);
			}
			else if (m_bDir == DIR_LEFT)
			{
				((FireShield*)(StageManager::Manager().GetCurStage()->GetListObj(OBJ_SHIELD)[0]))->PlayAnimation(L"Fire_Effect_Left");
				SoundManager::Manager()->PlaySoundW(L"Sound_Fire", false);
			}

			state = PLAYER_FIRESKILL;
			m_ptGravity.y = 0;
		}

		else if (m_eShield == SHIELD_WATER)
		{
			((WaterShield*)(StageManager::Manager().GetCurStage()->GetListObj(OBJ_SHIELD)[0]))->PlayAnimation(L"Water_Effect");
			
			state = PLAYER_WATERSKILL;
			m_ptGravity.y = 1000;

			SoundManager::Manager()->StopSound(L"Sound_Water");
			SoundManager::Manager()->PlaySoundW(L"Sound_Water", false);
		}

		else if (m_eShield == SHIELD_END && m_bSuperSonic == false && m_iRingCnt >= 30)
		{
			SoundManager::Manager()->PlayBGM(L"BGM_SuperSonic");
			state = PLAYER_TRANSFORM;
			m_Animation = ANI_TRANSFORM;
			return;
		}

		if (m_bSuperSonic == true)
		{
			if(m_bDir == DIR_RIGHT)
				m_fSpeed = 2000;

			else if (m_bDir == DIR_LEFT)
			{
				m_fSpeed = -2000;
			}
		}
	}

	if (m_bOnGround == true)
	{
		m_fSpeed = m_ptJumpGradient.x * m_fJumpSpeed + m_ptGradient.x * m_fSpeed;
		m_fJumpSpeed = 0;

		state = PLAYER_STOP;

		return;
	}

}

void Sonic::Player_TransForm()
{
	if (true == Anim->GetCurAnimation()->isFin())
	{
		state = PLAYER_STOP;
		m_Animation = ANI_STOP;
		m_bSuperSonic = true;
	}
}

void Sonic::Player_FinalStage()
{
	if (m_bPause == true)
	{
		return;
	}

	if (m_Animation != ANI_HITTED && m_bSuperDashOn == false)
	{
		if (true == KeyManager::Manager().GetKeyState(KEY_RIGHT, STATE_HOLD))
		{
			pos.x += (m_fSpeed / 3) * 2 * DT;
		}

		if (true == KeyManager::Manager().GetKeyState(KEY_LEFT, STATE_HOLD))
		{
			pos.x -= m_fSpeed * DT;
		}
		if (true == KeyManager::Manager().GetKeyState(KEY_UP, STATE_HOLD))
		{
			pos.y -= m_fSpeed * DT;
		}
		if (true == KeyManager::Manager().GetKeyState(KEY_DOWN, STATE_HOLD))
		{
			pos.y += m_fSpeed * DT;
		}
		
		if (KeyManager::Manager().GetKeyState(KEY_SPACE, STATE_TAB))
		{
			m_fSpeed = 1500;
			m_bSuperDashOn = true;
			m_Animation = ANI_ROLL;
		}
	}
	

	else if (m_Animation == ANI_HITTED)
	{
		m_fSuperDashTime = 0.f;
		m_bSuperDashOn = false;
		pos.x -= 1200 * DT;

		m_fSpeed = 900.f;

		m_fSuperHittedTime += DT;

		if (m_fSuperHittedTime >= 1)
		{
			m_Animation = ANI_FINALSTAGE;
			m_fSuperHittedTime = 0.f;
		}
	}

	if (m_bSuperDashOn == true)
	{
		m_fSuperDashTime += 3*DT;

		pos.x += m_fSpeed * DT;

		if (m_fSuperDashTime >= 1)
		{
			m_bSuperDashOn = false;
			m_fSpeed = 900;
			m_Animation = ANI_FINALSTAGE;
			m_fSuperDashTime = 0.f;
			
		}
	}

	if (pos.y <= 100)
	{
		pos.y = 100;
	}

	if (pos.y >= 4400)
	{
		pos.y = 4400;
	}
	
	if (pos.x >= 2500)
	{
		pos.x = 2500;
	}
}

void Sonic::SwitchAnimation()
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
			Anim->PlayAnimation(L"rightcrouch", 0);
		else
			Anim->PlayAnimation(L"leftcrouch", 0);

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

	case ANI_VICTORY:
		Anim->PlayAnimation(L"victory");
		break;

	case ANI_TRANSFORM:
		Anim->PlayAnimation(L"TransForm");
		break;

	case ANI_END:
		break;
	default:
		break;
	}
}

void Sonic::SwitchSuperAnimation()
{
	switch (m_Animation)
	{
	case ANI_STOP:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"Super_rightidle1");
			m_WhiteAnim->PlayAnimation(L"Super_rightidle1");
		}
		else
		{
			Anim->PlayAnimation(L"Super_leftidle1");
			m_WhiteAnim->PlayAnimation(L"Super_leftidle1");
		}
		break;
	case ANI_iDLE:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"Super_rightidle2");
			m_WhiteAnim->PlayAnimation(L"Super_rightidle2");
		}
		else
		{
			Anim->PlayAnimation(L"Super_leftidle2");
			m_WhiteAnim->PlayAnimation(L"Super_leftidle2");
		}
		break;
	case ANI_ROLL:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"Super_rightroll");
			m_WhiteAnim->PlayAnimation(L"Super_rightroll");

		}	
		else
		{
			Anim->PlayAnimation(L"Super_leftroll");
			m_WhiteAnim->PlayAnimation(L"Super_leftroll");
		}
		break;

	case ANI_JUMP:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"Super_rightroll");
			m_WhiteAnim->PlayAnimation(L"Super_rightroll");
		}
			
		else
		{
			Anim->PlayAnimation(L"Super_leftroll");
			m_WhiteAnim->PlayAnimation(L"Super_leftroll");
		}
			
		break;

	case ANI_CROUCH:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"Super_rightcrouch");
			m_WhiteAnim->PlayAnimation(L"Super_rightcrouch");
		}
			
		else
		{
			Anim->PlayAnimation(L"Super_leftcrouch");
			m_WhiteAnim->PlayAnimation(L"Super_leftcrouch");
		}
			
		break;
	case ANI_SIT:
		if (m_eOldAnimation == ANI_SIT)
			break;

		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"Super_rightcrouch", 0);
			m_WhiteAnim->PlayAnimation(L"Super_rightcrouch", 0);
		}
			
		else
		{
			Anim->PlayAnimation(L"Super_leftcrouch", 0);
			m_WhiteAnim->PlayAnimation(L"Super_leftcrouch", 0);
		}

		break;
	case ANI_LOOKUP:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"Super_rightlookup");
			m_WhiteAnim->PlayAnimation(L"Super_rightlookup");
		}
			
		else
		{
			Anim->PlayAnimation(L"Super_leftlookup");
			m_WhiteAnim->PlayAnimation(L"Super_leftlookup");
		}
			
		break;

	case ANI_WALK:
		if (m_bDir == DIR_RIGHT)
		{
			if (m_fSpeed < 200 && m_fSpeed > -200)
			{
				if (m_ptGradient.x >= 0.8f)
				{
					Anim->PlayAnimation(L"Super_rightwalk");
					m_WhiteAnim->PlayAnimation(L"Super_rightwalk");

				}

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R1");
				}
					

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R2");

				}

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R3");

				}

				else if (m_ptGradient.x <= -0.8f)
				{
					Anim->PlayAnimation(L"Super_walk_R4");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R4");

				}

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R5");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R5");

				}

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R6");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R6");

				}

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R7");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R7");

				}
			}
			else if ((m_fSpeed >= 200 && m_fSpeed < 300) || (m_fSpeed <-200 && m_fSpeed >= -300))
			{
				if (m_ptGradient.x >= 0.8f)
				{
					Anim->PlayAnimation(L"Super_rightwalk1");
					m_WhiteAnim->PlayAnimation(L"Super_rightwalk1");

				}

				else if (m_ptGradient.x > 0.3 && m_ptGradient.x <= 0.8 && m_ptGradient.y > 0)
				{
					Anim->PlayAnimation(L"Super_walk_R1_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R1_1");

				}

				else if (m_ptGradient.x > -0.3 && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0)
				{
					Anim->PlayAnimation(L"Super_walk_R2_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R2_1");

				}

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R3_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R3_1");

				}

				else if (m_ptGradient.x <= -0.8f)
				{
					Anim->PlayAnimation(L"Super_walk_R4_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R4_1");

				}

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R5_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R5_1");

				}

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R6_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R6_1");

				}

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R7_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R7_1");

				}
			}

			else if ((m_fSpeed >= 300 && m_fSpeed < 400) || (m_fSpeed <-300 && m_fSpeed >= -400))
			{
				if (m_ptGradient.x >= 0.8f)
				{
					Anim->PlayAnimation(L"Super_rightwalk2");
					m_WhiteAnim->PlayAnimation(L"Super_rightwalk2");

				}

				else if (m_ptGradient.x > 0.3 && m_ptGradient.x <= 0.8 && m_ptGradient.y > 0)
				{
					Anim->PlayAnimation(L"Super_walk_R1_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R1_2");

				}

				else if (m_ptGradient.x > -0.3 && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0)
				{
					Anim->PlayAnimation(L"Super_walk_R2_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R2_2");

				}

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R3_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R3_2");

				}

				else if (m_ptGradient.x <= -0.8f)
				{
					Anim->PlayAnimation(L"Super_walk_R4_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R4_2");

				}

				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R5_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R5_2");

				}

				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R6_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R6_2");

				}

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R7_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R7_2");

				}
			}

			else if ((m_fSpeed >= 400 && m_fSpeed < ChangeWtoR) || (m_fSpeed < -400 && m_fSpeed > -ChangeWtoR))
			{
				if (m_ptGradient.x >= 0.8f)
				{
					Anim->PlayAnimation(L"Super_rightwalk3");
					m_WhiteAnim->PlayAnimation(L"Super_rightwalk3");

				}

				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R1_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R1_3");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R2_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R2_3");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R3_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R3_3");

				}

				else if (m_ptGradient.x <= -0.8f)
				{
					Anim->PlayAnimation(L"Super_walk_R4_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R4_3");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R5_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R5_3");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R6_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R6_3");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_R7_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_R7_3");

				}
			}

			else if (m_fSpeed >= ChangeWtoR || m_fSpeed <= -ChangeWtoR)
			{
				if (m_ptGradient.x >= 0.8f)
				{
					Anim->PlayAnimation(L"Super_rightrun1");
					m_WhiteAnim->PlayAnimation(L"Super_rightrun1");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_rightrun_1");
					m_WhiteAnim->PlayAnimation(L"Super_rightrun_1");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_rightrun_2");
					m_WhiteAnim->PlayAnimation(L"Super_rightrun_2");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_rightrun_3");
					m_WhiteAnim->PlayAnimation(L"Super_rightrun_3");

				}
				else if (m_ptGradient.x <= -0.8f)
				{
					Anim->PlayAnimation(L"Super_rightrun_4");
					m_WhiteAnim->PlayAnimation(L"Super_rightrun_4");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_rightrun_5");
					m_WhiteAnim->PlayAnimation(L"Super_rightrun_5");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_rightrun_6");
					m_WhiteAnim->PlayAnimation(L"Super_rightrun_6");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_rightrun_7");
					m_WhiteAnim->PlayAnimation(L"Super_rightrun_7");

				}
			}
			break;
		}

		else if (m_bDir != DIR_RIGHT)
		{
			if (m_fSpeed < 200 && m_fSpeed > -200)
			{
				if (m_ptGradient.x >= 0.8f)
				{
					Anim->PlayAnimation(L"Super_leftwalk");
					m_WhiteAnim->PlayAnimation(L"Super_leftwalk");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L7");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L7");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L6");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L6");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L5");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L5");

				}
				else if (m_ptGradient.x <= -0.8f)
				{
					Anim->PlayAnimation(L"Super_walk_L4");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L4");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L3");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L2");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L1");

				}
			}
			else if ((m_fSpeed >= 200 && m_fSpeed < 300) || (m_fSpeed <-200 && m_fSpeed >= -300))
			{
				if (m_ptGradient.x >= 0.8f)
				{
					Anim->PlayAnimation(L"Super_leftwalk1");
					m_WhiteAnim->PlayAnimation(L"Super_leftwalk1");

				}
				else if (m_ptGradient.x > 0.3 && m_ptGradient.x <= 0.8 && m_ptGradient.y > 0)
				{
					Anim->PlayAnimation(L"Super_walk_L7_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L7_1");

				}
				else if (m_ptGradient.x > -0.3 && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0)
				{
					Anim->PlayAnimation(L"Super_walk_L6_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L6_1");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L5_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L5_1");

				}
				else if (m_ptGradient.x <= -0.8f)
				{
					Anim->PlayAnimation(L"Super_walk_L4_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L4_1");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L3_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L3_1");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L2_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L2_1");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L1_1");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L1_1");

				}
			}

			else if ((m_fSpeed >= 300 && m_fSpeed < 400) || (m_fSpeed <-300 && m_fSpeed >= -400))
			{
				if (m_ptGradient.x >= 0.8f)
				{
					Anim->PlayAnimation(L"Super_leftwalk2");
					m_WhiteAnim->PlayAnimation(L"Super_leftwalk2");

				}
				else if (m_ptGradient.x > 0.3 && m_ptGradient.x <= 0.8 && m_ptGradient.y > 0)
				{
					Anim->PlayAnimation(L"Super_walk_L7_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L7_2");

				}
				else if (m_ptGradient.x > -0.3 && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0)
				{
					Anim->PlayAnimation(L"Super_walk_L6_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L6_2");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L5_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L5_2");

				}
				else if (m_ptGradient.x <= -0.8f)
				{
					Anim->PlayAnimation(L"Super_walk_L4_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L4_2");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L3_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L3_2");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L2_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L2_2");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L1_2");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L1_2");

				}
			}

			else if ((m_fSpeed >= 400 && m_fSpeed < ChangeWtoR) || (m_fSpeed < -400 && m_fSpeed > -ChangeWtoR))
			{
				if (m_ptGradient.x >= 0.8f)
				{
					Anim->PlayAnimation(L"Super_leftwalk3");
					m_WhiteAnim->PlayAnimation(L"Super_leftwalk3");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L7_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L7_3");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L6_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L6_3");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L5_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L5_3");

				}
				else if (m_ptGradient.x <= -0.8f)
				{
					Anim->PlayAnimation(L"Super_walk_L4_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L4_3");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L3_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L3_3");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L2_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L2_3");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_walk_L1_3");
					m_WhiteAnim->PlayAnimation(L"Super_walk_L1_3");

				}
			}
			else if (m_fSpeed >= ChangeWtoR || m_fSpeed <= -ChangeWtoR)
			{
				if (m_ptGradient.x >= 0.8f)
				{
					Anim->PlayAnimation(L"Super_leftrun1");
					m_WhiteAnim->PlayAnimation(L"Super_leftrun1");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_leftrun_7");
					m_WhiteAnim->PlayAnimation(L"Super_leftrun_7");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_leftrun_6");
					m_WhiteAnim->PlayAnimation(L"Super_leftrun_6");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
				{
					Anim->PlayAnimation(L"Super_leftrun_5");
					m_WhiteAnim->PlayAnimation(L"Super_leftrun_5");

				}
				else if (m_ptGradient.x <= -0.8f)
				{
					Anim->PlayAnimation(L"Super_leftrun_4");
					m_WhiteAnim->PlayAnimation(L"Super_leftrun_4");

				}
				else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_leftrun_3");
					m_WhiteAnim->PlayAnimation(L"Super_leftrun_3");

				}
				else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_leftrun_2");
					m_WhiteAnim->PlayAnimation(L"Super_leftrun_2");

				}
				else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
				{
					Anim->PlayAnimation(L"Super_leftrun_1");
					m_WhiteAnim->PlayAnimation(L"Super_leftrun_1");

				}
			}
			break;
		}


	case ANI_BREAK:
		if (m_eOldAnimation != ANI_BREAK)
		{
			if (m_bDir == DIR_RIGHT)
			{
				Anim->PlayAnimation(L"Super_rightbreak", 0);
				m_WhiteAnim->PlayAnimation(L"Super_rightbreak", 0);

			}
			else
			{
				Anim->PlayAnimation(L"Super_leftbreak", 0);
				m_WhiteAnim->PlayAnimation(L"Super_leftbreak", 0);

			}
		}
		break;

	case ANI_SPIN:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"Super_rightspin");
			m_WhiteAnim->PlayAnimation(L"Super_rightspin");

		}
		else
		{
			Anim->PlayAnimation(L"Super_leftspin");
			m_WhiteAnim->PlayAnimation(L"Super_leftspin");

		}
		break;

	case ANI_PUSH:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"Super_rightpush");
			m_WhiteAnim->PlayAnimation(L"Super_rightpush");

		}
		else
		{
			Anim->PlayAnimation(L"Super_leftpush");
			m_WhiteAnim->PlayAnimation(L"Super_leftpush");

		}
		break;

	case ANI_SPRINGJUMP:
		if (m_bDir == DIR_RIGHT)
		{
			Anim->PlayAnimation(L"Super_SpringRjump");
			m_WhiteAnim->PlayAnimation(L"Super_SpringRjump");
		}

		else
		{
			Anim->PlayAnimation(L"Super_SpringLjump");
			m_WhiteAnim->PlayAnimation(L"Super_SpringLjump");

		}
		break;

	case ANI_HITTED:
		if (m_eOldAnimation != ANI_HITTED)
		{
			if (m_bDir == DIR_RIGHT)
			{
				Anim->PlayAnimation(L"Super_righthit", 0);
				m_WhiteAnim->PlayAnimation(L"Super_righthit", 0);

			}

			else if (m_bDir == DIR_LEFT)
			{
				Anim->PlayAnimation(L"Super_lefthit", 0);
				m_WhiteAnim->PlayAnimation(L"Super_lefthit", 0);

			}
		}
		break;

	case ANI_VICTORY:
		Anim->PlayAnimation(L"victory");
		m_WhiteAnim->PlayAnimation(L"victory");
		break;

	case ANI_FINALSTAGE:
		Anim->PlayAnimation(L"Super_rightrun1");
		m_WhiteAnim->PlayAnimation(L"Super_rightrun1");
		break;

	case ANI_END:
		break;
	default:
		break;
	}
}

void Sonic::SetOldPos()
{
	/*m_ptOldPos_15 = m_ptOldPos_14;
	m_ptOldPos_14 = m_ptOldPos_13;
	m_ptOldPos_13 = m_ptOldPos_12;
	m_ptOldPos_12 = m_ptOldPos_11;*/
	m_ptOldPos_11 = m_ptOldPos_10;
	m_ptOldPos_10 = m_ptOldPos_09;
	m_ptOldPos_09 = m_ptOldPos_08;
	m_ptOldPos_08 = m_ptOldPos_07;
	m_ptOldPos_07 = m_ptOldPos_06;
	m_ptOldPos_06 = m_ptOldPos_05;
	m_ptOldPos_05 = m_ptOldPos_04;
	m_ptOldPos_04 = m_ptOldPos_03;
	m_ptOldPos_03 = m_ptOldPos_02;
	m_ptOldPos_02 = m_ptOldPos_01;
	m_ptOldPos_01 = m_ptOldPos;
	m_ptOldPos = pos;
}

