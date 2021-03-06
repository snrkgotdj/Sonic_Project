// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers


#define _AFXDLL
#include <afxdlgs.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#define _USE_MATH_DEFINES

#include <cmath>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "define.h"
#include <list>
#include <vector>
#include <map>
#include <WinGdi.h>
#include <assert.h>
#include <random>
using namespace std;

// sound mgr 용도 - 헤더 순서 중요
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")


#pragma comment(lib, "Msimg32.lib")

//video
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

