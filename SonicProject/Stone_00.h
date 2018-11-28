#pragma once
#include "Stone.h"
class Stone_00 :
	public Stone
{
private:
	float m_fSpeed;

public:
	void init(fPOINT _pos);

public:
	virtual void update();
	virtual void enterCollision(Collider* _other);

public:
	Stone_00();
	virtual ~Stone_00();
};

