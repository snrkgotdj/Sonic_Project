#pragma once
#include "OBJ.h"
class MouseObj :
	public OBJ
{
private:
	Texture* m_pTex;
	int m_idxTile;
	fPOINT m_ptOffset;
public:
	void SetTileIdx(int _idxTile) { m_idxTile = _idxTile; }
	void SetOffset(fPOINT _offset) { m_ptOffset = _offset; }
	int GetTileIdx() { return m_idxTile; }
	

public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void init();

public:
	MouseObj();
	~MouseObj();
};

