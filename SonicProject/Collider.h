#pragma once

class OBJ;

class Collider
{
private:
	static WORD nextID;

private:
	WORD ID;
	OBJ* Owner;
	COL_TYPE type;
	fPOINT offset;
	fPOINT m_ptCpos;
	fPOINT m_ptCsize;
public:
	void render(HDC _dc);
	void update();
	void SetType(COL_TYPE _type) { type = _type; }
	void SetOffset(fPOINT _offset) { offset = _offset; }
	void SetSize(fPOINT _size) { m_ptCsize = _size; }

	OBJ* GetOwner() { return Owner; }
	WORD GetID() { return ID; }
	
	fPOINT GetPos();
	fPOINT GetSize() { return m_ptCsize; }
	COL_TYPE GetType() { return type; }

public:
	void enterCollision(Collider* _other);
	void onCollision(Collider* _other);
	void exitCollision(Collider* _other);

public:
	Collider(OBJ* _Owner);
	~Collider();
};
