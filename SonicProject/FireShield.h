#pragma once
#include "Shield.h"

class Player;

class FireShield :
	public Shield
{
private:
	float m_fAccTime;
	bool m_bSkillOn;

public:
	void PlayAnimation(const wstring & _strKey);


public:
	void init(Player* _player );

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other) {};
	virtual void exitCollision(Collider* _other) {};

public:
	FireShield();
	~FireShield();
};

