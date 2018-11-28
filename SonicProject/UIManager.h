#pragma once
#include "global.h"

class UI;
class OBJ;
class Texture;

class UIManager
{
private:
	Texture* m_FontTex;
	Texture* m_ScoreTex;
	Texture* m_LifeTex;
	Texture* m_LifeFont;

private:
	Texture* m_VicToryFont;

private:
	int m_iLife;
	bool m_bVictory;

	int m_iScore;
	int m_iTimeBonus;
	int m_iRingBonus;
	int m_iTotal;

	float m_fAccVictory;


private:
	int m_iSec;
	int m_iMin;
	int m_iHour;
	int m_iTenHour;
	float m_fAccTime;

private:
	void MouseCheck(UI* _pUI);
	void MouseClickCheck(vector<OBJ*> _vecUI);

public:
	void ScoreFontRender(HDC _dc, int _x, int _y, int _number);
	void LifeFontRender(HDC _dc, int _x, int _y);
	void VictoryRender(HDC _dc, int _x, int _y);
	void TimeCheck();

public:
	Texture* GetFontTex() { return m_FontTex; }
	int GetHour() { return m_iHour; }
	int GetMin() { return m_iMin; }
	int GetSec() { return m_iSec; }

public:
	void SetVictory(bool _victory) { m_bVictory = _victory; }
	void SetTime(int _hour, int _min, int _sec);

	void PlusLife(int _life) { m_iLife += _life; }
	void PlusScore(int _score) { m_iScore += 20; }


public:
	void CharactorLifeTexLoad();


public:
	void update();
	void init();
	void render(HDC _dc);

public:
	static UIManager& Manager()
	{
		static UIManager inst;
		return inst;
	}

private:
	UIManager();
	~UIManager();
};

