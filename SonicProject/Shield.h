#pragma once
#include "OBJ.h"

class Player;

class Shield :
	public OBJ
{

protected:
	HDC m_ShieldTexDC;
	Player* player;
public:
	virtual void render(HDC _dc) = 0;
	virtual void update() = 0;
	virtual void enterCollision(Collider* _other) {};
	virtual void onCollision(Collider* _other) {};
	virtual void exitCollision(Collider* _other) {};

public:
	Shield();
	~Shield();
};