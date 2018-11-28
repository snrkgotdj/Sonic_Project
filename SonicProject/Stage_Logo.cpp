#include "stdafx.h"
#include "Stage_Logo.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "Camera.h"
#include "CollManager.h"
#include "ResManager.h"
#include "Texture.h"
#include "KeyManager.h"
#include "StageManager.h"
#include "Animator.h"
#include "Box.h"
#include "SoundManager.h"
#include "UIManager.h"

Stage_Logo::Stage_Logo()
{

}

Stage_Logo::~Stage_Logo()
{
	vector<OBJ*>::iterator iter;
	for (int i = 0; i < Obj_END; ++i)
	{
		iter = vecObj[i].begin();
		for (; iter != vecObj[i].end(); ++iter)
		{
			if ((*iter) != NULL)
			{
				delete (*iter);
				(*iter) = NULL;
			}
		}
	}
}



void Stage_Logo::enter()
{
	StageManager::Manager().SetCurStageType(STAGE_LOGO);

	UIManager::Manager().SetTime(0, 0, 0);

	Camera::Cam().init(fPOINT{ WindowSizeX / 2 , WindowSizeY / 2 }, NULL);
	background.init();
}

void Stage_Logo::exit()
{
	background.Clear();
	ResManager::Manager().clear();

	SoundManager::Manager()->StopSound(L"Sound_Intro");


}		   

void Stage_Logo::render(HDC _dc)
{
	background.render(_dc);
}

void Stage_Logo::update()
{
	background.update();
	if (true == KeyManager::Manager().GetKeyState(KEY_ENTER, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_SELECT);
	}
}

