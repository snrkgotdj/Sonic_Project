#pragma once
#include "OBJ.h"
class OBJ_Box :
	public OBJ
{
private:
	int m_iMove;
	float m_fSpeed;

	COL_DIRECT m_ColDirect;

private:
	void Move_Top();
	void Move_Right();
	void Move_Bottom();
	void Move_Left();


public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other);

public:
	void init(fPOINT _pos, int _move);
	


public:
	OBJ_Box();
	virtual ~OBJ_Box();
};

