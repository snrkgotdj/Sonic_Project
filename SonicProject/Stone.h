#pragma once
#include "OBJ.h"
class Stone :
	public OBJ
{
protected:
	float getRandomNumber(float min, float max);

public:
	virtual void render(HDC _dc);
	virtual void update() = 0;
	virtual void enterCollision(Collider* _other);

public:
	Stone();
	~Stone();
};

