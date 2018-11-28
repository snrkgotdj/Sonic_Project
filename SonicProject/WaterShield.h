#pragma once
#include "Shield.h"
class WaterShield :
	public Shield
{
private:
	bool m_bSkillOn;
	float m_fAccTime;

private:
	float m_fAccRender;
	bool m_bRenderChange;
	void RanderChange();

public:
	void PlayAnimation(const wstring & _strKey);

public:
	void init(Player* _player);

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other) {};
	virtual void exitCollision(Collider* _other) {};

public:
	WaterShield();
	virtual ~WaterShield();
};

