#pragma once
#include "OBJ.h"
class Effect_ItemBomb :
	public OBJ
{
private:


public:
	virtual void render(HDC _dc);
	virtual void update();

public:
	void init(fPOINT _pos);
public:
	Effect_ItemBomb();
	virtual ~Effect_ItemBomb();
};

