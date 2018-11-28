#include "stdafx.h"
#include "UIManager.h"
#include "StageManager.h"
#include "Stage.h"
#include "KeyManager.h"
#include "UI.h"
#include "ResManager.h"
#include "Texture.h"
#include "PathManager.h"
#include "Player.h"
#include "TimeManager.h"
#include "SoundManager.h"



UIManager::UIManager()
	:m_iSec(0)
	,m_iMin(0)
	, m_iHour(0)
	, m_iTenHour(0)
	, m_fAccTime(0.f)
	, m_iLife(3)
	, m_bVictory(false)
	, m_iScore(0)
	, m_iTimeBonus(3300)
	, m_iRingBonus(2600)
	, m_fAccVictory(0.f)
	, m_iTotal(0)
	, m_LifeTex(NULL)
{
} 


UIManager::~UIManager()
{
	delete m_FontTex;
	delete m_LifeTex;
	delete m_ScoreTex;
	delete m_LifeFont;
	delete m_VicToryFont;
}

void UIManager::SetTime(int _hour, int _min, int _sec)
{
	m_iHour = _hour;
	m_iMin = _min;
	m_iSec = _sec;
	m_iTenHour = 0;
}

void UIManager::CharactorLifeTexLoad()
{
	wstring strpath = PathManager::GetResPath();

	if (m_LifeTex != NULL)
	{
		delete m_LifeTex;
		m_LifeTex = NULL;
	}

	if (StageManager::Manager().GetCharactorMode() == KNUCKLE_MODE)
	{
		strpath += L"\\UI\\Life\\Knuckle_Life.bmp";
		m_LifeTex = m_FontTex->Load(strpath);
	}
	else if (StageManager::Manager().GetCharactorMode() == SONIC_MODE)
	{
		strpath += L"\\UI\\Life\\Sonic_Life.bmp";
		m_LifeTex = m_FontTex->Load(strpath);
	}
	else if (StageManager::Manager().GetCharactorMode() == TAIL_MODE)
	{
		strpath += L"\\UI\\Life\\Tail_Life.bmp";
		m_LifeTex = m_FontTex->Load(strpath);
	}

}

void UIManager::update()
{
	Stage* CurStage = StageManager::Manager().GetCurStage();
	vector<OBJ*> vecUI = CurStage->GetListObj(Obj_UI);

	fPOINT MousePos = KeyManager::Manager().GetMouseCur();
	
	for (int i = 0; i < vecUI.size(); ++i)
	{
		UI* pUI = (UI*)vecUI[i];
		MouseCheck(pUI);
	}
	MouseClickCheck(vecUI);

	if(m_bVictory == false)
		TimeCheck();

	else if (m_bVictory == true && m_iTimeBonus !=0)
	{
		m_fAccVictory += DT;

		if (m_fAccVictory >= 3)
		{
			m_iScore -= (int)(1600 * DT);
			m_iTimeBonus -= (int)(1600 * DT);
			m_iRingBonus -= (int)(1600 * DT);

			if (m_iTimeBonus <= 0)
			{
				m_iTotal = 3300 + 3200 + 2600;

				m_iScore = 0;
				m_iTimeBonus = 0;
				m_iRingBonus = 0;

				SoundManager::Manager()->PlaySoundW(L"Sound_CashRegister",false);
				m_fAccVictory = 0.f;
				
			}
			
		}
	}

	else if (m_bVictory == true && m_iTimeBonus == 0)
	{
		m_fAccVictory += DT;

		if (m_fAccVictory >= 3)
		{
			m_bVictory = false;
			m_iHour = 0;
			m_iMin = 0;
			m_iSec = 0;

			StageManager::Manager().ChangeStage(STAGE_01);
		}
	}


	if (true == KeyManager::Manager().GetKeyState(KEY_L, STATE_TAB))
	{
		m_iLife += 1;
	}

	
}

