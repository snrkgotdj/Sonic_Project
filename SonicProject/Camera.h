#pragma once

class OBJ;

class Camera
{
private:
	fPOINT		Center;
	OBJ*		TargetObj;
	float		m_followspeed;

	fPOINT		Diff;
	POINT		m_Limit;

	bool		m_bPauseCam;


private:
	void CamLimit(fPOINT _point);

public:
	fPOINT GetDiff() { return Diff; }
	void FollowPoint(fPOINT _point);
public:
	void init(fPOINT _center, OBJ* _target);
	void update();
	
public:
	void SetTarget(OBJ* _obj) { TargetObj = _obj; }
	void SetLimit(POINT _point) { m_Limit = _point; }
	void SetPause(bool _pause) { m_bPauseCam = _pause; }

public:
	fPOINT GetCamPos(fPOINT _point);
	fPOINT GetCamMousePos(fPOINT _point);
	fPOINT GetBackCamPos(fPOINT _point, int _rate);
	fPOINT GetMousePos();
	POINT GetLimit() { return m_Limit; }
	bool isPause() { return m_bPauseCam; }

public:
	static Camera& Cam()
	{
		static Camera cam;
		return cam;
	}
public:
	Camera();
	~Camera();
};

