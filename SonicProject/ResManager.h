#pragma once
class Texture;

class ResManager
{
private:
	map<wstring, Texture*> m_mapTexture;

public:
	Texture* LoadTexture(const wstring& _strPath, const wstring& _strKey);
	Texture* FindTexture(const wstring& _strKey);
	void clear();
public:
	static ResManager& Manager()
	{
		static ResManager inst;
		return inst;
	}
public:
	ResManager();
	~ResManager();
};

