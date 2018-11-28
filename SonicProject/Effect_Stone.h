#pragma once
#include "OBJ.h"
class Effect_Stone :
	public OBJ
{
private:
	float m_fAccTime;

	float m_fSpeed;
	bool m_bDir;

public:
	void init(fPOINT _pos, bool _Dir);

public:
	virtual void render(HDC _dc);
	virtual void update();

public:
	Effect_Stone();
	virtual ~Effect_Stone();
};

