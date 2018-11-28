#pragma once
#include "OBJ.h"
class Effect_Spin :
	public OBJ
{
public:
	virtual void render(HDC _dc);
	virtual void update();

public:
	void init(fPOINT _pos, bool _dir);

public:
	Effect_Spin();
	~Effect_Spin();
};