void UIManager::init()
{
	wstring strpath = PathManager::GetResPath();
	strpath += L"\\UI\\Pont\\Font_Score.bmp";
	m_FontTex = m_FontTex->Load(strpath);

	strpath = PathManager::GetResPath();
	strpath += L"\\UI\\Score\\Score.bmp";
	m_ScoreTex = m_ScoreTex->Load(strpath);

	strpath = PathManager::GetResPath();
	strpath += L"\\UI\\Pont\\Victory_Pont.bmp";
	m_VicToryFont = m_VicToryFont->Load(strpath);
	

	strpath = PathManager::GetResPath();
	if (StageManager::Manager().GetCharactorMode() == KNUCKLE_MODE)
	{
		strpath += L"\\UI\\Life\\Knuckle_Life.bmp";
		m_LifeTex = m_FontTex->Load(strpath);
	}
	else if (StageManager::Manager().GetCharactorMode() == SONIC_MODE)
	{
		strpath += L"\\UI\\Life\\Sonic_Life.bmp";
		m_LifeTex = m_FontTex->Load(strpath);
	}
	else if (StageManager::Manager().GetCharactorMode() == TAIL_MODE)
	{
		strpath += L"\\UI\\Life\\Tail_Life.bmp";
		m_LifeTex = m_FontTex->Load(strpath);
	}

	strpath = PathManager::GetResPath();
	strpath += L"\\UI\\Pont\\Font_Life.bmp";
	m_LifeFont = m_LifeFont->Load(strpath);
}

void UIManager::render(HDC _dc)
{
	TransparentBlt(_dc, 70, 40, 180, 155, m_ScoreTex->GetTexDC(), 0, 0, 180, 155, RGB(255, 0, 255));

	ScoreFontRender(_dc, 280, 152 ,((Player*)(StageManager::Manager().GetCurStage()->GetListObj(Obj_PLAYER)[0]))->GetRingCnt());

	TransparentBlt(_dc, 175, 100, 21, 33, m_FontTex->GetTexDC(), 21 * m_iTenHour, 0, 21, 33, RGB(255, 0, 255));
	TransparentBlt(_dc, 200, 100, 21, 33, m_FontTex->GetTexDC(), 21 * m_iHour, 0, 21, 33, RGB(255, 0, 255));
	TransparentBlt(_dc, 255, 100, 21, 33, m_FontTex->GetTexDC(), 21 * m_iMin, 0, 21, 33, RGB(255, 0, 255));
	TransparentBlt(_dc, 280, 100, 21, 33, m_FontTex->GetTexDC(), 21 * m_iSec, 0, 21, 33, RGB(255, 0, 255));

	ScoreFontRender(_dc, 280, 50, m_iScore);

	TransparentBlt(_dc, 40, WindowSizeY - 60, 130, 46, m_LifeTex->GetTexDC(), 0, 0, 130, 46, RGB(255, 0, 255));

	LifeFontRender(_dc, 150, WindowSizeY - 35);


	//Victory Score
	if (m_bVictory == true)
	{
		VictoryRender(_dc, 260, 210);
	}
}


void UIManager::MouseCheck(UI* _pUI)
{
	bool bMouseOn = _pUI->isMouseOn(true);

	if (bMouseOn == true)
	{
		if (_pUI->m_bMouseOn)
		{
			_pUI->MouseOn();
		}

		else
		{
			_pUI->MousejustOn();
		}
	}

	else
	{
		if (_pUI->m_bMouseOn)
		{
			_pUI->MouseOut();
		}
	}
	_pUI->m_bMouseOn = bMouseOn;
}

void UIManager::MouseClickCheck(vector<OBJ*> _vecUI)
{
	if (false == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && false == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_AWAY))
	{
		return;
	}

	UI* pUI = NULL;
	
	vector<OBJ*>::iterator iter = _vecUI.begin();
	vector<OBJ*>::iterator targetiter = _vecUI.end();

	for (iter; iter != _vecUI.end(); ++iter)
	{
		pUI = (UI*)(*iter);

		if (true == pUI->m_bMouseOn)
		{
			targetiter = iter;
		}
	}

	if (targetiter != _vecUI.end())
	{
		static list<UI*> listUI;

		listUI.clear();
		listUI.push_back((UI*)(*targetiter));
		UI* pTargetUI = (UI*)(*targetiter);
		
		while (true)
		{
			if (true == listUI.empty())
				break;

			UI* pUI = listUI.front();
			listUI.pop_front();

			const vector<UI*>& vecChild = pUI->GetChild();
			for (int i = 0; i < vecChild.size(); ++i)
			{
				listUI.push_back(vecChild[i]);
			}

			if (true == pUI->isMouseOn(true))
				pTargetUI = pUI;
		}

		

		if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB))
		{
			pTargetUI->MouseLbtnClick();
		}

		else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_AWAY))
		{
			pTargetUI->MouseLbtnAway();
		}
		OBJ* pParentUI = (*targetiter);
		_vecUI.erase(targetiter);
		_vecUI.push_back(pParentUI);
	}
}

