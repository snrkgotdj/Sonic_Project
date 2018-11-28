#pragma once
#include "Player.h"
class Knuckle :
	public Player
{
public:
	virtual void render(HDC _dc);
	virtual void update();
	void init(fPOINT _pos, STAGE_TYPE _type);

public:
	Knuckle();
	virtual ~Knuckle();
};

