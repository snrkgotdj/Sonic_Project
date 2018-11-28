#include "stdafx.h"
#include "Missile.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animator.h"
#include "Collider.h"
#include "Player.h"
#include "TimeManager.h"
#include "Effect_Missile_Bomb.h"
#include "StageManager.h"
#include "Stage.h"
#include "SoundManager.h"

Missile::Missile()
	:m_pPlayer(NULL)
	, m_ptGradient{ 1,0 }
	, m_fSpeed(300)
	, m_bFollow(false)
{
}


Missile::~Missile()
{
}


void Missile::init(fPOINT _pos, Player* _player, bool _follow)
{
	pos = _pos;
	m_bFollow = _follow;

	m_pPlayer = _player;
	size = fPOINT{ 64,16 };

	collider = new Collider(this);
	collider->SetType(COL_RECT);
	collider->SetOffset(fPOINT{ 0, 0 });

	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Left_Missile.bmp", L"Missile_Left");
	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Right_Missile.bmp", L"Missile_Right");
	
	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Left_UP_Missile.bmp", L"Missile_Left_UP");
	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Right_UP_Missile.bmp", L"Missile_Right_UP");
	
	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Left_Down_Missile.bmp", L"Missile_Left_Down");
	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Right_Down_Missile.bmp", L"Missile_Right_Down");

	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\Down_Missile.bmp", L"Missile_Down");
	ResManager::Manager().LoadTexture(L"\\Boss\\FinalBoss\\UP_Missile.bmp", L"Missile_UP");


	Anim = new Animator;


	Anim->AddAnimation(L"Missile_Left", ResManager::Manager().FindTexture(L"Missile_Left"), fPOINT{ 0,0 }, 1, fPOINT{ 128,32 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Missile_Right", ResManager::Manager().FindTexture(L"Missile_Right"), fPOINT{ 0,0 }, 1, fPOINT{ 128,32 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Missile_Left_UP", ResManager::Manager().FindTexture(L"Missile_Left_UP"), fPOINT{ 0,0 }, 1, fPOINT{ 128,128 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Missile_Right_UP", ResManager::Manager().FindTexture(L"Missile_Right_UP"), fPOINT{ 0,0 }, 1, fPOINT{ 128,128 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Missile_Left_Down", ResManager::Manager().FindTexture(L"Missile_Left_Down"), fPOINT{ 0,0 }, 1, fPOINT{ 128,128 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Missile_Right_Down", ResManager::Manager().FindTexture(L"Missile_Right_Down"), fPOINT{ 0,0 }, 1, fPOINT{ 128,128 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Missile_UP", ResManager::Manager().FindTexture(L"Missile_UP"), fPOINT{ 0,0 }, 1, fPOINT{ 32,128 }, 2, 0.025f, RGB(255, 0, 255), 0);
	Anim->AddAnimation(L"Missile_Down", ResManager::Manager().FindTexture(L"Missile_Down"), fPOINT{ 0,0 }, 1, fPOINT{ 32,128 }, 2, 0.025f, RGB(255, 0, 255), 0);


	Anim->PlayAnimation(L"Missile_Left");
}

void Missile::SetAnimation(const wstring & _Animation)
{
	Anim->PlayAnimation(_Animation);
}

void Missile::SwitchAnimation()
{
	if (m_ptGradient.x >= 0.8f)
		Anim->PlayAnimation(L"Missile_Left");

	else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
		Anim->PlayAnimation(L"Missile_Left_Down");
		
	else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
		Anim->PlayAnimation(L"Missile_Down");
		
	else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
		Anim->PlayAnimation(L"Missile_Right_Down");
		
	else if (m_ptGradient.x <= -0.8f)
		Anim->PlayAnimation(L"Missile_Right");

	else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
		Anim->PlayAnimation(L"Missile_Right_UP");

	else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
		Anim->PlayAnimation(L"Missile_UP");

	else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
		Anim->PlayAnimation(L"Missile_Left_UP");
}

void Missile::AdjustCol()
{
	if (m_ptGradient.x >= 0.8f)
	{
		size = fPOINT{ 64,16 };
	}

	else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
		size = fPOINT{ 50,50 };

	else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
		size = fPOINT{ 16,64 };

	else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
		size = fPOINT{ 50,50 };

	else if (m_ptGradient.x <= -0.8f)
		size = fPOINT{ 64,16 };

	else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
		size = fPOINT{ 50,50 };

	else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
		size = fPOINT{ 16,64 };

	else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
		size = fPOINT{ 50,50 };
}

void Missile::CreateEffect()
{
	Effect_Missile_Bomb* pEffect = new Effect_Missile_Bomb;
	if (m_ptGradient.x >= 0.8f)
		pEffect->init(fPOINT{ pos.x - 50, pos.y + 16 });

	else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y > 0.f)
		pEffect->init(fPOINT{ pos.x - 50, pos.y + 50 });

	else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y > 0.f)
		pEffect->init(fPOINT{ pos.x, pos.y + 50 });

	else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y > 0.f)
		pEffect->init(fPOINT{ pos.x + 50, pos.y + 50 });

	else if (m_ptGradient.x <= -0.8f)
		pEffect->init(fPOINT{ pos.x + 50, pos.y + 16 });

	else if (m_ptGradient.x > -0.8f && m_ptGradient.x <= -0.3f && m_ptGradient.y < 0.f)
		pEffect->init(fPOINT{ pos.x + 50, pos.y - 50 });

	else if (m_ptGradient.x > -0.3f && m_ptGradient.x <= 0.3f && m_ptGradient.y < 0.f)
		pEffect->init(fPOINT{ pos.x, pos.y - 50 });

	else if (m_ptGradient.x > 0.3f && m_ptGradient.x <= 0.8f && m_ptGradient.y < 0.f)
		pEffect->init(fPOINT{ pos.x - 50, pos.y - 50 });


	StageManager::Manager().GetCurStage()->GetListObj(OBJ_EFFECT).push_back(pEffect);
}



