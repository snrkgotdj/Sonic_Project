#pragma once

#include "define.h"

void SaveWstring(const wstring& _string, FILE* _pFile);
wchar_t* LoadWstring(FILE* _pFile);