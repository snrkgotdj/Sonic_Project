#pragma once
#include "Boss.h"
class Final_Boss_00 :
	public Boss
{
private:
	HDC m_BossTex;
	int m_iLife;
	bool m_bHitted;
	bool m_bDie;

private:
	BOSS_STATE m_eBossState;

private:
	float m_fAccTime;
	float m_fHittedTime;
	float m_fBurnTime;


private:
	void Boss_HItted();
	void Boss_Idle();
	void Boss_Die();
	

public:
	void init(fPOINT _pos);
	bool isDie() { return m_bDie; }

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void exitCollision(Collider* _other) {};

public:
	Final_Boss_00();
	virtual ~Final_Boss_00();
};

