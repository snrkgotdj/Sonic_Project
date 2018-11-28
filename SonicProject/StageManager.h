#pragma once
class Stage;

class StageManager
{
private:
	Stage* CurStage;
	Stage* ArrStage[STAGE_END];
	STAGE_TYPE CurStageType;
	
	Charactor_Mode m_eCharactor;

public:
	void init();
	void render(HDC _dc);
	void update();

public:
	void SetCharactorMode(Charactor_Mode _Charactor) { m_eCharactor = _Charactor; }
	void SetCurStageType(STAGE_TYPE _stage) { CurStageType = _stage; }

public:
	Stage* GetCurStage() { return CurStage; }
	Charactor_Mode GetCharactorMode() { return m_eCharactor; }
	STAGE_TYPE GetCurStageType() { return CurStageType; }

public:
	void ChangeStage(STAGE_TYPE _type);
	
public:
	static StageManager& Manager()
	{
		static StageManager inst;
		return inst;
	}
public:
	StageManager();
	~StageManager();
};

