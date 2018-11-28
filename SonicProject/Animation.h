#pragma once

class Texture;
class OBJ;
class Animation
{
private:
	vector<AniFrame>  m_vecFrame;
	int m_iCurFrame;
	float m_AccTime;
	bool m_bFin;

public:
	void Addframe(AniFrame _frame) { m_vecFrame.push_back(_frame); }
	void SetFrame(int _frame) { m_iCurFrame = _frame; }
	void SetFin(bool _fin) { m_bFin = _fin; }

public:
	bool isFin() { return m_bFin; }

public:
	void render(HDC _dc, OBJ* _Owner);
	void render(HDC _dc, fPOINT _point);
	void render(HDC _dc, fPOINT _point, int _CurFrame);

public:
	Animation();
	~Animation();
};

