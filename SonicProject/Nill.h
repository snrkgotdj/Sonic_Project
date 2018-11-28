#pragma once
#include "OBJ.h"
class Nill :
	public OBJ
{
protected:
	HDC m_NillDC;


private:
	void SpitOutRing(Collider * _other);
	float getRandomNumber(float min, float max);

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other) {};

public:
	void init(fPOINT _pos);
	void init();

public:
	Nill();
	virtual ~Nill();
};

