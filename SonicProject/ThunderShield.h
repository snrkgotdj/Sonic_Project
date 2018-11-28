#pragma once
#include "Shield.h"
class ThunderShield :
	public Shield
{
public:
	void init(Player* _player);

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other) {};
	virtual void exitCollision(Collider* _other) {};

public:
	ThunderShield();
	virtual ~ThunderShield();
};

