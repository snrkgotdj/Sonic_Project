#include "stdafx.h"
#include "Btn_TC.h"
#include "ResManager.h"
#include "Texture.h"
#include "Resource.h"
#include "Stage_Maptool.h"
#include "StageManager.h"
#include "KeyManager.h"



void Btn_TC::MouseJustOn()
{
}

void Btn_TC::MouseOn()
{
}

void Btn_TC::MouseOut()
{
}

void Btn_TC::MouseLbtnClick()
{
	m_bLbtnClicked = true;
	
}

void Btn_TC::MouseLbtnAway()
{
	if (m_bLbtnClicked == false)
		return;

	

	m_bLbtnClicked = false;
}

Btn_TC::Btn_TC()
{
}


Btn_TC::~Btn_TC()
{
}

void Btn_TC::init()
{

	/*Texture* pTex = ResManager::Manager().LoadTexture(L"\\UI\\BUTTON\\TileCount.bmp", L"Button");
	vecBtnTex.push_back(pTex);

	pos.x = pTex->GetWidth();
	pos.y = pTex->GetHeight();

	size = fPOINT{ 140,40 };*/
}

void Btn_TC::update()
{
	/*UI_Btn::update();*/
}

void Btn_TC::render(HDC _dc)
{
	//fPOINT ptParentPos = {};

	//if (m_pParents != NULL)
	//	ptParentPos = m_pParents->GetFinalPos();


	//TransparentBlt(_dc
	//	, pos.x + ptParentPos.x
	//	, pos.y + ptParentPos.y
	//	, vecBtnTex[m_idxButton]->GetWidth()
	//	, vecBtnTex[m_idxButton]->GetHeight()
	//	, vecBtnTex[m_idxButton]->GetTexDC()
	//	, 0
	//	, 0
	//	, vecBtnTex[m_idxButton]->GetWidth()
	//	, vecBtnTex[m_idxButton]->GetHeight()
	//	, RGB(255, 255, 255));

	//child_render(_dc);
}
