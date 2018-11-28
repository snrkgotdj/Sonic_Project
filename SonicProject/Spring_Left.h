#pragma once
#include "OBJ.h"

class Texture;

class Spring_Left :
	public OBJ
{
private:
	Texture* TLeftSpring;
	float m_fSpringPower;
	float m_fAccTime;

	bool m_bOnCollision;

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other);

public:
	void init(fPOINT _pos, float _Power);
	void init();

public:
	Spring_Left();
	~Spring_Left();
};
