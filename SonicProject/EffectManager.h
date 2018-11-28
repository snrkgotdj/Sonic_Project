#pragma once

class Animator;
class Texture;

class EffectManager
{
private:
	map<wstring, Texture*> m_mapEffectTex;
	Animator* m_EffectAnim;


public:
	void init();
	void render(HDC _dc, fPOINT _pos);

public:
	Texture* LoadTexture(const wstring& _strPath, const wstring& _strKey);
	Texture* FindTexture(const wstring& _strKey);

public:
	void PlayEffect(const wstring& _strAnimation);

public:
	static EffectManager& Manager()
	{
		static EffectManager inst;
		return inst;
	}

private:
	EffectManager();
	~EffectManager();
};

