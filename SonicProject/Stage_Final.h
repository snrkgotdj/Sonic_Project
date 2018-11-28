#pragma once
#include "Stage.h"

class Player;
class Final_Boss_00;
class Final_Boss_01;


class Stage_Final :
	public Stage
{
private:
	fPOINT m_ptMapPos;
	Final_Boss_00* m_pBoss;
	Final_Boss_01* m_pBoss_01;
	Player* m_pPlayer;

	float m_fRingCreateTime;

	float m_fMissileCreateTime;
	float m_fMissileCreateTime_01;


	float m_fStone_00_CreateTime;
	float m_fStone_01_CreateTime;
	float m_fStone_02_CreateTime;
	bool m_bBossON;
	bool m_bBossON_01;



private:
	void LoadMap();
	void SetColPair();
	float getRandomNumber(float min, float max);

private:
	void CreatePlayer();
	void CreateBoss();
	void CreateMissile();
	void CreateStone();
	void CreateBoss_01();
	void CreateRing();

public:
	void SetBossOn_01(bool _on) { m_bBossON_01 = _on; }
	void SetBossOn(bool _on) { m_bBossON = _on; }

public:
	virtual void enter();
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();

public:
	Stage_Final();
	virtual ~Stage_Final();
};

