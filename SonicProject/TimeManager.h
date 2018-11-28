#pragma once
class TimeManager
{
private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER OldCnt;
	LARGE_INTEGER CurCnt;

	int m_iFrame;

	float DeltaTime;
	float OldDeltaTime;
	float Renewfrequency;
	float m_tFPSTime;
	float m_iFrameLimit;

public:
	float GetDelatTime() { return DeltaTime; }
	LARGE_INTEGER GetFrequency() { return frequency; }
public:
	void init();
	void update();
	void render(HDC _dc);

public:
	static TimeManager& Manager()
	{
		static TimeManager inst;
		return inst;
	}
public:
	TimeManager();
	~TimeManager();
};

