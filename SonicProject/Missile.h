#pragma once
#include "OBJ.h"

class Player;

class Missile :
	public OBJ
{
private:
	Player* m_pPlayer;
	fPOINT m_ptGradient;
	float m_fSpeed;
	bool m_bFollow;

private:
	void FollowPlayer();
	void MoveMissile();
	void SwitchAnimation();
	void AdjustCol();
	void CreateEffect();

public:
	void init(fPOINT _pos, Player* _player, bool _follow);
	void SetAnimation(const wstring& _Animation);

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other) {};

public:
	Missile();
	~Missile();
};

