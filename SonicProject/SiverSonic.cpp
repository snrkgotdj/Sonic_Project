#include "stdafx.h"
#include "SiverSonic.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "Collider.h"
#include "Camera.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "Player.h"
#include "StageManager.h"
#include "Ring.h"
#include "Stage.h"
#include "Goal.h"


SiverSonic::SiverSonic()
	:m_iFloor(1435)
	, m_FireAnim(NULL)
	, m_bGroundOn(false)
	, Boss_State(BOSS_APPEAR)
	, m_fAccTime(0.f)
	, m_bDir(DIR_LEFT)
	, m_eAnim(SILVER_IDLE)
	, m_eOldAnim(SILVER_IDLE)
	, m_fSpeed(0.f)
	, m_bDashOn(false)
	, m_iDashStack(0)
	, m_bHitted(false)
	, m_fAccRender(0.f)
	, m_bRenderChange(false)
	, m_fHittedTime(0.f)
	, m_iLife(10)
{
}


SiverSonic::~SiverSonic()
{
	if (m_FireAnim != NULL)
	{
		delete m_FireAnim;
	}

}

void SiverSonic::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 40, 56 };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	

	ResManager::Manager().LoadTexture(L"\\Boss\\SiverSonic\\Right_Idle.bmp", L"Siver_Idle_Right");
	ResManager::Manager().LoadTexture(L"\\Boss\\SiverSonic\\Left_Idle.bmp", L"Siver_Idle_Left");
	ResManager::Manager().LoadTexture(L"\\Boss\\SiverSonic\\Fire.bmp", L"Siver_Fire");
	ResManager::Manager().LoadTexture(L"\\Boss\\SiverSonic\\Right_Roll.bmp", L"Siver_Right_Roll");
	ResManager::Manager().LoadTexture(L"\\Boss\\SiverSonic\\Left_Roll.bmp", L"Siver_Left_Roll");
	ResManager::Manager().LoadTexture(L"\\Boss\\SiverSonic\\Right_Dash.bmp", L"Siver_Right_Dash");
	ResManager::Manager().LoadTexture(L"\\Boss\\SiverSonic\\Left_Dash.bmp", L"Siver_Left_Dash");
	ResManager::Manager().LoadTexture(L"\\Boss\\SiverSonic\\Right_Dash_Turn.bmp", L"Siver_Right_Dash_Turn");
	ResManager::Manager().LoadTexture(L"\\Boss\\SiverSonic\\Right_Hitted.bmp", L"Siver_Right_Hitted");
	ResManager::Manager().LoadTexture(L"\\Boss\\SiverSonic\\Left_Hitted.bmp", L"Siver_Left_Hitted");

	ResManager::Manager().LoadTexture(L"\\Boss\\BossExplosion.bmp", L"Boss_Explosion");




	Anim = new Animator;
	
	//IDLE
	Anim->AddAnimation(L"Idle_Right", ResManager::Manager().FindTexture(L"Siver_Idle_Right"), fPOINT{ 0,0 }, 1, fPOINT{ 80,112 }, 3, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Idle_Left", ResManager::Manager().FindTexture(L"Siver_Idle_Left"), fPOINT{ 0,0 }, -1, fPOINT{ 80,112 }, 3, 0.1f, RGB(255, 0, 255), 0);

	//ROLL
	Anim->AddAnimation(L"Roll_Right", ResManager::Manager().FindTexture(L"Siver_Right_Roll"), fPOINT{ 0,0 }, 1, fPOINT{ 96,92 }, 3, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Roll_Right_00", ResManager::Manager().FindTexture(L"Siver_Right_Roll"), fPOINT{ 0,0 }, 1, fPOINT{ 96,92 }, 3, 0.08f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Roll_Right_01", ResManager::Manager().FindTexture(L"Siver_Right_Roll"), fPOINT{ 0,0 }, 1, fPOINT{ 96,92 }, 3, 0.06f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Roll_Right_02", ResManager::Manager().FindTexture(L"Siver_Right_Roll"), fPOINT{ 0,0 }, 1, fPOINT{ 96,92 }, 3, 0.03f, RGB(255, 0, 255), 0);

	Anim->AddAnimation(L"Roll_Left", ResManager::Manager().FindTexture(L"Siver_Left_Roll"), fPOINT{ 0,0 }, -1, fPOINT{ 96,92 }, 3, 0.1f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Roll_Left_00", ResManager::Manager().FindTexture(L"Siver_Left_Roll"), fPOINT{ 0,0 }, -1, fPOINT{ 96,92 }, 3, 0.08f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Roll_Left_01", ResManager::Manager().FindTexture(L"Siver_Left_Roll"), fPOINT{ 0,0 }, -1, fPOINT{ 96,92 }, 3, 0.06f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Roll_Left_02", ResManager::Manager().FindTexture(L"Siver_Left_Roll"), fPOINT{ 0,0 }, -1, fPOINT{ 96,92 }, 3, 0.03f, RGB(255, 0, 255), 0);

	//DASH
	Anim->AddAnimation(L"Dash_Right", ResManager::Manager().FindTexture(L"Siver_Right_Dash"), fPOINT{ 0,0 }, 1, fPOINT{ 128,110 }, 3, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Dash_Left", ResManager::Manager().FindTexture(L"Siver_Left_Dash"), fPOINT{ 0,0 }, -1, fPOINT{ 128,110 }, 3, 0.025f, RGB(255, 0, 255), 0);

	//DASH TURN
	Anim->AddAnimation(L"Dash_Turn_Right", ResManager::Manager().FindTexture(L"Siver_Right_Dash_Turn"), fPOINT{ 0,0 }, 1, fPOINT{ 88,110 }, 3, 0.2f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"Dash_Turn_Left", ResManager::Manager().FindTexture(L"Siver_Right_Dash_Turn"), fPOINT{ 0,0 }, -1, fPOINT{ 88,110 }, 3, 0.2f, RGB(255, 0, 255), 1);

	//Hitted
	Anim->AddAnimation(L"Hitted_Right", ResManager::Manager().FindTexture(L"Siver_Right_Hitted"), fPOINT{ 0,0 }, 1, fPOINT{ 80,112 }, 1, 0.2f, RGB(255, 0, 255), 1);
	Anim->AddAnimation(L"Hitted_Left", ResManager::Manager().FindTexture(L"Siver_Left_Hitted"), fPOINT{ 0,0 }, 1, fPOINT{ 80,112 }, 1, 0.2f, RGB(255, 0, 255), 1);


	Anim->PlayAnimation(L"Idle_Left");


	m_FireAnim = new Animator;
	m_FireAnim->AddAnimation(L"Fire", ResManager::Manager().FindTexture(L"Siver_Fire"), fPOINT{ 0,0 }, 1, fPOINT{ 32,44 }, 2, 0.025f, RGB(255, 0, 255), 0);
	m_FireAnim->AddAnimation(L"Explosion", ResManager::Manager().FindTexture(L"Boss_Explosion"), fPOINT{ 0,0 }, 1, fPOINT{ 80,82 }, 32, 0.5f, RGB(255, 0, 255), 0);

	
	m_FireAnim->PlayAnimation(L"Fire");
}

void SiverSonic::render(HDC _dc)
{
	if (m_eAnim != SILVER_DASH)
	{
		if(m_eAnim != SILVER_IDLE)
			Anim->render(_dc, pos);

		else if (m_eAnim == SILVER_IDLE)
		{
			if (m_bHitted == false)
			{
				Anim->render(_dc, pos);
			}
			
			else if (m_bHitted == true)
			{
				if (m_bRenderChange == false)
				{
					if(m_bDir == DIR_RIGHT)
						Anim->PlayAnimation(L"Hitted_Right");

					else if (m_bDir == DIR_LEFT)
						Anim->PlayAnimation(L"Hitted_Left");

					Anim->render(_dc, pos);
				}

				else if(m_bRenderChange == true)
				{
					if (m_bDir == DIR_RIGHT)
						Anim->PlayAnimation(L"Idle_Right");

					else if (m_bDir == DIR_LEFT)
						Anim->PlayAnimation(L"Idle_Left");

					Anim->render(_dc, pos);
				}

			}
		}
	}

	else if (m_eAnim == SILVER_DASH)
	{
		if (m_bDir == DIR_RIGHT)
		{
			Anim->render(_dc, fPOINT{pos.x -35, pos.y});
		}

		else if (m_bDir == DIR_LEFT)
		{
			Anim->render(_dc, fPOINT{ pos.x + 35, pos.y });
		}
	}

	if (m_bGroundOn == false)
		m_FireAnim->render(_dc, fPOINT{ pos.x , pos.y + 44 });

	if (m_iLife <= 0)
	{
		m_FireAnim->render(_dc, fPOINT{ pos.x - size.x , pos.y});
		m_FireAnim->render(_dc, fPOINT{ pos.x + size.x , pos.y });
		m_FireAnim->render(_dc, fPOINT{ pos.x - 20, pos.y - 30 });
		m_FireAnim->render(_dc, fPOINT{ pos.x + 30, pos.y  - 30});
		m_FireAnim->render(_dc, fPOINT{ pos.x , pos.y });
	}

}

void SiverSonic::update()
{
	collider->update();

	if (Camera::Cam().isPause() == false)
	{
		return;
	}

	switch (Boss_State)
	{
	case BOSS_APPEAR:
		Boss_Appear();
		break;
	case BOSS_ROLL:
		Boss_Roll();
		break;

	case BOSS_RIGHTDASH:
		Boss_RightDash();
		break;

	case BOSS_LEFTDASH:
		Boss_LeftDash();
		break;

	case BOSS_ROLLJUMP:
		Boss_RollJump();
		break;
	case BOSS_DIE:
		Boss_Die();
		break;
	default:
		break;
	}
	
	SwitchAnimation();

	RanderChange();

	AdjustCol();

	m_eOldAnim = m_eAnim;

	if (pos.y >= m_iFloor)
	{
		pos.y = (float)m_iFloor;
	}

	if (m_iLife <= 0 && Boss_State != BOSS_DIE)
	{
		m_fAccTime = 0.f;
		Boss_State = BOSS_DIE;
	}
}

void SiverSonic::onCollision(Collider * _other)
{
	if (((ANI_SPINING == ((Player*)(_other->GetOwner()))->GetAnimation()||ANI_JUMP == ((Player*)(_other->GetOwner()))->GetAnimation()) && m_eAnim == SILVER_IDLE && m_bHitted == false)
		|| (((Player*)(_other->GetOwner()))->isSuper() == true && m_bHitted == false && m_eAnim == SILVER_IDLE))
	{
		m_iLife -= 1;
		((Player*)(_other->GetOwner()))->SetState(PLAYER_JUMP);
		((Player*)(_other->GetOwner()))->SetJumpSpeed(500);
		((Player*)(_other->GetOwner()))->SetGravity(0.f);

		m_bHitted = true;

		SoundManager::Manager()->StopSound(L"Sound_BossDamage");
		SoundManager::Manager()->PlaySoundW(L"Sound_BossDamage", false);
	}

	else if (((ANI_SPINING != ((Player*)(_other->GetOwner()))->GetAnimation() && ANI_JUMP != ((Player*)(_other->GetOwner()))->GetAnimation()) || m_eAnim != SILVER_IDLE) && ((Player*)(_other->GetOwner()))->GetInvincible() == false)
	{
		if (((Player*)(_other->GetOwner()))->isSuper() == true)
		{
			return;
		}

		if (((Player*)(_other->GetOwner()))->GetDir() == DIR_RIGHT)
		{
			((Player*)(_other->GetOwner()))->SetState(PLAYER_HITTED);
			((Player*)(_other->GetOwner()))->SetSpeed(-250.f);
			((Player*)(_other->GetOwner()))->SetGravity(0.f);
			((Player*)(_other->GetOwner()))->SetJumpSpeed(300.f);
			((Player*)(_other->GetOwner()))->SetInvincible(true);
			if (((Player*)(_other->GetOwner()))->GetShield() == SHIELD_END)
			{
				if (0 != ((Player*)(_other->GetOwner()))->GetRingCnt())
				{
					SoundManager::Manager()->PlaySoundW(L"Sound_SpitRing", false);
					SpitOutRing(_other);
					((Player*)(_other->GetOwner()))->SetRingCnt(0);
				}
				else
				{
					SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
				}
			}

			else
			{
				SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
			}
		}

		else if (((Player*)(_other->GetOwner()))->GetDir() == DIR_LEFT)
		{
			((Player*)(_other->GetOwner()))->SetState(PLAYER_HITTED);
			((Player*)(_other->GetOwner()))->SetSpeed(+250.f);
			((Player*)(_other->GetOwner()))->SetGravity(0.f);
			((Player*)(_other->GetOwner()))->SetJumpSpeed(300.f);
			((Player*)(_other->GetOwner()))->SetInvincible(true);
			if (((Player*)(_other->GetOwner()))->GetShield() == SHIELD_END)
			{
				if (0 != ((Player*)(_other->GetOwner()))->GetRingCnt())
				{
					SoundManager::Manager()->PlaySoundW(L"Sound_SpitRing", false);
					SpitOutRing(_other);
					((Player*)(_other->GetOwner()))->SetRingCnt(0);
				}
				else
				{
					SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
				}
			}
			else
			{
				SoundManager::Manager()->PlaySoundW(L"Sound_Electricity", false);
			}
		}
	}
}

void SiverSonic::Boss_Appear()
{
	if (pos.y < m_iFloor)
	{
		
		pos.y += 200 * DT;

		if (pos.y >= m_iFloor)
		{
			pos.y = (float)m_iFloor;
			m_bGroundOn = true;
		}
	}

	if (m_bGroundOn == true)
	{
		m_fAccTime += DT;

		if (m_fAccTime >= 1)
		{
			Boss_State = BOSS_ROLL;
			m_eAnim = SILVER_ROLL;
			m_fAccTime = 0.f;
		}
	}
}

void SiverSonic::Boss_Roll()
{
	SoundManager::Manager()->PlaySoundW(L"Sound_BossRoll", true);

	if (m_fSpeed < 500 && pos.x != Camera::Cam().GetLimit().x - 930)
	{
		m_fSpeed += 200 * DT;

		if (m_fSpeed >= 500)
		{
			m_fSpeed = 500;
		}
	}

	if ((int)m_fSpeed == 500 && m_bDir == DIR_LEFT)
	{
		if (pos.x > Camera::Cam().GetLimit().x - 930)
		{
			pos.x -= m_fSpeed *DT;

			if (pos.x <= Camera::Cam().GetLimit().x - 930)
			{
				pos.x = (float)Camera::Cam().GetLimit().x - 930;
			}
		}
	}

	if (pos.x == Camera::Cam().GetLimit().x - 930)
	{
		if (m_fSpeed > 0)
		{
			m_fSpeed -= 200 * DT;
			if (m_fSpeed <= 0)
			{
				m_fSpeed = 0;
				m_eAnim = SILVER_IDLE;
				m_bDir = DIR_RIGHT;
				Boss_State = BOSS_RIGHTDASH;

				SoundManager::Manager()->StopSound(L"Sound_BossRoll");
			}
		}
	}
}


void SiverSonic::SwitchAnimation()
{
	switch (m_eAnim)
	{
	case SILVER_IDLE:
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"Idle_Right");

		else if (m_bDir == DIR_LEFT)
			Anim->PlayAnimation(L"Idle_Left");

		break;
	case SILVER_ROLL:
		if (m_bDir == DIR_RIGHT)
		{
			if (m_fSpeed < 100 && m_fSpeed >= 0)
				Anim->PlayAnimation(L"Roll_Right");
			else if (m_fSpeed < 200 && m_fSpeed >= 100)
				Anim->PlayAnimation(L"Roll_Right_00");
			else if (m_fSpeed < 300 && m_fSpeed >= 200)
				Anim->PlayAnimation(L"Roll_Right_01");
			else if (m_fSpeed >= 400)
				Anim->PlayAnimation(L"Roll_Right_02");

		}
			
		else if (m_bDir == DIR_LEFT)
		{
			if (m_fSpeed <= 100 && m_fSpeed >= 0)
				Anim->PlayAnimation(L"Roll_Left");
			else if (m_fSpeed <= 200 && m_fSpeed >= 100)
				Anim->PlayAnimation(L"Roll_Left_00");
			else if (m_fSpeed < 300 && m_fSpeed >= 200)
				Anim->PlayAnimation(L"Roll_Left_01");
			else if (m_fSpeed >= 400)
				Anim->PlayAnimation(L"Roll_Left_02");
		}

		break;
	case SILVER_DASH:
		
		if (m_bDir == DIR_RIGHT)
			Anim->PlayAnimation(L"Dash_Right");

		else if (m_bDir == DIR_LEFT)
			Anim->PlayAnimation(L"Dash_Left");
		
		break;

	case SILVER_DASHTURN:
		if (m_eOldAnim != SILVER_DASHTURN)
		{
			if (m_bDir == DIR_RIGHT)
				Anim->PlayAnimation(L"Dash_Turn_Right", 0);

			else if (m_bDir == DIR_LEFT)
				Anim->PlayAnimation(L"Dash_Turn_Left", 0);
		}
		break;
	case SILVER_END:
		break;
	default:
		break;
	}

}

void SiverSonic::AdjustCol()
{
	switch (m_eAnim)
	{
	case SILVER_IDLE:
		size = fPOINT{ 40, 56 };
		break;
	case SILVER_ROLL:
		size = fPOINT{ 48,46 };

		break;
	case SILVER_END:
		break;
	default:
		break;
	}
}

void SiverSonic::Boss_RightDash()
{
	
	if (m_fAccTime <= 1)
	{
		m_fAccTime += DT;
	}

	if (m_fAccTime >= 1 && m_bDashOn == false)
	{
		SoundManager::Manager()->PlaySoundW(L"Sound_BossDash", false); 
		m_eAnim = SILVER_DASH;

		m_fSpeed += 500 * DT;

		if (m_fSpeed >= 1200)
		{
			m_bDashOn = true;
		}
	}

	if (m_bDashOn == true && m_bDir == DIR_RIGHT)
	{
		if (pos.x >= Camera::Cam().GetLimit().x - 300)
		{
			m_fSpeed -= 3000 * DT;
			m_eAnim = SILVER_DASHTURN;

			if (m_fSpeed <= 0 && m_iDashStack <=3)
			{
				m_iDashStack += 1;
				m_fSpeed = 0;
				Boss_State = BOSS_LEFTDASH;
				m_eAnim = SILVER_DASH;
				m_fSpeed = 1200;
				m_bDir = DIR_LEFT;
				return;
			}
		}
		pos.x += m_fSpeed * DT;
	}
}

void SiverSonic::Boss_LeftDash()
{
	if (m_bDir == DIR_LEFT)
	{
		if (pos.x <= Camera::Cam().GetLimit().x - 700)
		{
			m_fSpeed -= 3000 * DT;
			m_eAnim = SILVER_DASHTURN;
			if (m_fSpeed <= 0 && m_iDashStack != 3)
			{
				m_fSpeed = 0;
				Boss_State = BOSS_RIGHTDASH;
				m_eAnim = SILVER_DASH;
				m_fSpeed = 1200;
				m_bDir = DIR_RIGHT;
				return;
			}

			if (m_fSpeed <= 0 && m_iDashStack == 3)
			{
				m_fSpeed = 0;
				m_eAnim = SILVER_IDLE;
				m_bDir = DIR_RIGHT;
				Boss_State = BOSS_ROLLJUMP;
				m_bDashOn = false;
				m_fAccTime = 0.f;
				m_iDashStack = 0;

				
				return;
			}
		}
		pos.x -= m_fSpeed * DT;
	}
}



void SiverSonic::Boss_RollJump()
{


	if (m_fAccTime <= 1 && m_bDashOn == false)
	{
		m_fAccTime += DT;
	}

	if (m_fAccTime >= 1 && m_bDashOn == false)
	{
		m_eAnim = SILVER_ROLL;

		SoundManager::Manager()->PlaySoundW(L"Sound_BossRoll", true);

		m_fSpeed += 200 * DT;

		if (m_fSpeed >= 500)
		{
			m_bDashOn = true;
			m_fSpeed = 900;
			m_eAnim = SILVER_ROLL;
			m_fJumpSpeed = 800;
			m_fGravity = 0;
			m_fAccTime = 0.f;

			
		}
	}

	if (m_bDashOn == false)
	{
		return;
	}


	if (pos.x < Camera::Cam().GetLimit().x - 100)
	{
		m_fGravity += 1800 * DT;

		pos.x += m_fSpeed * DT;

		pos.y -= m_fJumpSpeed * DT;
		pos.y += m_fGravity * DT;
	}
	
	else if (pos.x >= Camera::Cam().GetLimit().x - 100)
	{
		if (m_fGravity != 0)
		{
			m_fSpeed = 500;
		}
		pos.x = (float)Camera::Cam().GetLimit().x - 100;
		m_fGravity = 0;

		m_fSpeed -= 200 * DT;

		if (m_fSpeed <= 0)
		{
			SoundManager::Manager()->StopSound(L"Sound_BossRoll");
			m_eAnim = SILVER_IDLE;
			m_bDir = DIR_LEFT;

			m_fAccTime += DT;

			if (m_fAccTime >= 1)
			{
				m_fAccTime = 0.f;
				Boss_State = BOSS_ROLL;
				m_fSpeed = 0.f;
				m_eAnim = SILVER_ROLL;
				m_bDashOn = false;
			}
		}
	}

}

void SiverSonic::Boss_Die()
{
	SoundManager::Manager()->PlaySoundW(L"Sound_BossDeath", true);

	m_fAccTime += DT;

	m_FireAnim->PlayAnimation(L"Explosion");

	if (m_fAccTime >= 3)
	{
		OBJ::Die();
		SoundManager::Manager()->StopSound(L"Sound_BossDeath");
		SoundManager::Manager()->PlayBGM(L"BGM_STAGE_00");

		Goal * pGoal = new Goal;
		pGoal->init(fPOINT{ 19622, 900 });
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_GOAL).push_back(pGoal);
		
	}
}


void SiverSonic::SpitOutRing(Collider * _other)
{
	int iRingCnt = ((Player*)(_other->GetOwner()))->GetRingCnt();


	for (int i = 0; i < iRingCnt; ++i)
	{
		Ring* pRing = new Ring(true, getRandomNumber(0, (float)M_PI)
			, StageManager::Manager().GetCurStage()->GetFloorColor()
			, StageManager::Manager().GetCurStage()->GetWallColor()
			, StageManager::Manager().GetCurStageType());

		pRing->init(fPOINT{ _other->GetOwner()->GetPos().x, _other->GetOwner()->GetPos().y });
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_RING).push_back(pRing);
	}
}

float SiverSonic::getRandomNumber(float min, float max)
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_real_distribution<float> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}


void SiverSonic::RanderChange()
{
	m_fHittedTime += DT;
	m_fAccRender += 20 * DT;

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

	if (m_fHittedTime >= 0.7)
	{
		m_bHitted = false;
		m_fHittedTime = 0;
		m_fAccRender = 0;
	}
}