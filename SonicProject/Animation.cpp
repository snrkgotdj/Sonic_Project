#include "stdafx.h"
#include "Animation.h"
#include "OBJ.h"
#include "Camera.h"
#include "TimeManager.h"
#include "Texture.h"

Animation::Animation()
	:m_iCurFrame(0)
	, m_AccTime(0.f)
	, m_bFin(false)
{
}


Animation::~Animation()
{

}


void Animation::render(HDC _dc, OBJ* _Owner)
{
	fPOINT ptCamPos;
	ptCamPos.x = Camera::Cam().GetCamPos(_Owner->GetPos()).x;
	ptCamPos.y = Camera::Cam().GetCamPos(_Owner->GetPos()).y;

	AniFrame& frame = m_vecFrame[m_iCurFrame];

	TransparentBlt(_dc
		, (int)(ptCamPos.x - frame.m_ptCropSize.x / 2)
		, (int)(ptCamPos.y - frame.m_ptCropSize.y / 2)
		, (int)(frame.m_ptCropSize.x)
		, (int)(frame.m_ptCropSize.y)
		, frame.m_pTexture->GetTexDC()
		, (int)frame.m_ptStartPos.x
		, (int)frame.m_ptStartPos.y
		, (int)frame.m_ptCropSize.x
		, (int)frame.m_ptCropSize.y
		, frame.m_RGB);

	m_AccTime += TimeManager::Manager().GetDelatTime();
	if (frame.m_fInteval < m_AccTime)
	{
		m_AccTime = 0.f;
		m_iCurFrame += 1;

		if (m_iCurFrame >= m_vecFrame.size())
		{
			if (frame.m_Fin == true)
			{
				m_iCurFrame = (int)m_vecFrame.size()-1;
			}
			else
			{
				m_iCurFrame = 0;
			}
		}
	}
}

void Animation::render(HDC _dc, fPOINT _point)
{
	m_bFin = false;

	fPOINT ptCamPos;
	ptCamPos.x = Camera::Cam().GetCamPos(_point).x;
	ptCamPos.y = Camera::Cam().GetCamPos(_point).y;

	AniFrame& frame = m_vecFrame[m_iCurFrame];

	TransparentBlt(_dc
		, (int)(ptCamPos.x - frame.m_ptCropSize.x / 2)
		, (int)(ptCamPos.y - frame.m_ptCropSize.y)
		, (int)frame.m_ptCropSize.x
		, (int)frame.m_ptCropSize.y
		, frame.m_pTexture->GetTexDC()
		, (int)frame.m_ptStartPos.x
		, (int)frame.m_ptStartPos.y
		, (int)frame.m_ptCropSize.x
		, (int)frame.m_ptCropSize.y
		, (UINT)frame.m_RGB);

	m_AccTime += TimeManager::Manager().GetDelatTime();
	if (frame.m_fInteval < m_AccTime)
	{
		m_AccTime = 0.f;
		m_iCurFrame += 1;

		if (m_iCurFrame >= m_vecFrame.size())
		{
			if (frame.m_Fin == true)
			{
				m_bFin = true;
				m_iCurFrame = (int)m_vecFrame.size()-1;
			}
			else
			{
				m_iCurFrame = 0;
			}
		}
	}
}

void Animation::render(HDC _dc, fPOINT _point, int _CurFrame)
{
	m_bFin = false;

	fPOINT ptCamPos;
	ptCamPos.x = Camera::Cam().GetCamPos(_point).x;
	ptCamPos.y = Camera::Cam().GetCamPos(_point).y;

	AniFrame& frame = m_vecFrame[m_iCurFrame];

	TransparentBlt(_dc
		, (int)(ptCamPos.x - frame.m_ptCropSize.x / 2.f)
		, (int)(ptCamPos.y - frame.m_ptCropSize.y)
		, (int)frame.m_ptCropSize.x
		, (int)frame.m_ptCropSize.y
		, frame.m_pTexture->GetTexDC()
		, (int)frame.m_ptStartPos.x
		, (int)frame.m_ptStartPos.y
		, (int)frame.m_ptCropSize.x
		, (int)frame.m_ptCropSize.y
		, (UINT)frame.m_RGB);

	m_AccTime += TimeManager::Manager().GetDelatTime();
	if (frame.m_fInteval < m_AccTime)
	{
		m_AccTime = 0.f;
		m_iCurFrame += 1;

		if (m_iCurFrame >= m_vecFrame.size())
		{
			if (frame.m_Fin == true)
			{
				m_bFin = true;
				m_iCurFrame = (int)m_vecFrame.size() - 1;
			}
			else
			{
				m_iCurFrame = _CurFrame - 1;
			}
		}
	}
}