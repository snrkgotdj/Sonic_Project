#include "stdafx.h"
#include "Stage_ICE.h"
#include "Player.h"
#include "ResManager.h"
#include "CollManager.h"
#include "Texture.h"
#include "KeyManager.h"
#include "StageManager.h"
#include "Camera.h"

Stage_ICE::Stage_ICE()
{

}


Stage_ICE::~Stage_ICE()
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


void Stage_ICE::enter()
{
	Player * player = new Player;
	player->init(fPOINT{ 100, 0 }, STAGE_ICE);
	vecObj[Obj_PLAYER].push_back(player);

	ResManager::Manager().LoadTexture(L"\\Map\\Stage\\ICE\\ICE_Map_first.bmp", L"Ice_Map");
	m_MapDC = ResManager::Manager().FindTexture(L"Ice_Map")->GetTexDC();
}

void Stage_ICE::exit()
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
		vecObj[i].clear();
	}

	ResManager::Manager().clear();
	CollManager::Manager().clear();
}

void Stage_ICE::render(HDC _dc)
{
	fPOINT CamPos = Camera::Cam().GetCamMousePos(fPOINT{ 0,200 });

	BitBlt(_dc, 0, 0, WindowSizeX, WindowSizeY, m_MapDC, CamPos.x, CamPos.y, SRCCOPY);

	vector<OBJ*>::iterator iter;
	for (int i = 0; i < Obj_END; ++i)
	{
		iter = vecObj[i].begin();

		for (; iter != vecObj[i].end(); ++iter)
		{
			if ((*iter) != NULL)
			{
				(*iter)->render(_dc);
			}
		}
	}
}

void Stage_ICE::update()
{
	CheckDie();

	vector<OBJ*>::iterator iter;
	for (int i = 0; i < Obj_END; ++i)
	{
		iter = vecObj[i].begin();
		for (; iter != vecObj[i].end(); ++iter)
		{
			if ((*iter) != NULL)
			{
				(*iter)->update();
			}
		}
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_ENTER, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_ICE);
	}
}

