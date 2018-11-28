#pragma once
#include "OBJ.h"
class Ring :
	public OBJ
{
private:
	fPOINT m_ptVector;


private:
	COLORREF m_FloorColor;
	COLORREF m_WallColor;
	HDC Col_DC;

private:
	bool m_bSpitedRing;
	bool m_bOnGround;

	int m_iGravity;
	bool m_bCanEat;
	float m_fRadian;
	float m_fSpeed;

private:
	float m_fAccRender;
	float m_fAccMaintain;
	bool m_bRenderChange;

private:
	void RanderChange();
	void MaintainRing();
	void RingMove();
	void FollowPlayer();

private:
	void Gravity();
	void CheckWall();

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
	Ring();
	Ring(bool _Spit, float _Radian, COLORREF _floorColor, COLORREF _wallColor, STAGE_TYPE _type);
	virtual ~Ring();
};

