#include "stdafx.h"
#include "PathManager.h"

wchar_t PathManager::m_szResPath[255] = {};

PathManager::PathManager()
{
}


PathManager::~PathManager()
{
}

void PathManager::init()
{
	GetCurrentDirectory(255, m_szResPath);

	int iLen = (int)wcslen(m_szResPath);
	for (int i = iLen - 1; i >= 0; --i)
	{
		if (m_szResPath[i] == L'\\')
		{
			wmemset(m_szResPath + i, 0, iLen - 1);
			break;
		}
	}
	
	wcscat_s(m_szResPath, 255, L"\\Debug\\Resource");
}
