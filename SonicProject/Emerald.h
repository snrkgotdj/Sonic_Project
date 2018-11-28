#pragma once
#include "OBJ.h"
class Emerald :
	public OBJ
{
public:
	void init(fPOINT _pos);

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
public:
	Emerald();
	~Emerald();
};

