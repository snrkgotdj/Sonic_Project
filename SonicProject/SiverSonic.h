#pragma once
#include "Boss.h"

class Animator;

class SiverSonic :
	public Boss
{
private:
	Animator* m_FireAnim;



private:
	BOSS_STATE Boss_State;
	SILVER_ANIM m_eAnim;
	SILVER_ANIM m_eOldAnim;


private:
	int m_iDashStack;
	int m_iLife;

private:
	int m_iFloor;
	bool m_bGroundOn;
	bool m_bDir;
	bool m_bDashOn;
	bool m_bHitted;
	bool m_bRenderChange;

private:
	float m_fAccTime;
	float m_fSpeed;
	float m_fJumpSpeed;
	float m_fGravity;
	float m_fAccRender;
	float m_fHittedTime;

private:
	void RanderChange();
	void SwitchAnimation();
	void AdjustCol();

private:
	void Boss_Appear();
	void Boss_Roll();
	void Boss_RightDash();
	void Boss_LeftDash();
	void Boss_RollJump();
	void Boss_Die();

private:
	void SpitOutRing(Collider * _other);
	float getRandomNumber(float min, float max);

public:
	void init(fPOINT _pos);

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other) {};
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other) {};

public:
	SiverSonic();
	virtual ~SiverSonic();
};

