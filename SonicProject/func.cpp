#include "stdafx.h"
#include "func.h"

wchar_t g_wstring[255] = {};

void SaveWstring(const wstring& _string, FILE * _pFile)
{
	BYTE len = (BYTE)_string.length();
	fwrite(&len, sizeof(BYTE), 1, _pFile);
	fwrite(_string.c_str(), sizeof(wchar_t), len, _pFile);

}

wchar_t* LoadWstring(FILE * _pFile)
{
	BYTE len = 0;
	fread(&len, sizeof(BYTE), 1, _pFile);

	memset(g_wstring, 0, sizeof(wchar_t) * 255);

	fread(g_wstring, sizeof(wchar_t), len, _pFile);

	return g_wstring;
}



