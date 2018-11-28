#pragma once
#include "OBJ.h"


class Tile :
	public OBJ
{
private:
	Texture* pTex;
	int		 idxTile;

public:
	void SetIdx(int _idx) { idxTile = _idx; }

	void Save(FILE* _pFile);
	void Load(FILE* _pFile);
public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void init();

	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other);

public:
	Tile();
	virtual ~Tile();
};

