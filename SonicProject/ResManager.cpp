#include "stdafx.h"
#include "ResManager.h"
#include "PathManager.h"
#include "Texture.h"

ResManager::ResManager()
{
}


ResManager::~ResManager()
{
	clear();
}



Texture * ResManager::LoadTexture(const wstring & _strPath, const wstring & _strKey)
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
		MessageBox(g_hWnd, L"에러", L"이미지 로드 실패", MB_OK);
		return NULL;
	}

	pTex->m_Path = _strPath;
	pTex->m_key = _strKey;


	m_mapTexture.insert(make_pair(_strKey, pTex));
	return pTex;
	
}

Texture * ResManager::FindTexture(const wstring & _strKey)
{
	map<wstring,Texture*>::iterator iter =  m_mapTexture.find(_strKey);
	if (iter == m_mapTexture.end())
	{
		return NULL;
	}
	return iter->second;
}

void ResManager::clear()
{
	map<wstring, Texture*>::iterator iter = m_mapTexture.begin();
	for (; iter != m_mapTexture.end(); ++iter)
	{
		if (iter->second != NULL)
		{
			delete iter->second;
			iter->second = NULL;
		}
	}
	m_mapTexture.clear();
}

