#pragma once
class GameManager
{
public:




private:
	HDC m_dc;
	HDC m_BackDC;
	HBITMAP m_BackBitmap;

public:
	HDC GetBackDC() { return m_BackDC; }
	HDC GetMainDC() { return m_dc; }
	HBITMAP& GetBitMap() { return m_BackBitmap; }

public:
	void init();
	void play();
	void render();
	void update();

public:
	static GameManager& Manager()
	{
		static GameManager inst;
		return inst;
	}

public:
	GameManager();
	~GameManager();
};

