#pragma once
#include "Player.h"
class Tail :
	public Player
{
public:
	virtual void render(HDC _dc);
	virtual void update();
	void init(fPOINT _pos, STAGE_TYPE _type);


private:
	void SwitchAnimation();
	void adjustCol();
	void Jump_Move();
private:
	void Player_Jump();
	void Player_Flying();

public:
	Tail();
	virtual ~Tail();
};

