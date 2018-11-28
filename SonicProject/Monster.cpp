#include "stdafx.h"
#include "Monster.h"
#include "Camera.h"
#include "Collider.h"

void Monster::update()
{
	if (HP <= 0)
	{
		pos.x = -1000;
	}
}

void Monster::render(HDC _dc)
{
	fPOINT campos;
	fPOINT diff = Camera::Cam().GetDiff();
	campos.x = pos.x - diff.x;
	campos.y = pos.y - diff.y;
	
	Rectangle(_dc, (int)campos.x - (int)size.x, (int)campos.y - (int)size.y, (int)campos.x + (int)size.y, (int)campos.y + (int)size.y);

	collider->render(_dc);
}

void Monster::init(fPOINT _pos)
{
	pos = _pos;
	size = fPOINT{ 10,10 };
	HP = 5;

	collider = new Collider(this);
	collider->SetType(COL_RECT);
}

void Monster::enterCollision(Collider * _other)
{
	//HP -= 1;
}

void Monster::onCollision(Collider * _other)
{
}

void Monster::exitCollision(Collider * _other)
{
}

Monster::Monster()
{
}


Monster::~Monster()
{
}
