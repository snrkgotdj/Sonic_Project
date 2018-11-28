#include "stdafx.h"
#include "Texture.h"
#include "GameManager.h"

Texture * Texture::Load(const wstring & _strFullPath)
{
	HBITMAP hBit = (HBITMAP)LoadImage(NULL, _strFullPath.c_str(), IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);

	if (NULL == hBit)
		return NULL;

	HDC hdc = CreateCompatibleDC(GameManager::Manager().GetBackDC());
	HBITMAP oldbitmap = (HBITMAP)SelectObject(hdc, hBit);
	DeleteObject(oldbitmap);

	BITMAP Bit;
	GetObject(hBit, sizeof(BITMAP), &Bit);

	Texture* pTex = new Texture;
	pTex->m_width = (float)Bit.bmWidth;
	pTex->m_height = (float)Bit.bmHeight;

	pTex->m_hBitmap = hBit;
	pTex->m_DC = hdc;

	return pTex;
}


Texture::Texture()
{
}


Texture::~Texture()
{
}
