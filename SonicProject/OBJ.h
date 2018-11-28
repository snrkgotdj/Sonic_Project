#pragma once

class Collider;
class Animator;
class OBJ
{
protected:
	fPOINT pos;
	fPOINT size;

	Collider* collider;
	Animator* Anim;
	float gravity;

	bool m_bAlive;

	OBJ_TYPE m_eOBJ_TYPE;
	

public:
	fPOINT GetPos() { return pos; }
	fPOINT GetSize() { return size; }
	OBJ_TYPE GetOBJType() { return m_eOBJ_TYPE; }
	bool HasCollider() {if (collider) return true; 	else return false; 	}
	Collider* GetCollider() { return collider; }

public:
	void SetPos(fPOINT _point) { pos = _point; }
	void SetXPos(float _Xpos) { pos.x = _Xpos; }
	void SetSize(fPOINT _size) { size = _size; }
	virtual bool isMouseOn(bool _bFixed);
	
public:
	void Die() { m_bAlive = false; }
	bool GetAlive() { return m_bAlive; }

public:
	virtual void render(HDC _dc) = 0;
	virtual void update() = 0;
	virtual void enterCollision(Collider* _other) {};
	virtual void onCollision(Collider* _other) {};
	virtual void exitCollision(Collider* _other) {};

public:
	void Load(FILE* _pFile);
	
public:
	OBJ();
	virtual ~OBJ();
};

