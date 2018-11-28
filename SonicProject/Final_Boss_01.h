#pragma once
#include "Boss.h"
class Final_Boss_01 :
	public Boss
{
private:
	fPOINT m_ptStartPos;
	BOSS_STATE m_eBossState;

private:
	int m_iLife;
	bool m_bHitted;
	bool m_bDie;

private:
	float m_fAccTime;
	float m_fHittedTime;
	float m_fBurnTime;

private:
	void Boss_Apear();
	void Boss_Idle();
	void Boss_HItted();
	void Boss_Die();

	float getRandomNumber(float min, float max);

public:
	void init(fPOINT _pos);

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void exitCollision(Collider* _other) {};

public:
	Final_Boss_01();
	~Final_Boss_01();
};

