#pragma once
#include "OBJ.h"
class UI :
	public OBJ
{
protected:
	HDC m_GameUI;

protected:
	bool m_bMouseOn;
	bool m_bLbtnClicked;
	bool m_bRbtnClicked;

	UI* m_pParents;
	vector<UI*> m_vecChild;

	fPOINT m_FinalPos;

public:
	bool isParent() { if (NULL != m_pParents) return true; else return false; }
	void SetParent(UI* _parents) { m_pParents = _parents; }
	void AddChild(UI* _child);
	fPOINT GetFinalPos() { return m_FinalPos; }
	const vector<UI*>& GetChild() { return m_vecChild; }
	void ResetChild();

protected:
	void child_update();
	void child_render(HDC _dc);

public:
	virtual void render(HDC _dc) = 0;
	virtual void update();
	virtual void init() = 0;

public:
	virtual void MousejustOn();
	virtual void MouseOn();
	virtual void MouseOut();

	virtual void MouseLbtnClick();
	virtual void MouseLbtnAway();
					   
	virtual void MouseRbtnClick();
	virtual void MouseRbtnAway();
	virtual bool isMouseOn(bool _bFixed);

public:
	

public:
	UI();
	~UI();

	friend class UIManager;
};

