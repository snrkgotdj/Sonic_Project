#include "stdafx.h"
#include "UI.h"
#include "Camera.h"
#include "KeyManager.h"

UI::UI()
	:m_bMouseOn(false)
	,m_pParents(NULL)
	,m_bLbtnClicked(false)
	,m_bRbtnClicked(false)
{
}


UI::~UI()
{
	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		if (m_vecChild[i] != NULL)
		{
			delete m_vecChild[i];
		}
	}
	

}


void UI::AddChild(UI * _child)
{
	m_vecChild.push_back(_child);
	_child->SetParent(this);
}

void UI::ResetChild()
{
	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		if (m_vecChild[i] != NULL)
		{
			delete m_vecChild[i];
			m_vecChild[i] = NULL;
		}
	}
	m_vecChild.clear();
}

void UI::child_update()
{
	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->update();
	}
}

void UI::child_render(HDC _dc)
{
	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->render(_dc);
	}
}

void UI::update()
{
	m_FinalPos = pos;

	if (m_pParents != NULL)
	{
		m_FinalPos = m_pParents->GetFinalPos() + m_FinalPos;
	}
}

void UI::MousejustOn()
{
}

void UI::MouseOn()
{
}

void UI::MouseOut()
{
}

void UI::MouseLbtnClick()
{
}

void UI::MouseLbtnAway()
{
}

void UI::MouseRbtnClick()
{
}

void UI::MouseRbtnAway()
{
}

bool UI::isMouseOn(bool _bFixed)
{
	if (_bFixed == true)
	{
		fPOINT mouse = KeyManager::Manager().GetMouseCur();
		if (m_FinalPos.x < mouse.x && mouse.x <= m_FinalPos.x + size.x
			&&m_FinalPos.y < mouse.y && mouse.y <= m_FinalPos.y + size.y)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	else
	{
		fPOINT mouse = KeyManager::Manager().GetMouseCur();
		mouse = Camera::Cam().GetCamMousePos(mouse);

		if (m_FinalPos.x < mouse.x && mouse.x <= m_FinalPos.x + size.x
			&&m_FinalPos.y < mouse.y && mouse.y <= m_FinalPos.y + size.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

