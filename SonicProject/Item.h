#pragma once
#include "OBJ.h"

class Texture;

class Item :
	public OBJ
{
protected:
	HDC m_TexDC;
	HDC m_NomalDC;
	COL_DIRECT m_ColDirect;

protected:
	float m_fAccTime;

public:
	virtual void render(HDC _dc);
	virtual void update() = 0;
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other);
	

public:
	Item();
	virtual ~Item();
};