void UIManager::ScoreFontRender(HDC _dc, int _x, int _y , int _number)
{
	if (_number < 10)
	{
		TransparentBlt(_dc, _x, _y, 21, 33, m_FontTex->GetTexDC(), 21*_number, 0, 21, 33, RGB(255, 0, 255));
	}

	else if (_number >= 10 && _number < 100)
	{
		TransparentBlt(_dc, _x - 25, _y, 21, 33, m_FontTex->GetTexDC(), 21 * (_number / 10), 0, 21, 33, RGB(255, 0, 255));
		TransparentBlt(_dc, _x, _y, 21, 33, m_FontTex->GetTexDC(), 21 * (_number % 10), 0, 21, 33, RGB(255, 0, 255));
	}

	else if (_number >= 100 && _number < 1000)
	{
		TransparentBlt(_dc, _x - 50, _y, 21, 33, m_FontTex->GetTexDC(), 21 * (_number / 100), 0, 21, 33, RGB(255, 0, 255));
		TransparentBlt(_dc, _x - 25, _y, 21, 33, m_FontTex->GetTexDC(), 21 * ((_number % 100)/10), 0, 21, 33, RGB(255, 0, 255));
		TransparentBlt(_dc, _x, _y, 21, 33, m_FontTex->GetTexDC(), 21 * (_number % 10), 0, 21, 33, RGB(255, 0, 255));
	}

	else if (_number >= 1000)
	{
		TransparentBlt(_dc, _x - 75, _y, 21, 33, m_FontTex->GetTexDC(), 21 * (_number / 1000), 0, 21, 33, RGB(255, 0, 255));
		TransparentBlt(_dc, _x - 50, _y, 21, 33, m_FontTex->GetTexDC(), 21 * ((_number % 1000)/100), 0, 21, 33, RGB(255, 0, 255));
		TransparentBlt(_dc, _x - 25, _y, 21, 33, m_FontTex->GetTexDC(), 21 * ((_number % 100) / 10), 0, 21, 33, RGB(255, 0, 255));
		TransparentBlt(_dc, _x, _y, 21, 33, m_FontTex->GetTexDC(), 21 * (_number % 10), 0, 21, 33, RGB(255, 0, 255));
	}
}


void UIManager::LifeFontRender(HDC _dc, int _x, int _y)
{
	if (m_iLife < 10)
	{
		TransparentBlt(_dc, _x, _y, 24, 22, m_LifeFont->GetTexDC(), 24 * (m_iLife), 0, 24, 22, RGB(255, 0, 255));
	}

	else if (m_iLife >= 10 && m_iLife < 100)
	{
		TransparentBlt(_dc, _x - 25, _y, 24, 22, m_LifeFont->GetTexDC(), 24 * (m_iLife / 10), 0, 24, 22, RGB(255, 0, 255));
		TransparentBlt(_dc, _x, _y, 24, 22, m_LifeFont->GetTexDC(), 24 * (m_iLife % 10), 0, 24, 22, RGB(255, 0, 255));
	}

	else if (m_iLife >= 100 && m_iLife < 1000)
	{
		TransparentBlt(_dc, _x - 50, _y, 24, 22, m_LifeFont->GetTexDC(), 24 * (m_iLife / 100), 0, 24, 22, RGB(255, 0, 255));
		TransparentBlt(_dc, _x - 25, _y, 24, 22, m_LifeFont->GetTexDC(), 24 * ((m_iLife % 100) / 10), 0, 24, 22, RGB(255, 0, 255));
		TransparentBlt(_dc, _x, _y, 24, 22, m_LifeFont->GetTexDC(), 24 * (m_iLife % 10), 0, 24, 22, RGB(255, 0, 255));
	}
}

void UIManager::VictoryRender(HDC _dc, int _x, int _y)
{
	TransparentBlt(_dc, _x, _y, 170, 164, m_VicToryFont->GetTexDC(), 0, 0, 170, 164, RGB(255, 0, 255));

	ScoreFontRender(_dc, _x + 440, _y -10, m_iScore);

	ScoreFontRender(_dc, _x + 440, _y + 25, m_iTimeBonus);

	ScoreFontRender(_dc, _x + 440, _y + 60, m_iRingBonus);


	ScoreFontRender(_dc, 700, _y + 130, m_iTotal);
}

void UIManager::TimeCheck()
{
	m_fAccTime += DT;

	if (m_fAccTime >= 1)
	{
		m_iSec += 1;
		m_fAccTime = 0.f;
	}

	if (m_iSec >= 10)
	{
		m_iMin += 1;
		m_iSec = 0;
	}

	if (m_iMin >= 6)
	{
		m_iHour += 1;
		m_iMin = 0;
	}

	if (m_iHour >= 10)
	{
		m_iTenHour += 1;
		m_iHour = 0;
	}
}
