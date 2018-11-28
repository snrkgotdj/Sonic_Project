#pragma once
#include "Item.h"
class ThunderItem :
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
	ThunderItem();
	virtual ~ThunderItem();
};

