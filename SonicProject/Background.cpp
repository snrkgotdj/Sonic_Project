#include "stdafx.h"
#include "Background.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "ResManager.h"
#include "TimeManager.h"

// jisu

void Background::init()
{
	BackTex = ResManager::Manager().LoadTexture(L"\\Logo\\Background.bmp", L"LOGO_back");
	LogoWing = ResManager::Manager().LoadTexture(L"\\Logo\\Wing.bmp", L"LOGO_WING");
	pTex = ResManager::Manager().LoadTexture(L"\\Logo\\Charactor.bmp", L"LOGO_TEX");
	
	m_fAccTime = 0.f;
	positionY = -200.f;


	Charactor = new Animator;
	Charactor->AddAnimation(L"Logo_Anim", pTex, fPOINT{ 0,0 }, 1, fPOINT{200,160 }, 8, 0.15f, RGB(255, 0, 255),0);
	
	Charactor->PlayAnimation(L"Logo_Anim");
}

void Background::render(HDC _dc)
{
	BitBlt(_dc, 0, 0, WindowSizeX, WindowSizeY, BackTex->GetTexDC(), 0, 0, SRCCOPY);
	
	if (m_fAccTime >= 0.9)
	{
		TransparentBlt(_dc
			, (int)(WindowSizeX / 2 - LogoWing->GetWidth() / 2)
			, (int)positionY
			, (int)LogoWing->GetWidth()
			, (int)LogoWing->GetHeight()
			, LogoWing->GetTexDC()
			, 0
			, 0
			, (int)LogoWing->GetWidth()
			, (int)LogoWing->GetHeight()
			, (UINT)RGB(255, 0, 255));
	}
	
	if (m_fAccTime >= 3.4)
	{
		Charactor->render(_dc, fPOINT{ WindowSizeX/2 , WindowSizeY/2 }, 7);
	}
}

void Background::update()
{
	m_fAccTime += DT;

	if (positionY <= (WindowSizeY / 2 - LogoWing->GetHeight() / 2) && m_fAccTime >= 0.9)
	{
		positionY += DT * 200;
	}
}

void Background::Clear()
{
	if (Charactor != NULL)
	{
		delete Charactor;
		Charactor = NULL;
	}
}

Background::Background()
	:BackTex(NULL)
	,LogoWing(NULL)
	, Charactor(NULL)
	,pTex(NULL)
	, m_fAccTime(0.f)
	, positionY(-200.f)
{
}


Background::~Background()
{
	BackTex = NULL;
	Clear();
}
