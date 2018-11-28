#pragma once
#include "OBJ.h"

class Player;

class Effect_Break :
	public OBJ
{
private:
	Player* player;

public:
	virtual void render(HDC _dc);
	virtual void update();

public:
	void init(Player* _player);

public:
	Effect_Break();
	virtual ~Effect_Break();
};

