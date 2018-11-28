#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "ResManager.h"
#include "CollManager.h"
#include "Ring.h"
#include "Nill.h"
#include "PathManager.h"
#include "FireItem.h"
#include "WaterItem.h"
#include "ThunderItem.h"
#include "Spring.h"
#include "Spring_Left.h"
#include "Spring_Right.h"
#include "KeyManager.h"
#include "Camera.h"
#include "RingItem.h"
#include "LifeBox.h"
#include "NillWall.h"


Stage::Stage()
	:vecObj{}
	, m_eStageMode(MODE_PLAY)
	, m_eEditMode(EDIT_RING)
	, m_VecPos_OBJ{}
{

}


Stage::~Stage()
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




void Stage::exit()
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

void Stage::render(HDC _dc)
{
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

void Stage::update()
{
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
}

void Stage::CheckDie()
{
	vector<OBJ*>::iterator iter;
	for (int i = 0; i < Obj_END; ++i)
	{
		iter = vecObj[i].begin();
		for (; iter != vecObj[i].end();)
		{
			if ((*iter)->GetAlive() == false)
			{
				if ((*iter) != NULL)
				{
					delete (*iter);
					iter = vecObj[i].erase(iter);
				}
			}
			else
			{
				++iter;
			}
		}
	}
}



void Stage::LoadOBJ(const wstring& _strSTAGE)
{
	LoadRing(_strSTAGE);

	LoadNill(_strSTAGE);

	LoadSpring_UP(_strSTAGE);

	LoadSpring_RIGHT(_strSTAGE);

	LoadSpring_LEFT(_strSTAGE);

	LoadFireItem(_strSTAGE);

	LoadWaterItem(_strSTAGE);

	LoadThunderItem(_strSTAGE);

	LoadRingItem(_strSTAGE);

	LoadLifeItem(_strSTAGE);

	LoadRightNillWall(_strSTAGE);

	LoadLeftNillWall(_strSTAGE);

}

void Stage::Save(const wstring& _strSTAGE)
{
	SaveRing(_strSTAGE);

	SaveNill(_strSTAGE);

	SaveSpring_UP(_strSTAGE);

	SaveSpring_RIGHT(_strSTAGE);

	SaveSpring_LEFT(_strSTAGE);

	SaveFireItem(_strSTAGE);

	SaveWaterItem(_strSTAGE);

	SaveThunderItem(_strSTAGE);

	SaveRingItem(_strSTAGE);

	SaveLifeItem(_strSTAGE);

	SaveRightNillWall(_strSTAGE);

	SaveLeftNillWall(_strSTAGE);
}

void Stage::EditMode(const wstring & _strSTAGE)
{
	if (m_eStageMode == MODE_PLAY)
		return;

	ChangeItem();

	CreateItem();

	if (true == KeyManager::Manager().GetKeyState(KEY_P, STATE_TAB))
	{
		Stage::Save(_strSTAGE);
	}
}

void Stage::EditRender(HDC _dc)
{
	char test[255] = {};

	if (m_eStageMode == MODE_PLAY)
	{
		sprintf_s(test, "MODE :  PLAY_MODE");
		TextOutA(_dc, 500, 100, test, (int)strlen(test));
	}

	else if (m_eStageMode == MODE_EDIT)
	{
		sprintf_s(test, "MODE :  EDIT_MODE");
		TextOutA(_dc, 500, 100, test, (int)strlen(test));

		switch (m_eEditMode)
		{
		case EDIT_RING:
			sprintf_s(test, "EDIT :  EDIT_RING");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_NILL:
			sprintf_s(test, "EDIT :  EDIT_NILL");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_SPRING_UP:
			sprintf_s(test, "EDIT :  EDIT_SPRING_UP");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_SPRING_RIGHT:
			sprintf_s(test, "EDIT :  EDIT_SPRING_RIGHT");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_SPRING_LEFT:
			sprintf_s(test, "EDIT :  EDIT_SPRING_LEFT");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_FIREITEM:
			sprintf_s(test, "EDIT :  EDIT_FIREITEM");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_WATERITEM:
			sprintf_s(test, "EDIT :  EDIT_WATERITEM");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_THUNDERITEM:
			sprintf_s(test, "EDIT :  EDIT_THUNDERITEM");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_RINGITEM:
			sprintf_s(test, "EDIT :  EDIT_RINGITEM");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_LIFEITEM:
			sprintf_s(test, "EDIT :  EDIT_LIFEITEM");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_NILLWALL_RIGHT:
			sprintf_s(test, "EDIT :  EDIT_NILLWALL_RIGHT");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;

		case EDIT_NILLWALL_LEFT:
			sprintf_s(test, "EDIT :  EDIT_NILLWALL_LEFT");
			TextOutA(_dc, 500, 120, test, (int)strlen(test));
			break;
		case EDIT_END:
			break;
		default:
			break;
		}
	}

}

void Stage::ChangeItem()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_1, STATE_TAB))
	{
		m_eEditMode = EDIT_RING;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_2, STATE_TAB))
	{
		m_eEditMode = EDIT_NILL;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_3, STATE_TAB))
	{
		m_eEditMode = EDIT_SPRING_UP;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_4, STATE_TAB))
	{
		m_eEditMode = EDIT_SPRING_RIGHT;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_5, STATE_TAB))
	{
		m_eEditMode = EDIT_SPRING_LEFT;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_6, STATE_TAB))
	{
		m_eEditMode = EDIT_FIREITEM;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_7, STATE_TAB))
	{
		m_eEditMode = EDIT_THUNDERITEM;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_8, STATE_TAB))
	{
		m_eEditMode = EDIT_WATERITEM;
	}
	else if (true == KeyManager::Manager().GetKeyState(KEY_9, STATE_TAB))
	{
		m_eEditMode = EDIT_END;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_F1, STATE_TAB))
	{
		m_eEditMode = EDIT_RINGITEM;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_F2, STATE_TAB))
	{
		m_eEditMode = EDIT_LIFEITEM;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_F3, STATE_TAB))
	{
		m_eEditMode = EDIT_NILLWALL_RIGHT;
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_F4, STATE_TAB))
	{
		m_eEditMode = EDIT_NILLWALL_LEFT;
	}
}

