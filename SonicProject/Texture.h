#pragma once


class Texture
{
private:
	HDC m_DC;
	HBITMAP m_hBitmap;
	wstring m_Path;
	wstring m_key;

	float m_width;
	float m_height;


public:
	static Texture* Load(const wstring& _strFullPath);

public:
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
	const wstring& GetPath() { return m_Path; }
	const wstring& GetKey() { return m_key; }
	HDC GetTexDC() { return m_DC; }

public:
	void SetPath(const wstring& _strPath) { m_Path = _strPath; }
	void SetKey(const wstring& _strKey) { m_key = _strKey; }

public:
	Texture();
	~Texture();

	friend class ResManager;
};

