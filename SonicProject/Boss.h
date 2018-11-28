#pragma once
#include "OBJ.h"
class Boss :
	public OBJ
{






public:
	virtual void render(HDC _dc) = 0;
	virtual void update() = 0;
	virtual void enterCollision(Collider* _other) {};
	virtual void onCollision(Collider* _other) {};
	virtual void exitCollision(Collider* _other) {};
protected:
	Boss();
	virtual ~Boss();
};

