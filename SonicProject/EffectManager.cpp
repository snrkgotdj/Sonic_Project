#include "stdafx.h"
#include "EffectManager.h"
#include "ResManager.h"
#include "PathManager.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"


EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
	map<wstring, Texture*>::iterator iter = m_mapEffectTex.begin();
	for (; iter != m_mapEffectTex.end(); ++iter)
	{
		if (iter->second != NULL)
		{
			delete iter->second;
			iter->second = NULL;
		}
	}
	m_mapEffectTex.clear();

	delete m_EffectAnim;
}




void EffectManager::init()
{
	LoadTexture(L"\\Effect\\Break.bmp", L"Break_ash");
	
	m_EffectAnim = new Animator;

	m_EffectAnim->AddAnimation(L"Break_Ash", FindTexture(L"Break_ash"), fPOINT{ 0,0 }, 1, fPOINT{ 26,28 }, 4, 0.1f, RGB(255, 0, 255), 0);
	m_EffectAnim->PlayAnimation(L"NULL",0);
}

void EffectManager::render(HDC _dc, fPOINT _pos)
{
	m_EffectAnim->render(_dc, _pos);
}

Texture * EffectManager::LoadTexture(const wstring & _strPath, const wstring & _strKey)
{
	Texture* pTex = FindTexture(_strKey);

	if (NULL != pTex)
	{
		return pTex;
	}

	// TODO: 여기에 반환 구문을 삽입합니다.
	wstring strpath = PathManager::GetResPath();

	strpath += _strPath;

	pTex = Texture::Load(strpath);
	if (NULL == pTex)
	{
		MessageBox(hWnd, L"에러", L"이미지 로드 실패", MB_OK);
		return NULL;
	}
	
	pTex->SetPath(_strPath);
	pTex->SetKey(_strKey);


	m_mapEffectTex.insert(make_pair(_strKey, pTex));
	return pTex;

}

Texture * EffectManager::FindTexture(const wstring & _strKey)
{
	map<wstring, Texture*>::iterator iter = m_mapEffectTex.find(_strKey);
	if (iter == m_mapEffectTex.end())
	{
		return NULL;
	}
	return iter->second;
}

void EffectManager::PlayEffect(const wstring & _strAnimation)
{
	m_EffectAnim->PlayAnimation(_strAnimation, 0);
}

