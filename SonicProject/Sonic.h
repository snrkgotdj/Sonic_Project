#pragma once
#include "Player.h"

class Animator;

class Sonic :
	public Player
{
private:
	fPOINT m_ptOldPos_01;
	fPOINT m_ptOldPos_02;
	fPOINT m_ptOldPos_03;
	fPOINT m_ptOldPos_04;
	fPOINT m_ptOldPos_05;
	fPOINT m_ptOldPos_06;
	fPOINT m_ptOldPos_07;
	fPOINT m_ptOldPos_08;
	fPOINT m_ptOldPos_09;
	fPOINT m_ptOldPos_10;
	fPOINT m_ptOldPos_11;
	fPOINT m_ptOldPos_12;
	fPOINT m_ptOldPos_13;
	fPOINT m_ptOldPos_14;
	fPOINT m_ptOldPos_15;
	fPOINT m_ptOldPos_16;
	fPOINT m_ptOldPos_17;
	fPOINT m_ptOldPos_18;
	fPOINT m_ptOldPos_19;


private:
	Animator* m_WhiteAnim;
	Animator* m_SuperEffect;

private:
	float m_fAccRender;
	float m_fSuperHittedTime;
	float m_fSuperDashTime;
	float m_fSuperSonicTime;

	bool m_bRenderChange;
	bool m_bSuperDashOn;

public:
	void RanderChange();


public:
	virtual void render(HDC _dc);
	virtual void update();
	void init(fPOINT _pos, STAGE_TYPE _type);

private:
	void RendAfterImage(HDC _dc);
	void CheckSuperSonicTime();


private:
	void Player_Jump();
	void Player_TransForm();
	void Player_FinalStage();

	void SwitchAnimation();
	void SwitchSuperAnimation();
	void SetOldPos();

private:
	void Player_FireSkill();
	void Player_WaterSkill();
	void Player_ThunderSkill();

public:
	Sonic();
	virtual ~Sonic();
};

