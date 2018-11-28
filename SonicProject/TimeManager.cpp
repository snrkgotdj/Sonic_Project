#include "stdafx.h"
#include "TimeManager.h"


void TimeManager::init()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&CurCnt);
	OldCnt = CurCnt;


	m_tFPSTime = 0.f;
	m_iFrameLimit = 60;

}

void TimeManager::update()
{
	QueryPerformanceCounter(&CurCnt);
	DeltaTime = (CurCnt.QuadPart - OldCnt.QuadPart) / (float)frequency.QuadPart;
	OldCnt = CurCnt;

	Renewfrequency += DeltaTime;
	if (Renewfrequency > 1.f)
	{
		Renewfrequency = 0.f;
		QueryPerformanceFrequency(&frequency);
	}
	
	m_tFPSTime = 1 / DeltaTime;

	if (OldDeltaTime != 0)
	{
		if (DeltaTime > OldDeltaTime * 10)
		{
			DeltaTime = 0.f;
		}
	}

	OldDeltaTime = DeltaTime;
}

void TimeManager::render(HDC _dc)
{
	char str[128] = {};

	sprintf_s(str, "DeltaTime : %f, FPS : %f", DeltaTime, m_tFPSTime);
	TextOutA(_dc, 0, 0, str, (int)strlen(str));
}

TimeManager::TimeManager()
	:m_tFPSTime(0.f)
	, OldDeltaTime(0.f)
{
}


TimeManager::~TimeManager()
{
}