void Missile::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Missile::update()
{
	collider->update();

	if (m_bFollow == true)
	{
		FollowPlayer();

		MoveMissile();

		SwitchAnimation();

		AdjustCol();
	}

	else if (m_bFollow == false)
	{
		pos.x -= 700 * DT;
	}
	
}

void Missile::enterCollision(Collider * _other)
{
	CreateEffect();
	
	if (_other->GetOwner()->GetOBJType() == Obj_PLAYER)
	{
		((Player*)(_other->GetOwner()))->SetAnimation(ANI_HITTED);
		((Player*)(_other->GetOwner()))->SetInvincible(true);
	}

	OBJ::Die();

	SoundManager::Manager()->StopSound(L"Sound_Explosion");
	SoundManager::Manager()->PlaySoundW(L"Sound_Explosion", false);
}

void Missile::onCollision(Collider * _other)
{

	
}

void Missile::FollowPlayer()
{
	fPOINT PlayerPos = m_pPlayer->GetPos();
	fPOINT PlayerSize = m_pPlayer->GetSize();

	float v = sqrt((pos.x - PlayerPos.x) * (pos.x - PlayerPos.x) + ((PlayerPos.y - PlayerSize.y) - (pos.y - size.y )) * ((PlayerPos.y - PlayerSize.y) - (pos.y - size.y)));
	if (v == 0)
		assert(NULL);

	m_ptGradient.x = (pos.x - PlayerPos.x) / v;
	m_ptGradient.y = ((PlayerPos.y - PlayerSize.y) - (pos.y- size.y)) / v;


}

void Missile::MoveMissile()
{
	pos.x -= m_fSpeed * DT * m_ptGradient.x;
	pos.y += m_fSpeed * DT * m_ptGradient.y;
}


