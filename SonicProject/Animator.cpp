#include "stdafx.h"
#include "Animator.h"
#include "Animation.h"
#include "OBJ.h"


Animator::Animator(OBJ* _Owner)
	:m_pOwner(_Owner)
	,m_pCurAnim(NULL)
{
}

Animator::Animator()
	: m_pCurAnim(NULL)
{
}


Animator::~Animator()
{
	Clear();
}



void Animator::render(HDC _dc,OBJ* _owner)
{
	if (NULL != m_pCurAnim)
	{
		m_pCurAnim->render(_dc, _owner);
	}
}

void Animator::render(HDC _dc, fPOINT _point)
{
	if (NULL != m_pCurAnim)
	{
		m_pCurAnim->render(_dc, _point);
	}
}

void Animator::render(HDC _dc, fPOINT _point, int _CurFrame)
{
	if (NULL != m_pCurAnim)
	{
		m_pCurAnim->render(_dc, _point, _CurFrame);
	}
}


void Animator::AddAnimation(const wstring & _strKey
	, Texture * _pTex, fPOINT _ptStart
	, int _iDir, fPOINT _ptCropSize
	, int _iMaxFrame, float _fInterval
	, DWORD _RGB, bool _fin)
{
	if (_iDir > 0)
	{
		Animation* pAnim = new Animation;
		for (int i = 0; i < _iMaxFrame; ++i)
		{
			AniFrame frame{};
			frame.m_fInteval = _fInterval;
			frame.m_iDir = _iDir;
			frame.m_ptCropSize = _ptCropSize;
			frame.m_pTexture = _pTex;
			frame.m_ptStartPos.x = _ptStart.x + (i * _ptCropSize.x) * _iDir;
			frame.m_ptStartPos.y = _ptStart.y;
			frame.m_RGB = _RGB;
			frame.m_Fin = _fin;
			pAnim->Addframe(frame);
		}

		m_mapAnim.insert(make_pair(_strKey, pAnim));
	}
	
	else if (_iDir < 0)
	{
		Animation* pAnim = new Animation;
		for (int i = 0; i < _iMaxFrame; ++i)
		{
			AniFrame frame{};
			frame.m_fInteval = _fInterval;
			frame.m_iDir = _iDir;
			frame.m_ptCropSize = _ptCropSize;
			frame.m_pTexture = _pTex;
			frame.m_ptStartPos.x = (_iMaxFrame-1) * _ptCropSize.x  +(i * _ptCropSize.x) * _iDir;
			frame.m_ptStartPos.y = _ptStart.y;
			frame.m_RGB = _RGB;
			frame.m_Fin = _fin;
			pAnim->Addframe(frame);
		}

		m_mapAnim.insert(make_pair(_strKey, pAnim));
	}
}


void Animator::PlayAnimation(const wstring & _strKey, int _frame)
{
	if (_strKey == L"NULL")
	{
		m_pCurAnim = NULL;
		return;
	}

	map<wstring, Animation*>::iterator iter = m_mapAnim.find(_strKey);
	
	if (iter == m_mapAnim.end())
		assert(NULL);

	m_pCurAnim = iter->second;
	m_pCurAnim->SetFrame(_frame);
}

void Animator::PlayAnimation(const wstring & _strKey)
{
	if (_strKey == L"NULL")
	{
		m_pCurAnim = NULL;
		return;
	}
	map<wstring, Animation*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
		assert(NULL);

	m_pCurAnim = iter->second;
}


void Animator::Clear()
{
	map<wstring, Animation*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{
		if (iter->second != NULL)
		{
			delete iter->second;
			iter->second = NULL;
		}
	}
	m_mapAnim.clear();
}

