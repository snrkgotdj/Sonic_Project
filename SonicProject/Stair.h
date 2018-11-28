#pragma once
#include "OBJ.h"
class Stair :
	public OBJ
{
private:
	MOVE_STATE m_eMoveState;

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other);

public:
	void init(fPOINT _pos, MOVE_STATE _state);


public:
	Stair();
	virtual ~Stair();
};

