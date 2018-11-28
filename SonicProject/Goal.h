#pragma once
#include "OBJ.h"
class Goal :
	public OBJ
{
private:
	int m_iFloor;
	float m_fGravity;
	float m_fJumpSpeed;
	float m_fEffectTime;

	bool m_bGroundOn;
	fPOINT m_ptGradient;

private:
	void GravityOn();
	void BounceWall();
	void StarEffect();
	float getRandomNumber(float min, float max);

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other);

public:
	void init(fPOINT _pos);


public:
	Goal();
	virtual ~Goal();
};

