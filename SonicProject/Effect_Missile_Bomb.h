#pragma once
#include "OBJ.h"

class Effect_Missile_Bomb:
	public OBJ
{
public:
	virtual void render(HDC _dc);
	virtual void update();

public:
	void init(fPOINT _pos);

public:
	Effect_Missile_Bomb();
	~Effect_Missile_Bomb();
};

