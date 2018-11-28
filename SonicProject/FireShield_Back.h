#pragma once
#include "Shield.h"
class FireShield_Back :
	public Shield
{
private:
	bool m_bRendOn;

	bool m_bSkillOn;
	float m_fAccTime;

public:
	void SetRendOn(bool _off) { m_bRendOn = _off; m_bSkillOn = true; }

public:
	void init(Player* _player);

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other) {};
	virtual void exitCollision(Collider* _other) {};

public:
	FireShield_Back();
	virtual ~FireShield_Back();
};

