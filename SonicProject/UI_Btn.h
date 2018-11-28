#pragma once
#include "UI.h"
class UI_Btn :
	public UI
{
protected:
	vector<Texture*> vecBtnTex;
	

	int m_idxButton;

public:
	virtual void update();
	
public:
	UI_Btn();
	~UI_Btn();
};

