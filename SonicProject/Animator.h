#pragma once

class Animation;
class OBJ;
class Texture;

class Animator
{
private:
	OBJ*						m_pOwner;
	map<wstring, Animation*>	m_mapAnim;
	Animation*					m_pCurAnim;
	
public:
	void render(HDC _dc, OBJ* _owner);
	void render(HDC _dc, fPOINT _point);
	void render(HDC _dc, fPOINT _point, int _CurFrame);

public:
	void AddAnimation(const wstring& _strKey, Texture* _pTex, fPOINT _ptStart, int _iDir, fPOINT _ptCropSize, int _iMaxFrame, float _fInterval, DWORD _RGB, bool _fin);
	void PlayAnimation(const wstring& _strKey, int _frame);
	void PlayAnimation(const wstring& _strKey);
	void Clear();

public:
	Animation* GetCurAnimation() { return m_pCurAnim; }

public:
	Animator(OBJ* _Owner);
	Animator();
	~Animator();
};