void Stage::CreateItem()
{
	fPOINT Mouse = KeyManager::Manager().GetMouseCur();

	Mouse = Camera::Cam().GetCamMousePos(Mouse);
	//링
	if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_RING)
	{
		Ring* pRing = new Ring;
		pRing->init(Mouse);
		vecObj[OBJ_RING].push_back(pRing);

		m_VecPos_OBJ[EDIT_RING].push_back(Mouse);
	}
	//바늘
	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_NILL)
	{
		Nill* pNill = new Nill;
		pNill->init(Mouse);
		vecObj[OBJ_NILL].push_back(pNill);

		m_VecPos_OBJ[EDIT_NILL].push_back(Mouse);
	}
	//스프링 위
	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_SPRING_UP)
	{

		Spring* pSpring_UP = new Spring;
		pSpring_UP->init(Mouse, 1700.f);
		vecObj[OBJ_SPRING].push_back(pSpring_UP);

		m_VecPos_OBJ[EDIT_SPRING_UP].push_back(Mouse);
	}
	//스프링 오른쪽
	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_SPRING_RIGHT)
	{

		Spring_Right* pSpring_Right = new Spring_Right;
		pSpring_Right->init(Mouse, 1500.f);
		vecObj[OBJ_SPRING].push_back(pSpring_Right);

		m_VecPos_OBJ[EDIT_SPRING_RIGHT].push_back(Mouse);
	}
	//스프링 왼쪽
	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_SPRING_LEFT)
	{

		Spring_Left* pSpring_Left = new Spring_Left;
		pSpring_Left->init(Mouse, 1500.f);
		vecObj[OBJ_SPRING].push_back(pSpring_Left);

		m_VecPos_OBJ[EDIT_SPRING_LEFT].push_back(Mouse);
	}
	//불 아이템
	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_FIREITEM)
	{
		FireItem* pFireItem = new FireItem;
		pFireItem->init(Mouse);
		vecObj[OBJ_ITEM].push_back(pFireItem);

		m_VecPos_OBJ[EDIT_FIREITEM].push_back(Mouse);
	}
	//물 아이템
	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_WATERITEM)
	{
		WaterItem* pWaterItem = new WaterItem;
		pWaterItem->init(Mouse);
		vecObj[OBJ_ITEM].push_back(pWaterItem);

		m_VecPos_OBJ[EDIT_WATERITEM].push_back(Mouse);
	}
	//번개 아이템
	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_THUNDERITEM)
	{
		ThunderItem* pThunderItem = new ThunderItem;
		pThunderItem->init(Mouse);
		vecObj[OBJ_ITEM].push_back(pThunderItem);

		m_VecPos_OBJ[EDIT_THUNDERITEM].push_back(Mouse);
	}
	//링 아이템
	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_RINGITEM)
	{
		RingItem* pRingItem = new RingItem;
		pRingItem->init(Mouse);
		vecObj[OBJ_ITEM].push_back(pRingItem);

		m_VecPos_OBJ[EDIT_RINGITEM].push_back(Mouse);
	}
	//라이프 아이템
	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_LIFEITEM)
	{
		LifeBox* pLifeBox = new LifeBox;
		pLifeBox->init(Mouse);
		vecObj[OBJ_ITEM].push_back(pLifeBox);

		m_VecPos_OBJ[EDIT_LIFEITEM].push_back(Mouse);
	}
	//바늘 벽 왼쪽
	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_NILLWALL_LEFT)
	{
		NillWall* pNillWall = new NillWall;
		pNillWall->init(Mouse, MOVE_LEFT);
		vecObj[OBJ_ITEM].push_back(pNillWall);

		m_VecPos_OBJ[EDIT_NILLWALL_LEFT].push_back(Mouse);
	}

	else if (true == KeyManager::Manager().GetKeyState(KEY_LBTN, STATE_TAB) && m_eEditMode == EDIT_NILLWALL_RIGHT)
	{
		NillWall* pNillWall = new NillWall;
		pNillWall->init(Mouse, MOVE_RIGHT);
		vecObj[OBJ_ITEM].push_back(pNillWall);

		m_VecPos_OBJ[EDIT_NILLWALL_RIGHT].push_back(Mouse);
	}
}


