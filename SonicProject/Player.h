#pragma once
#include "OBJ.h"

class Animator;

class Player :
	public OBJ
{
	friend class Shield;
protected:
	bool m_bSuperSonic;
	bool m_bPause;

protected:
	int m_iRingCnt;
	int m_iLife;

protected:
	fPOINT campos;
	fPOINT m_ptOldPos;
	fPOINT m_ptGradient;
	fPOINT m_ptOldGradient;
	fPOINT m_ptJumpGradient;
	fPOINT m_ptGravity;

	Texture* pTex_Col;
	HDC Col_DC;

protected:
	COLORREF FloorColor;
	COLORREF WallColor;
	COLORREF ChangeColor;

protected:
	float m_AccTime;
	float m_fInvincibleTime;
	float m_fAccSpeed;
	float m_fAccRender;
	float m_fEndClimbTime;
	float m_fSpringSpeed;
	float m_fBreakSpeed;

protected:
	CHECK_TYPE m_CheckType;
	PLAYER_STATE state;
	ANI_STATE m_Animation;
	ANI_STATE m_eOldAnimation;
	SHIELD_STATE m_eShield;
	SHIELD_STATE m_eOldShield;

	STAGE_TYPE m_eCurStage;

protected:
	bool m_bDir;
	bool m_bOnGround;
	bool m_bCanJump;
	bool m_bChangeLayer;
	bool m_bTurn;
	bool m_bRightWallOn;
	bool m_bLeftWallOn;
	bool m_bClimbOn;
	bool m_bInvincible;
	bool m_bRenderOn;
	bool m_bOnStair;

protected:
	float m_fSpeed;
	float m_fJumpSpeed;
	float x1, r1, i1, p1;
	float y1, t1, j1, q1;
	float x2, r2, i2, p2;
	float y2, t2, j2, q2;


public:
	virtual void enterCollision(Collider* _other);
	virtual void onCollision(Collider* _other);
	virtual void exitCollision(Collider* _other);

protected:
	void ChangeLayer();
	void GravityON();
	void Limit();
	void CharactorMove();
	void adjustCol();
	void SwitchAnimation();
	void InvincibleTime();

protected:
	void CheckGradient();
	void CheckDownGradient();
	void CheckUpGradient();
	void CheckRightGradient();
	void CheckLeftGradient();

protected:
	void CheckPixel();
	void LeftPixcel();
	void RightPixcel();
	void UpPixcel();
	void DownPixcel();

protected:
	void CheckWall();
	void CheckRightWall();
	void CheckLeftWall();
	void CheckTopWall();

protected:
	void Player_Stop();
	void Player_Idle();
	void Player_Jump();
	void Player_Sit();
	void Player_Lookup();
	void Player_RightWalk();
	void Player_LeftWalk();
	void Player_Spin();
	void Player_SpinMove();
	void Player_RightBreak();
	void Player_LeftBreak();
	void Player_Spining();
	void Player_Drop();
	void Player_RightPush();
	void Player_LeftPush();
	void Player_RightClimb();
	void Player_LeftClimb();
	void Player_EndClimb_00();
	void Player_EndClimb_01();
	void Player_EndClimb_02();
	void Player_SpringJump();
	void Player_Hitted();
	void Player_Finish();
	

protected:
	void Jump_Move();
	void Spring_Jump();
	void ShieldON();


public:
	void SetState(PLAYER_STATE _state) { state = _state; }
	void SetSpringSpeed(float _speed) { m_fSpringSpeed = _speed; }
	void SetSpeed(float _speed) { m_fSpeed = _speed; }
	void SetGravity(float _gravity) { m_ptGravity.y = _gravity; }
	void SetClimb(bool _bool) { m_bClimbOn = _bool; }
	void SetJumpSpeed(float _jumpspeed) { m_fJumpSpeed = _jumpspeed; }
	void SetShieldState(SHIELD_STATE _state) { m_eShield = _state; }
	void SetColor(COLORREF _floor, COLORREF _wall, COLORREF _change) { FloorColor = _floor; WallColor = _wall, ChangeColor = _change; }
	void SetGradient(fPOINT _gradient) { m_ptGradient = _gradient; }
	void SetYPos(float _PosY) { pos.y = _PosY; }
	void SetOnGround(bool _ground) { m_bOnGround = _ground; }
	void SetInvincible(bool _invincible) { m_bInvincible = _invincible; }
	void SetAnimation(ANI_STATE _Animation) { m_Animation = _Animation; }
	void SetRingCnt(int _RingCnt) { m_iRingCnt = _RingCnt; }
	void SetCanJump(bool _jump) { m_bCanJump = _jump; }
	void SetOnStair(bool _stair) { m_bOnStair = _stair; }
	void SetDir(bool _dir) { m_bDir = _dir; }
	void SetSuperSonic(bool _super) { m_bSuperSonic = _super; }
	void SetPause(bool _pause) { m_bPause = _pause; }

public:
	void PlusLife(int _Life) { m_iLife += _Life; }
	void PlusRing(int _number) { m_iRingCnt += _number; }
	void MoveXPos(float _speed);

public:
	ANI_STATE GetAnimation() { return m_Animation; }
	SHIELD_STATE GetShield() { return m_eShield; }
	bool GetDir() { return m_bDir; }
	bool GetInvincible() { return m_bInvincible; }
	fPOINT GetOldPos() { return m_ptOldPos; }
	float GetSpeed() { return m_fSpeed; }
	int GetRingCnt() { return m_iRingCnt; }
	bool isSuper() { return m_bSuperSonic; }

public:
	float getRandomNumber(float min, float max);
	void SpitOutRing();
	
public:
	virtual void render(HDC _dc);
	virtual void update();
	void init( STAGE_TYPE _type);

public:
	Player();
	virtual ~Player();
};