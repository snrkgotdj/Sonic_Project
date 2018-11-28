#pragma once
#include "OBJ.h"
class Effect_Ring :
	public OBJ
{
public:
	virtual void render(HDC _dc);
	virtual void update();

public:
	void init(fPOINT _pos);

public:
	Effect_Ring();
	virtual ~Effect_Ring();
};