//LOAD
void Stage::LoadRing(const wstring& _strSTAGE)
{
	m_VecPos_OBJ[EDIT_RING].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\RingPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	for (int i = 0; i < vecObj[OBJ_RING].size(); ++i)
	{
		delete vecObj[OBJ_RING][i];
		vecObj[OBJ_RING][i] = NULL;
	}

	vecObj[OBJ_RING].clear();

	int iRingCnt = 0;
	fread(&iRingCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < iRingCnt; ++i)
	{
		Ring* pRing = new Ring;
		pRing->Load(pFile);
		pRing->init();
		vecObj[OBJ_RING].push_back(pRing);
		m_VecPos_OBJ[EDIT_RING].push_back(pRing->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadNill(const wstring& _strSTAGE)
{
	m_VecPos_OBJ[EDIT_NILL].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\NillPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	for (int i = 0; i < vecObj[OBJ_NILL].size(); ++i)
	{
		delete vecObj[OBJ_NILL][i];
		vecObj[OBJ_NILL][i] = NULL;
	}

	vecObj[OBJ_NILL].clear();

	int iNillCnt = 0;
	fread(&iNillCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < iNillCnt; ++i)
	{
		Nill* pNill = new Nill;
		pNill->Load(pFile);
		pNill->init();
		vecObj[OBJ_NILL].push_back(pNill);
		m_VecPos_OBJ[EDIT_NILL].push_back(pNill->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadSpring_UP(const wstring& _strSTAGE)
{
	m_VecPos_OBJ[EDIT_SPRING_UP].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\SpringPos_UP.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	for (int i = 0; i < vecObj[OBJ_SPRING].size(); ++i)
	{
		delete vecObj[OBJ_SPRING][i];
		vecObj[OBJ_SPRING][i] = NULL;
	}

	vecObj[OBJ_SPRING].clear();

	int iSpringCnt_UP = 0;
	fread(&iSpringCnt_UP, sizeof(int), 1, pFile);

	for (int i = 0; i < iSpringCnt_UP; ++i)
	{
		Spring* pSpring = new Spring;
		pSpring->Load(pFile);
		pSpring->init();
		vecObj[OBJ_SPRING].push_back(pSpring);
		m_VecPos_OBJ[EDIT_SPRING_UP].push_back(pSpring->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadSpring_RIGHT(const wstring& _strSTAGE)
{
	m_VecPos_OBJ[EDIT_SPRING_RIGHT].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\SpringPos_RIGHT.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	int iSpringCnt_RIGHT = 0;
	fread(&iSpringCnt_RIGHT, sizeof(int), 1, pFile);

	for (int i = 0; i < iSpringCnt_RIGHT; ++i)
	{
		Spring_Right* pSpring_Right = new Spring_Right;
		pSpring_Right->Load(pFile);
		pSpring_Right->init();
		vecObj[OBJ_SPRING].push_back(pSpring_Right);
		m_VecPos_OBJ[EDIT_SPRING_RIGHT].push_back(pSpring_Right->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadSpring_LEFT(const wstring& _strSTAGE)
{
	m_VecPos_OBJ[EDIT_SPRING_LEFT].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\SpringPos_LEFT.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	int iSpringCnt_LEFT = 0;
	fread(&iSpringCnt_LEFT, sizeof(int), 1, pFile);

	for (int i = 0; i < iSpringCnt_LEFT; ++i)
	{
		Spring_Left* pSpring_Left = new Spring_Left;
		pSpring_Left->Load(pFile);
		pSpring_Left->init();
		vecObj[OBJ_SPRING].push_back(pSpring_Left);
		m_VecPos_OBJ[EDIT_SPRING_LEFT].push_back(pSpring_Left->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadFireItem(const wstring& _strSTAGE)
{
	m_VecPos_OBJ[EDIT_FIREITEM].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\FireItemPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	for (int i = 0; i < vecObj[OBJ_ITEM].size(); ++i)
	{
		delete vecObj[OBJ_ITEM][i];
		vecObj[OBJ_ITEM][i] = NULL;
	}

	vecObj[OBJ_ITEM].clear();

	int iFireItemCnt = 0;
	fread(&iFireItemCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < iFireItemCnt; ++i)
	{
		FireItem* pFireItem = new FireItem;
		pFireItem->Load(pFile);
		pFireItem->init();
		vecObj[OBJ_ITEM].push_back(pFireItem);
		m_VecPos_OBJ[EDIT_FIREITEM].push_back(pFireItem->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadWaterItem(const wstring& _strSTAGE)
{
	m_VecPos_OBJ[EDIT_WATERITEM].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\WaterItemPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	int iWaterItemCnt = 0;
	fread(&iWaterItemCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < iWaterItemCnt; ++i)
	{
		WaterItem* pWaterItem = new WaterItem;
		pWaterItem->Load(pFile);
		pWaterItem->init();
		vecObj[OBJ_ITEM].push_back(pWaterItem);
		m_VecPos_OBJ[EDIT_WATERITEM].push_back(pWaterItem->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadThunderItem(const wstring& _strSTAGE)
{
	m_VecPos_OBJ[EDIT_THUNDERITEM].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\ThunderItemPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	int iThunderItemCnt = 0;
	fread(&iThunderItemCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < iThunderItemCnt; ++i)
	{
		ThunderItem* pThunderItem = new ThunderItem;
		pThunderItem->Load(pFile);
		pThunderItem->init();
		vecObj[OBJ_ITEM].push_back(pThunderItem);
		m_VecPos_OBJ[EDIT_THUNDERITEM].push_back(pThunderItem->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadRingItem(const wstring& _strSTAGE)
{
	m_VecPos_OBJ[EDIT_RINGITEM].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\RingItemPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	int iRingItemCnt = 0;
	fread(&iRingItemCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < iRingItemCnt; ++i)
	{
		RingItem* pRingItem = new RingItem;
		pRingItem->Load(pFile);
		pRingItem->init();
		vecObj[OBJ_ITEM].push_back(pRingItem);
		m_VecPos_OBJ[EDIT_RINGITEM].push_back(pRingItem->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadLifeItem(const wstring& _strSTAGE)
{
	m_VecPos_OBJ[EDIT_LIFEITEM].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\LifeItemPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	int iLifeItemCnt = 0;
	fread(&iLifeItemCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < iLifeItemCnt; ++i)
	{
		LifeBox* pLifeBox = new LifeBox;
		pLifeBox->Load(pFile);
		pLifeBox->init();
		vecObj[OBJ_ITEM].push_back(pLifeBox);
		m_VecPos_OBJ[EDIT_LIFEITEM].push_back(pLifeBox->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadRightNillWall(const wstring & _strSTAGE)
{
	m_VecPos_OBJ[EDIT_NILLWALL_RIGHT].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\Right_NillWall.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	for (int i = 0; i < vecObj[OBJ_FEATURE].size(); ++i)
	{
		delete vecObj[OBJ_FEATURE][i];
		vecObj[OBJ_FEATURE][i] = NULL;
	}

	vecObj[OBJ_FEATURE].clear();

	int iRight_NillWallCnt = 0;
	fread(&iRight_NillWallCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < iRight_NillWallCnt; ++i)
	{
		NillWall* pNillWall = new NillWall;
		pNillWall->Load(pFile);
		pNillWall->init(MOVE_RIGHT);
		vecObj[OBJ_FEATURE].push_back(pNillWall);
		m_VecPos_OBJ[EDIT_NILLWALL_RIGHT].push_back(pNillWall->GetPos());
	}

	fclose(pFile);
}

void Stage::LoadLeftNillWall(const wstring & _strSTAGE)
{
	m_VecPos_OBJ[EDIT_NILLWALL_LEFT].clear();

	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\Left_NillWall.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"rb");

	if (pFile == NULL)
		return;

	int iLeft_NillWallCnt = 0;
	fread(&iLeft_NillWallCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < iLeft_NillWallCnt; ++i)
	{
		NillWall* pNillWall = new NillWall;
		pNillWall->Load(pFile);
		pNillWall->init(MOVE_LEFT);
		vecObj[OBJ_FEATURE].push_back(pNillWall);
		m_VecPos_OBJ[EDIT_NILLWALL_LEFT].push_back(pNillWall->GetPos());
	}

	fclose(pFile);
}


//SAVE
void Stage::SaveRing(const wstring& _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\RingPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_RING].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_RING].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_RING][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveNill(const wstring& _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\NillPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_NILL].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_NILL].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_NILL][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveSpring_UP(const wstring& _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\SpringPos_UP.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_SPRING_UP].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_SPRING_UP].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_SPRING_UP][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveSpring_RIGHT(const wstring& _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\SpringPos_RIGHT.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_SPRING_RIGHT].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_SPRING_RIGHT].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_SPRING_RIGHT][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveSpring_LEFT(const wstring& _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\SpringPos_LEFT.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_SPRING_LEFT].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_SPRING_LEFT].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_SPRING_LEFT][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveFireItem(const wstring& _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\FireItemPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_FIREITEM].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_FIREITEM].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_FIREITEM][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveWaterItem(const wstring& _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\WaterItemPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_WATERITEM].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_WATERITEM].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_WATERITEM][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveThunderItem(const wstring& _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\ThunderItemPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_THUNDERITEM].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_THUNDERITEM].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_THUNDERITEM][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveRingItem(const wstring& _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\RingItemPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_RINGITEM].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_RINGITEM].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_RINGITEM][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveLifeItem(const wstring& _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\LifeItemPos.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_LIFEITEM].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_LIFEITEM].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_LIFEITEM][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveRightNillWall(const wstring & _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\Right_NillWall.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_NILLWALL_RIGHT].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_NILLWALL_RIGHT].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_NILLWALL_RIGHT][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);
}

void Stage::SaveLeftNillWall(const wstring & _strSTAGE)
{
	wstring strpath = PathManager::GetResPath();

	strpath += L"\\OBJPos\\";
	strpath += _strSTAGE;
	strpath += L"\\Left_NillWall.txt";

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strpath.c_str(), L"wb");

	if (pFile == NULL)
		return;

	int iCnt = (int)m_VecPos_OBJ[EDIT_NILLWALL_LEFT].size();

	fwrite(&iCnt, sizeof(int), 1, pFile);

	for (int i = 0; i < m_VecPos_OBJ[EDIT_NILLWALL_LEFT].size(); ++i)
	{
		fwrite(&(m_VecPos_OBJ[EDIT_NILLWALL_LEFT][i]), sizeof(fPOINT), 1, pFile);
	}

	fclose(pFile);

}
