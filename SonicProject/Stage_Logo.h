#pragma once
#include "Stage.h"
#include "Bullet.h"
#include "Background.h"
class OBJ;
class Player;
class Bullet;
class Texture;
class Animator;

class Stage_Logo :
	public Stage
{
private:
	Background background;

public:
	virtual void enter();
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();
public:
	Stage_Logo();
	virtual ~Stage_Logo();
};

