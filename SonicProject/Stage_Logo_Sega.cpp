#include "stdafx.h"
#include "Stage_Logo_Sega.h"
#include "SoundManager.h"
#include "ResManager.h"
#include "Texture.h"
#include "Animator.h"
#include "TimeManager.h"
#include "StageManager.h"
#include "UIManager.h"
#include "Camera.h"


void Stage_Logo_Sega::enter()
{
	StageManager::Manager().SetCurStageType(STAGE_LOGO);

	Camera::Cam().init(fPOINT{0 ,0 }, NULL);

	UIManager::Manager().SetTime(0, 0, 0);

	ResManager::Manager().LoadTexture(L"\\Logo\\SEGA_LOGO.bmp", L"LOGO_SEGA");

	pAnim = new Animator;

	pAnim->AddAnimation(L"Logo_Sega", ResManager::Manager().FindTexture(L"LOGO_SEGA"), fPOINT{ 0,0 }, 1, fPOINT{ 1024,600 }, 24, 0.03, RGB(255, 0, 255), 1);
	
	pAnim->PlayAnimation(L"Logo_Sega",0);

	SoundManager::Manager()->PlaySoundW(L"Sound_Intro", false);
}

void Stage_Logo_Sega::exit()
{
	m_fAccTime = 0.f;

	if (pAnim != NULL)
	{
		delete pAnim;

		pAnim = NULL;
	}
		
}

void Stage_Logo_Sega::render(HDC _dc)
{
	pAnim->render(_dc, fPOINT{ 100,WindowSizeY/2 });
}

void Stage_Logo_Sega::update()
{
	m_fAccTime += DT;

	if (m_fAccTime >= 2.6)
	{
		StageManager::Manager().ChangeStage(STAGE_LOGO);
	}
}

Stage_Logo_Sega::Stage_Logo_Sega()
	: m_fAccTime(0.f)
	, pAnim(NULL)
{
}


Stage_Logo_Sega::~Stage_Logo_Sega()
{
	if(pAnim != NULL)
		delete pAnim;
}
