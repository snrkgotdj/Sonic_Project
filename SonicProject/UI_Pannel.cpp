#include "stdafx.h"
#include "UI_Pannel.h"
#include "Texture.h"

#include "ResManager.h"
#include "KeyManager.h"


UI_Pannel::UI_Pannel()
	:m_ptMouseOffset{}
{
}


UI_Pannel::~UI_Pannel()
{
}


void UI_Pannel::render(HDC _dc)
{
	fPOINT ptParentPos = {};

	if (m_pParents != NULL)
		ptParentPos = m_pParents->GetFinalPos();

	if (m_pPannelTex != NULL)
	{
		TransparentBlt(_dc
			, (int)pos.x + (int)ptParentPos.x
			, (int)pos.y + (int)ptParentPos.y
			, (int)m_pPannelTex->GetWidth()
			, (int)m_pPannelTex->GetHeight()
			, m_pPannelTex->GetTexDC()
			, 0
			, 0
			, (int)m_pPannelTex->GetWidth()
			, (int)m_pPannelTex->GetHeight()
			, (UINT)RGB(255, 255, 255));
	}

	child_render(_dc);
}

void UI_Pannel::update()
{
	UI::update();
	child_update();
}

void UI_Pannel::init()
{
	m_pPannelTex = ResManager::Manager().LoadTexture(L"\\UI\\Pannel\\Panel.bmp", L"Pannel");

	pos = fPOINT{ 600.f, 60.f };
	size = fPOINT{ m_pPannelTex->GetWidth(), m_pPannelTex->GetHeight() };
}

void UI_Pannel::MouseOn()
{
	if (m_bLbtnClicked == false)
		return;

	fPOINT ptMouse = KeyManager::Manager().GetMouseCur();
	pos = ptMouse + m_ptMouseOffset;

}

void UI_Pannel::MouseLbtnClick()
{
	m_bLbtnClicked = true;

	fPOINT ptMouse = KeyManager::Manager().GetMouseCur();
	m_ptMouseOffset = pos - ptMouse;
}

void UI_Pannel::MouseLbtnAway()
{
	m_bLbtnClicked = false;
}

void UI_Pannel::SetPannelTex()
{

}

