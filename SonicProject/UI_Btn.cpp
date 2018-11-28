#include "stdafx.h"
#include "UI_Btn.h"
#include "KeyManager.h"




void UI_Btn::update()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_AWAY)&& false == m_bMouseOn)
	{
		m_bLbtnClicked = false;
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_AWAY) && false == m_bMouseOn)
	{
		m_bRbtnClicked = false;
	}

	UI::update();
	child_update();
}

UI_Btn::UI_Btn()
	: m_idxButton(0)
{
}


UI_Btn::~UI_Btn()
{
}



