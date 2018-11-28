#pragma once
#include "OBJ.h"
class Monster :
	public OBJ
{
private:
	int HP;

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void init(fPOINT _pos);

public:
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other);
public:
	Monster();
	virtual ~Monster();
};

