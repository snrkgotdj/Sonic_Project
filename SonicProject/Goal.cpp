#include "stdafx.h"
#include "Goal.h"
#include "OBJ_Box.h"
#include "ResManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Camera.h"
#include "Animation.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Player.h"
#include "SoundManager.h"
#include "StageManager.h"
#include "Stage.h"
#include "UIManager.h"
#include "Effect_Ring.h"


Goal::Goal()
	:m_iFloor(1435)
	, m_fGravity(0.f)
	, m_bGroundOn(false)
	, m_fJumpSpeed(0.f)
	, m_ptGradient{0,1}
	, m_fEffectTime(0.f)
{
}


Goal::~Goal()
{
}

float Goal::getRandomNumber(float min, float max)
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_real_distribution<float> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}



void Goal::GravityOn()
{
	if (m_bGroundOn == false)
	{
		m_fGravity += 400 * DT;
		pos.y += m_fGravity * DT;

		if (pos.y >= m_iFloor)
		{
			pos.y = (float)m_iFloor;
			m_fGravity = 0.f;
			m_bGroundOn = true;
			m_fJumpSpeed = 0.f;
			Anim->PlayAnimation(L"Goal_End");
			((Player*)(StageManager::Manager().GetCurStage()->GetListObj(Obj_PLAYER)[0]))->SetSuperSonic(false);
			((Player*)(StageManager::Manager().GetCurStage()->GetListObj(Obj_PLAYER)[0]))->SetState(PLAYER_FINISH);

			UIManager::Manager().SetVictory(true);

			SoundManager::Manager()->StopSound(L"BGM_STAGE_00");
			SoundManager::Manager()->PlaySoundW(L"Sound_Victory", false);
		}
		pos.x += m_ptGradient.x * m_fJumpSpeed * DT;
		pos.y -= m_ptGradient.y * m_fJumpSpeed * DT;
	}
}

void Goal::BounceWall()
{
	if (19190 + size.x > pos.x)
	{
		pos.x = 19191 + size.x;
		m_ptGradient.x = -m_ptGradient.x;
	}

	else if (20150 - size.y < pos.x)
	{
		pos.x = 20150 - size.x;
		m_ptGradient.x = -m_ptGradient.x;
	}
}

void Goal::StarEffect()
{
	m_fEffectTime += 10 * DT;
	if (m_fEffectTime >= 1)
	{
		Effect_Ring* pEffect = new Effect_Ring;
		pEffect->init(fPOINT{ getRandomNumber(pos.x - size.x, pos.x + size.x), getRandomNumber(pos.y - size.y * 2, pos.y) });
		StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pEffect);

		m_fEffectTime = 0;
	}
}

void Goal::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Goal::update()
{
	collider->update();

	GravityOn();

	BounceWall();

	StarEffect();
	
}

void Goal::enterCollision(Collider * _other)
{
	if (((Player*)(_other->GetOwner()))->GetAnimation() == ANI_JUMP)
	{
		SoundManager::Manager()->StopSound(L"Sound_Goal");
		SoundManager::Manager()->PlaySoundW(L"Sound_Goal", false);

		m_fJumpSpeed = 500;
		m_fGravity = 0.f;

		fPOINT ptPos = ((Player*)(_other->GetOwner()))->GetPos();
		fPOINT ptOldPos = ((Player*)(_other->GetOwner()))->GetOldPos();

		float v = sqrt((ptPos.x - ptOldPos.x) * (ptPos.x - ptOldPos.x) + (ptPos.y - ptOldPos.y) * (ptPos.y - ptOldPos.y));
		if (v == 0)
			assert(NULL);

		m_ptGradient.x = (ptPos.x - ptOldPos.x) / v;
		m_ptGradient.y = (ptOldPos.y - ptPos.y) / v;
	}
}

void Goal::onCollision(Collider * _other)
{
}

void Goal::exitCollision(Collider * _other)
{
}

void Goal::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 48, 48 };


	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Item\\Goal\\Goal.bmp", L"Item_Goal");

	Anim = new Animator;

	Anim->AddAnimation(L"Goal_turn", ResManager::Manager().FindTexture(L"Item_Goal"), fPOINT{ 0,0 }, 1, fPOINT{ 96,96 }, 9, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Goal_End", ResManager::Manager().FindTexture(L"Item_Goal"), fPOINT{ 0,0 }, 1, fPOINT{ 96,96 }, 9, 0.025f, RGB(255, 0, 255), 1);

	Anim->PlayAnimation(L"Goal_turn");
}

