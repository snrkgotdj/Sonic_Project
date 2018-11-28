#include "stdafx.h"
#include "Knuckle.h"
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

Knuckle::Knuckle()
{
}


Knuckle::~Knuckle()
{
}



void Knuckle::render(HDC _dc)
{
	Player::render(_dc);
}

void Knuckle::update()
{
	Player::update();
}

void Knuckle::init(fPOINT _pos, STAGE_TYPE _type)
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

	////idle
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Idle\\RightIdle.bmp", L"Knuckle_RightIdle");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Idle\\LeftIdle.bmp", L"Knuckle_LeftIdle");
	//TLeftStand = ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Stand\\LeftStand.bmp", L"Knuckle_LeftStand");

	//RUN
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Right\\RightRun.bmp", L"Knuckle_RightRun");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Left\\LeftRun.bmp", L"Knuckle_LeftRun");

	/////////////////////////////////////
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Right\\Run_1.bmp", L"Knuckle_RightRun_1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Right\\Run_2.bmp", L"Knuckle_RightRun_2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Right\\Run_3.bmp", L"Knuckle_RightRun_3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Right\\Run_4.bmp", L"Knuckle_RightRun_4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Right\\Run_5.bmp", L"Knuckle_RightRun_5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Right\\Run_6.bmp", L"Knuckle_RightRun_6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Right\\Run_7.bmp", L"Knuckle_RightRun_7");


	////////////////////////////////////
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Left\\Run_1.bmp", L"Knuckle_LeftRun_1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Left\\Run_2.bmp", L"Knuckle_LeftRun_2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Left\\Run_3.bmp", L"Knuckle_LeftRun_3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Left\\Run_4.bmp", L"Knuckle_LeftRun_4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Left\\Run_5.bmp", L"Knuckle_LeftRun_5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Left\\Run_6.bmp", L"Knuckle_LeftRun_6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Run\\Left\\Run_7.bmp", L"Knuckle_LeftRun_7");


	//Walk
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Left\\LeftWalk.bmp", L"Knuckle_LeftWalk");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Right\\RightWalk.bmp", L"Knuckle_RightWalk");

	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Right\\Walk_1.bmp", L"Knuckle_Walk_R1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Right\\Walk_2.bmp", L"Knuckle_Walk_R2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Right\\Walk_3.bmp", L"Knuckle_Walk_R3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Right\\Walk_4.bmp", L"Knuckle_Walk_R4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Right\\Walk_5.bmp", L"Knuckle_Walk_R5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Right\\Walk_6.bmp", L"Knuckle_Walk_R6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Right\\Walk_7.bmp", L"Knuckle_Walk_R7");


	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Left\\Walk_1.bmp", L"Knuckle_Walk_L1");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Left\\Walk_2.bmp", L"Knuckle_Walk_L2");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Left\\Walk_3.bmp", L"Knuckle_Walk_L3");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Left\\Walk_4.bmp", L"Knuckle_Walk_L4");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Left\\Walk_5.bmp", L"Knuckle_Walk_L5");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Left\\Walk_6.bmp", L"Knuckle_Walk_L6");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Walk\\Left\\Walk_7.bmp", L"Knuckle_Walk_L7");


	//Lookup
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\LookUp\\RightLookUp.bmp", L"Knuckle_RightLookup");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\LookUp\\LeftLookUp.bmp", L"Knuckle_LeftLookup");


	//Roll
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Roll\\RightRoll.bmp", L"Knuckle_RightRoll");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Roll\\LeftRoll.bmp", L"Knuckle_LeftRoll");

	//sit
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Crouch\\RightCrouch.bmp", L"Knuckle_RightSit");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Crouch\\LeftCrouch.bmp", L"Knuckle_LeftSit");

	//break
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Break\\Right_Break.bmp", L"Knuckle_RightBreak");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Break\\Left_Break.bmp", L"Knuckle_LeftBreak");

	//Spin
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Spin\\RightSpin.bmp", L"Knuckle_RightSpin");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Spin\\LeftSpin.bmp", L"Knuckle_LeftSpin");

	//Spining
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Spining\\Spining_00.bmp", L"Knuckle_Spining_00");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Spining\\Spining_01.bmp", L"Knuckle_Spining_01");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Spining\\Spining_02.bmp", L"Knuckle_Spining_02");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Spining\\Spining_03.bmp", L"Knuckle_Spining_03");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Spining\\Spining_04.bmp", L"Knuckle_Spining_04");

	//Climb
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\RClimb_00.bmp", L"Knuckle_RClimb_00");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\RClimb_01.bmp", L"Knuckle_RClimb_01");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\RClimb_02.bmp", L"Knuckle_RClimb_02");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\RClimb_03.bmp", L"Knuckle_RClimb_03");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\RClimb_04.bmp", L"Knuckle_RClimb_04");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\RClimb_05.bmp", L"Knuckle_RClimb_05");

	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\LClimb_00.bmp", L"Knuckle_LClimb_00");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\LClimb_01.bmp", L"Knuckle_LClimb_01");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\LClimb_02.bmp", L"Knuckle_LClimb_02");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\LClimb_03.bmp", L"Knuckle_LClimb_03");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\LClimb_04.bmp", L"Knuckle_LClimb_04");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Climb\\LClimb_05.bmp", L"Knuckle_LClimb_05");

	//Drop
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Drop\\RightDrop.bmp", L"Knuckle_RightDrop");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Drop\\LeftDrop.bmp", L"Knuckle_LefttDrop");

	//Push
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Push\\RightPush.bmp", L"Knuckle_RightPush");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Push\\LeftPush.bmp", L"Knuckle_LeftPush");

	//ENDClimb
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\EndClimb\\EndRClimb_01.bmp", L"Knuckle_EndRClimb_01");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\EndClimb\\EndRClimb_02.bmp", L"Knuckle_EndRClimb_02");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\EndClimb\\EndRClimb_03.bmp", L"Knuckle_EndRClimb_03");


	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\EndClimb\\EndLClimb_01.bmp", L"Knuckle_EndLClimb_01");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\EndClimb\\EndLClimb_02.bmp", L"Knuckle_EndLClimb_02");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\EndClimb\\EndLClimb_03.bmp", L"Knuckle_EndLClimb_03");

	//SpringJump
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\SpringJump\\RightSpringJump.bmp", L"Knuckle_SpringRJump");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\SpringJump\\LeftSpringJump.bmp", L"Knuckle_SpringLJump");

	//Hitted
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Hitted\\RightHitted.bmp", L"Knuckle_RightHit");
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Hitted\\LeftHitted.bmp", L"Knuckle_LeftHit");

	//Victory
	ResManager::Manager().LoadTexture(L"\\Charactor\\Knuckle\\Victory\\Victory.bmp", L"Knuckle_Victory");






	Anim = new Animator;
	//idle right;
	Anim->AddAnimation(L"rightidle1", ResManager::Manager().FindTexture(L"Knuckle_RightIdle"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightidle2", ResManager::Manager().FindTexture(L"Knuckle_RightIdle"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 13, 0.2f, RGB(255, 0, 255), 0);
	//idle left;
	Anim->AddAnimation(L"leftidle1", ResManager::Manager().FindTexture(L"Knuckle_LeftIdle"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 13, 500.f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftidle2", ResManager::Manager().FindTexture(L"Knuckle_LeftIdle"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 13, 0.2f, RGB(255, 0, 255), 0);


	//Run
	Anim->AddAnimation(L"rightrun1", ResManager::Manager().FindTexture(L"Knuckle_RightRun"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun1", ResManager::Manager().FindTexture(L"Knuckle_LeftRun"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);


	/////////////////////
	Anim->AddAnimation(L"rightrun_1", ResManager::Manager().FindTexture(L"Knuckle_RightRun_1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_2", ResManager::Manager().FindTexture(L"Knuckle_RightRun_2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_3", ResManager::Manager().FindTexture(L"Knuckle_RightRun_3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_4", ResManager::Manager().FindTexture(L"Knuckle_RightRun_4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_5", ResManager::Manager().FindTexture(L"Knuckle_RightRun_5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_6", ResManager::Manager().FindTexture(L"Knuckle_RightRun_6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightrun_7", ResManager::Manager().FindTexture(L"Knuckle_RightRun_7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);

	//////////////////////////////////////
	Anim->AddAnimation(L"leftrun_1", ResManager::Manager().FindTexture(L"Knuckle_LeftRun_1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_2", ResManager::Manager().FindTexture(L"Knuckle_LeftRun_2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_3", ResManager::Manager().FindTexture(L"Knuckle_LeftRun_3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_4", ResManager::Manager().FindTexture(L"Knuckle_LeftRun_4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_5", ResManager::Manager().FindTexture(L"Knuckle_LeftRun_5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_6", ResManager::Manager().FindTexture(L"Knuckle_LeftRun_6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftrun_7", ResManager::Manager().FindTexture(L"Knuckle_LeftRun_7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);

	//Walk
	Anim->AddAnimation(L"rightwalk", ResManager::Manager().FindTexture(L"Knuckle_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk", ResManager::Manager().FindTexture(L"Knuckle_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightwalk1", ResManager::Manager().FindTexture(L"Knuckle_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk1", ResManager::Manager().FindTexture(L"Knuckle_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightwalk2", ResManager::Manager().FindTexture(L"Knuckle_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk2", ResManager::Manager().FindTexture(L"Knuckle_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"rightwalk3", ResManager::Manager().FindTexture(L"Knuckle_RightWalk"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftwalk3", ResManager::Manager().FindTexture(L"Knuckle_LeftWalk"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	///////////////////Ri
	//加档0
	Anim->AddAnimation(L"walk_R1", ResManager::Manager().FindTexture(L"Knuckle_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2", ResManager::Manager().FindTexture(L"Knuckle_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3", ResManager::Manager().FindTexture(L"Knuckle_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4", ResManager::Manager().FindTexture(L"Knuckle_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5", ResManager::Manager().FindTexture(L"Knuckle_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6", ResManager::Manager().FindTexture(L"Knuckle_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7", ResManager::Manager().FindTexture(L"Knuckle_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	//加档1
	Anim->AddAnimation(L"walk_R1_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	//加档2					 	   
	Anim->AddAnimation(L"walk_R1_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	//加档3					  		   
	Anim->AddAnimation(L"walk_R1_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_R1"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R2_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_R2"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R3_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_R3"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R4_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_R4"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R5_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_R5"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R6_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_R6"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_R7_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_R7"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);

	/////////////////////eft
	//加档0

	Anim->AddAnimation(L"walk_L1", ResManager::Manager().FindTexture(L"Knuckle_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2", ResManager::Manager().FindTexture(L"Knuckle_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3", ResManager::Manager().FindTexture(L"Knuckle_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4", ResManager::Manager().FindTexture(L"Knuckle_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5", ResManager::Manager().FindTexture(L"Knuckle_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6", ResManager::Manager().FindTexture(L"Knuckle_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7", ResManager::Manager().FindTexture(L"Knuckle_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.2f, RGB(255, 0, 255), 0);

	//加档1
	Anim->AddAnimation(L"walk_L1_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7_1", ResManager::Manager().FindTexture(L"Knuckle_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.14f, RGB(255, 0, 255), 0);

	//加档2													 
	Anim->AddAnimation(L"walk_L1_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7_2", ResManager::Manager().FindTexture(L"Knuckle_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.09f, RGB(255, 0, 255), 0);

	//加档3													 
	Anim->AddAnimation(L"walk_L1_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_L1"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L2_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_L2"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L3_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_L3"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L4_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_L4"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L5_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_L5"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L6_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_L6"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"walk_L7_3", ResManager::Manager().FindTexture(L"Knuckle_Walk_L7"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 8, 0.05f, RGB(255, 0, 255), 0);


	////////////////////////////////////////////////
	//LokkUp
	Anim->AddAnimation(L"rightlookup", ResManager::Manager().FindTexture(L"Knuckle_RightLookup"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.2f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftlookup", ResManager::Manager().FindTexture(L"Knuckle_LeftLookup"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.2f, RGB(255, 0, 255), 0);

	//Roll
	Anim->AddAnimation(L"rightroll", ResManager::Manager().FindTexture(L"Knuckle_RightRoll"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftroll", ResManager::Manager().FindTexture(L"Knuckle_LeftRoll"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.05f, RGB(255, 0, 255), 0);

	//Sit
	Anim->AddAnimation(L"rightsit", ResManager::Manager().FindTexture(L"Knuckle_RightSit"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.2f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"leftsit", ResManager::Manager().FindTexture(L"Knuckle_LeftSit"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.2f, RGB(255, 0, 255), 1);


	//break
	Anim->AddAnimation(L"rightbreak", ResManager::Manager().FindTexture(L"Knuckle_RightBreak"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.1f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"leftbreak", ResManager::Manager().FindTexture(L"Knuckle_LeftBreak"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.1f, RGB(255, 0, 255), 1);

	//Spin
	Anim->AddAnimation(L"rightspin", ResManager::Manager().FindTexture(L"Knuckle_RightSpin"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 6, 0.05f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftspin", ResManager::Manager().FindTexture(L"Knuckle_LeftSpin"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 6, 0.05f, RGB(255, 0, 255), 0);


	//Spining
	Anim->AddAnimation(L"spiningleft", ResManager::Manager().FindTexture(L"Knuckle_Spining_00"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"spiningright", ResManager::Manager().FindTexture(L"Knuckle_Spining_04"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);


	//SpiningTurn
	Anim->AddAnimation(L"spining_turn_00", ResManager::Manager().FindTexture(L"Knuckle_Spining_01"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"spining_turn_01", ResManager::Manager().FindTexture(L"Knuckle_Spining_02"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"spining_turn_02", ResManager::Manager().FindTexture(L"Knuckle_Spining_03"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);

	//Climb
	Anim->AddAnimation(L"rightclimb_00", ResManager::Manager().FindTexture(L"Knuckle_RClimb_00"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightclimb_01", ResManager::Manager().FindTexture(L"Knuckle_RClimb_01"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightclimb_02", ResManager::Manager().FindTexture(L"Knuckle_RClimb_02"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightclimb_03", ResManager::Manager().FindTexture(L"Knuckle_RClimb_03"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightclimb_04", ResManager::Manager().FindTexture(L"Knuckle_RClimb_04"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"rightclimb_05", ResManager::Manager().FindTexture(L"Knuckle_RClimb_05"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);


	Anim->AddAnimation(L"leftclimb_00", ResManager::Manager().FindTexture(L"Knuckle_LClimb_00"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftclimb_01", ResManager::Manager().FindTexture(L"Knuckle_LClimb_01"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftclimb_02", ResManager::Manager().FindTexture(L"Knuckle_LClimb_02"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftclimb_03", ResManager::Manager().FindTexture(L"Knuckle_LClimb_03"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftclimb_04", ResManager::Manager().FindTexture(L"Knuckle_LClimb_04"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftclimb_05", ResManager::Manager().FindTexture(L"Knuckle_LClimb_05"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.1f, RGB(255, 0, 255), 0);


	//Drop
	Anim->AddAnimation(L"rightdrop", ResManager::Manager().FindTexture(L"Knuckle_RightDrop"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.12f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"leftdrop", ResManager::Manager().FindTexture(L"Knuckle_LefttDrop"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.12f, RGB(255, 0, 255), 1);


	//push
	Anim->AddAnimation(L"rightpush", ResManager::Manager().FindTexture(L"Knuckle_RightPush"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.18f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"leftpush", ResManager::Manager().FindTexture(L"Knuckle_LeftPush"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 4, 0.18f, RGB(255, 0, 255), 0);


	//EndClimb
	Anim->AddAnimation(L"EndRClimb_01", ResManager::Manager().FindTexture(L"Knuckle_EndRClimb_01"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.5f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"EndRClimb_02", ResManager::Manager().FindTexture(L"Knuckle_EndRClimb_02"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.5f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"EndRClimb_03", ResManager::Manager().FindTexture(L"Knuckle_EndRClimb_03"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 1, 0.5f, RGB(255, 0, 255), 0);


	Anim->AddAnimation(L"EndLClimb_01", ResManager::Manager().FindTexture(L"Knuckle_EndLClimb_01"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 1, 0.5f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"EndLClimb_02", ResManager::Manager().FindTexture(L"Knuckle_EndLClimb_02"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 1, 0.5f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"EndLClimb_03", ResManager::Manager().FindTexture(L"Knuckle_EndLClimb_03"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 1, 0.5f, RGB(255, 0, 255), 0);


	//SpringJump
	Anim->AddAnimation(L"SpringRjump", ResManager::Manager().FindTexture(L"Knuckle_SpringRJump"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 10, 0.12f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"SpringLjump", ResManager::Manager().FindTexture(L"Knuckle_SpringLJump"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 10, 0.12f, RGB(255, 0, 255), 0);

	//Hitted
	Anim->AddAnimation(L"righthit", ResManager::Manager().FindTexture(L"Knuckle_RightHit"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 2, 0.08f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"lefthit", ResManager::Manager().FindTexture(L"Knuckle_LeftHit"), fPOINT{ 0,0 }, -1, fPOINT{ 100,100 }, 2, 0.08f, RGB(255, 0, 255), 1);

	//Victory
	Anim->AddAnimation(L"victory", ResManager::Manager().FindTexture(L"Knuckle_Victory"), fPOINT{ 0,0 }, 1, fPOINT{ 100,100 }, 4, 0.2f, RGB(255, 0, 255), 1);


	Anim->PlayAnimation(L"rightidle1");

}

