#pragma once
#include "OBJ.h"
class Box :
	public OBJ
{
private:
	Texture * pTex;


public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void init();
public:
	Box();
	~Box();
};

