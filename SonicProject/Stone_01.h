#pragma once
#include "Stone.h"
class Stone_01 :
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
	Stone_01();
	virtual ~Stone_01();
};

