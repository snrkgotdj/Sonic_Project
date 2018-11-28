#pragma once
class OBJ;

class Stage
{
protected:
	COLORREF FloorColor;
	COLORREF WallColor;
	COLORREF ChangeColor;

protected:
	MODE_STATE m_eStageMode;
	EDIT_MODE m_eEditMode;
	
protected:
	vector<OBJ*> vecObj[Obj_END];
	vector<fPOINT> m_VecPos_OBJ[EDIT_END];

	HDC m_MapDC;
	POINT StageSize;

protected:
	void CheckDie();

public:
	vector<OBJ*>& GetListObj(OBJ_TYPE _type) { return vecObj[_type]; }
	MODE_STATE GetStageMode() { return m_eStageMode; }
	COLORREF GetFloorColor() { return FloorColor; }
	COLORREF GetWallColor() { return WallColor; }
	COLORREF GetChangeColor() { return ChangeColor; }

	
protected:
	void Save(const wstring& _strSTAGE);
	void LoadOBJ(const wstring& _strSTAGE);

protected:
	void EditMode(const wstring & _strSTAGE);
	void EditRender(HDC _dc);
	void ChangeItem();
	void CreateItem();

private:
	void SaveRing(const wstring& _strSTAGE);
	void SaveNill(const wstring& _strSTAGE);
	void SaveSpring_UP(const wstring& _strSTAGE);
	void SaveSpring_RIGHT(const wstring& _strSTAGE);
	void SaveSpring_LEFT(const wstring& _strSTAGE);
	void SaveFireItem(const wstring& _strSTAGE);
	void SaveWaterItem(const wstring& _strSTAGE);
	void SaveThunderItem(const wstring& _strSTAGE);
	void SaveRingItem(const wstring& _strSTAGE);
	void SaveLifeItem(const wstring& _strSTAGE);
	void SaveRightNillWall(const wstring& _strSTAGE);
	void SaveLeftNillWall(const wstring& _strSTAGE);

private:
	void LoadRing(const wstring& _strSTAGE);
	void LoadNill(const wstring& _strSTAGE);
	void LoadSpring_UP(const wstring& _strSTAGE);
	void LoadSpring_RIGHT(const wstring& _strSTAGE);
	void LoadSpring_LEFT(const wstring& _strSTAGE);
	void LoadFireItem(const wstring& _strSTAGE);
	void LoadWaterItem(const wstring& _strSTAGE);
	void LoadThunderItem(const wstring& _strSTAGE);
	void LoadRingItem(const wstring& _strSTAGE);
	void LoadLifeItem(const wstring& _strSTAGE);
	void LoadRightNillWall(const wstring& _strSTAGE);
	void LoadLeftNillWall(const wstring& _strSTAGE);


public:
	virtual void enter() = 0;
	virtual void exit();
	virtual void render(HDC _dc);
	virtual void update();

public:
	Stage();
	virtual ~Stage();
};

