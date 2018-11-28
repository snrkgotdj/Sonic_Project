#pragma once
#include "Item.h"
class RingItem :
	public Item
{
public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other);

public:
	void init(fPOINT _pos);
	void init();

public:
	RingItem();
	virtual ~RingItem();
};

