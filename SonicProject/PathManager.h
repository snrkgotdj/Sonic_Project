#pragma once
class PathManager
{
private:
	PathManager();
	~PathManager();

public:
	static void init();

public:
	static wchar_t m_szResPath[255];
	static wchar_t * GetResPath() { return m_szResPath; }
};

