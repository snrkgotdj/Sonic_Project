#include "stdafx.h"
#include "Camera.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "StageManager.h"
#include "OBJ.h"
#include "Stage.h"
#include "SoundManager.h"
#include "StageManager.h"
#include "Player.h"

Camera::Camera()
	: Center{}
	, TargetObj(NULL)
	, m_followspeed(200)
	, m_Limit{ 0,0 }
	, m_bPauseCam(false)
{
}


Camera::~Camera()
{
}



void Camera::CamLimit(fPOINT _point)
{
	if (_point.x <= WindowSizeX / 2)
	{
		Center.x = WindowSizeX / 2;
	}

	if (Center.y <= WindowSizeY / 2)
	{
		Center.y = WindowSizeY / 2;
	}

	if (m_Limit.x != 0 && m_Limit.y != 0)
	{
		if (Center.y >= (float)m_Limit.y - WindowSizeY / 2)
		{
			Center.y = (float)m_Limit.y - WindowSizeY / 2;
		}

		if (Center.x >= (float)m_Limit.x - WindowSizeX / 2)
		{
			Center.x = (float)m_Limit.x - WindowSizeX / 2;
			if (StageManager::Manager().GetCurStageType() == STAGE_00 && (Center.y >= 1210 && Center.y <= 1500) && m_bPauseCam == false)
			{
				m_bPauseCam = true;
				SoundManager::Manager()->PlayBGM(L"BGM_BOSS_SILVER");
			}
		}
	}
}

void Camera::FollowPoint(fPOINT _point)
{
	if (MODE_EDIT == StageManager::Manager().GetCurStage()->GetStageMode())
	{
		return;
	}

	if (m_bPauseCam == true)
		return;

	Player* pPlayer = ((Player*)StageManager::Manager().GetCurStage()->GetListObj(Obj_PLAYER)[0]);

//////////스무스 팔로우
	
	Center.x = _point.x;

	if (Center.y <= _point.y - 200)
	{
		Center.y = _point.y - 200;
	}

	else if (Center.y >= _point.y - 20 )
	{
		Center.y = _point.y - 20;
	}
	
	/////////////////파이널 스테이지 포지션
	if (StageManager::Manager().GetCurStageType() == STAGE_FINAL)
	{
		Center.x = _point.x;
		Center.y = _point.y;
	}

	CamLimit(_point);
}

void Camera::init(fPOINT _center, OBJ* _target)
{
	Center = _center;
	TargetObj = _target;
}

void Camera::update()
{
	Diff.x = Center.x - WindowSizeX / 2;
	Diff.y = Center.y - WindowSizeY / 2;

	if (m_bPauseCam == true || MODE_EDIT != StageManager::Manager().GetCurStage()->GetStageMode())
		return;


	float delta = TimeManager::Manager().GetDelatTime();
	if (KeyManager::Manager().GetKeyState(KEY_A, STATE_TAB) == true)
		Center.x -= 50;

	else if (KeyManager::Manager().GetKeyState(KEY_D, STATE_TAB) == true)
		Center.x += 50;

	else if (KeyManager::Manager().GetKeyState(KEY_W, STATE_TAB) == true)
		Center.y -= 50;
	
	else if (KeyManager::Manager().GetKeyState(KEY_S, STATE_TAB) == true)
		Center.y += 50;


	if (KeyManager::Manager().GetKeyState(KEY_F, STATE_HOLD) == true)
		Center.x -= 400*DT;

	else if (KeyManager::Manager().GetKeyState(KEY_H, STATE_HOLD) == true)
		Center.x += 400 *DT;

	else if (KeyManager::Manager().GetKeyState(KEY_T, STATE_HOLD) == true)
		Center.y -= 400 *DT;

	else if (KeyManager::Manager().GetKeyState(KEY_G, STATE_HOLD) == true)
		Center.y += 400 *DT;
	

}

fPOINT Camera::GetCamPos(fPOINT _point)
{
	_point.x -= Diff.x;
	_point.y -= Diff.y;
	return _point;
}

fPOINT Camera::GetCamMousePos(fPOINT _point)
{
	_point.x += Diff.x;
	_point.y += Diff.y;
	return _point;
}

fPOINT Camera::GetBackCamPos(fPOINT _point, int _rate)
{
	_point.x -= (Diff.x / _rate);
	_point.y -= (Diff.y / _rate);
	return _point;
}

fPOINT Camera::GetMousePos()
{

	return fPOINT();
}


