#include "stdafx.h"
#include "Collider.h"
#include "OBJ.h"
#include "Camera.h"
#include "Player.h"

WORD Collider::nextID = 0;

Collider::Collider(OBJ* _Owner)
	:type(COL_END)
	, offset(fPOINT{ 0,0 })
	, ID(nextID++)
{
	Owner = _Owner;
	m_ptCpos = _Owner->GetPos();
	m_ptCsize = _Owner->GetSize();
}

Collider::~Collider()
{
}


void Collider::render(HDC _dc)
{
	fPOINT campos;
	fPOINT diff = Camera::Cam().GetDiff();
	campos.x = m_ptCpos.x - diff.x;
	campos.y = m_ptCpos.y - diff.y;


	HBRUSH OldBrush = (HBRUSH)SelectObject(_dc, GetStockObject(HOLLOW_BRUSH));
	HPEN OldPen = (HPEN)SelectObject(_dc, GetStockObject(DC_PEN));
	SetDCPenColor(_dc, RGB(255, 0, 0));
	if (type == COL_RECT)
		Rectangle(_dc, (int)campos.x - (int)m_ptCsize.x, (int)campos.y - 2 * (int)m_ptCsize.y, (int)campos.x + (int)m_ptCsize.x, (int)campos.y);
	
	else if (type == COL_CIRCLE)
		Ellipse(_dc, (int)campos.x - (int)m_ptCsize.x, (int)campos.y - 2 * (int)m_ptCsize.y, (int)campos.x + (int)m_ptCsize.x, (int)campos.y);

	SelectObject(_dc, (HGDIOBJ)OldPen);
	SelectObject(_dc, (HGDIOBJ)OldBrush);
}

void Collider::update()
{
	m_ptCpos.x = Owner->GetPos().x + offset.x;
	m_ptCpos.y = Owner->GetPos().y - offset.y;

	if(offset.x == 0)
		m_ptCsize = Owner->GetSize();
}


fPOINT Collider::GetPos()
{
	fPOINT CPoint = fPOINT{ m_ptCpos.x, m_ptCpos.y - m_ptCsize.y };
	return CPoint;
}

void Collider::enterCollision(Collider* _other)
{
	Owner->enterCollision(_other);
}

void Collider::onCollision(Collider* _other)
{
	Owner->onCollision(_other);
}

void Collider::exitCollision(Collider* _other)
{
	Owner->exitCollision(_other);
}

