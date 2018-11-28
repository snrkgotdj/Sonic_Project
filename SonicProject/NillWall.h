#pragma once
#include "OBJ.h"

class Collider;

class NillWall :
	public OBJ
{
private:
	MOVE_STATE m_eMoveState;
	Collider* m_NillCol;

	fPOINT m_ptOriginPos;

	bool m_bMove;

private:
	void CheckNill();

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other);

public:
	void init(fPOINT _pos, MOVE_STATE _state);
	void init(MOVE_STATE _state);

public:
	NillWall();
	virtual ~NillWall();
};

