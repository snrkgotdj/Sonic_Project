#pragma once
#include "Stage.h"
#include "StartBack.h"


class Texture;


class Stage_Start :
	public Stage
{
private:
	StartBack Startback;
	HDC m_BackCover;

	

private:
	void CreateOBJ();
	void CreateSpring();
	void CreatePlayer();
	void CreateItem();
	void CreateNill();
	void CreateRing();
	void CreateUI();
	void SetColPair();

public:
	virtual void enter();
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();

public:
	Stage_Start();
	virtual ~Stage_Start();
};