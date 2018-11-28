#include "stdafx.h"
#include "Stage_Maptool.h"
#include "StageManager.h"
#include "KeyManager.h"
#include "ResManager.h"
#include "Camera.h"
#include "Tile.h"
#include "Resource.h"
#include "UI_Btn.h"
#include "Btn_TC.h"
#include "UI_Pannel.h"
#include "UI_Tile.h"
#include "MouseObj.h"
#include "PathManager.h"
#include "UI.h"

INT_PTR CALLBACK PROC_TILENUM(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			Stage_Maptool* MapStage = (Stage_Maptool*)StageManager::Manager().GetCurStage();

			int iXCnt = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, true);
			int iYCnt = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, true);

			MapStage->ResetTile(iXCnt, iYCnt);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		else if (LOWORD(wParam) == IDCANCEL)
		{

			EndDialog(hDlg, LOWORD(wParam));
			(INT_PTR)FALSE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

Stage_Maptool::Stage_Maptool()
	:iXCnt(1)
	,iYCnt(1)
	,pMouse(NULL)
	, FirstTileUIIdx(0)
{
}


Stage_Maptool::~Stage_Maptool()
{
	if(pMouse !=NULL)
		delete pMouse;
}



void Stage_Maptool::enter()
{
	Camera::Cam().init(fPOINT{ WindowSizeX / 2 , WindowSizeY / 2 }, NULL);
	ResManager::Manager().LoadTexture(L"\\Map\\EndMaptoolTile.bmp", L"Map_Tile");

	CreateButton();

	pMouse = new MouseObj;
	pMouse->init();

	for (int i = 0; i < iXCnt; ++i)
	{
		for (int j = 0; j < iYCnt; ++j)
		{
			Tile* pTile = new Tile;
			pTile->init();
			pTile->SetPos( fPOINT{ (float)j * TileSizeX, (float)i * TileSizeY });
			vecObj[Obj_TILE].push_back(pTile);
		}
	}
	
}

void Stage_Maptool::exit()
{
	ResManager::Manager().clear();
}

void Stage_Maptool::render(HDC _dc)
{
	vector<OBJ*>::iterator iter;
	for (int i = 0; i < Obj_END; ++i)
	{
		iter = vecObj[i].begin();
		for (; iter != vecObj[i].end(); ++iter)
		{
			(*iter)->render(_dc);
		}
	}
	pMouse->render(_dc);
}

void Stage_Maptool::update()
{
	KeyCheck();

	vector<OBJ*>::iterator iter;
	for (int i = 0; i < Obj_END; ++i)
	{
		iter = vecObj[i].begin();
		for (; iter != vecObj[i].end(); ++iter)
		{
			(*iter)->update();
		}
	}
	
	pMouse->update();


	if (KeyManager::Manager().GetKeyState(KEY_F1, STATE_TAB))
	{
		StageManager::Manager().ChangeStage(STAGE_LOGO);
	}
}



void Stage_Maptool::ResetTile(int _ixCnt, int _iYCnt)
{
	for (int i = 0; i < vecObj[Obj_TILE].size(); ++i)
	{
		if (NULL != vecObj[Obj_TILE][i])
		{
			delete vecObj[Obj_TILE][i];
			vecObj[Obj_TILE][i] = NULL;
		}
	}
	vecObj[Obj_TILE].clear();

	iXCnt = _ixCnt;
	iYCnt = _iYCnt;




	for (int i = 0; i < iYCnt; ++i)
	{
		for (int j = 0; j < iXCnt; ++j)
		{
			Tile* pTile = new Tile;
			pTile->init();
			pTile->SetPos(fPOINT{ (float)j * TileSizeX, (float)i * TileSizeY });
			vecObj[Obj_TILE].push_back(pTile);
		}
	}
}

void Stage_Maptool::CreateButton()
{

	pPannelUI = new UI_Pannel;
	pPannelUI->init();
	
	
	vecObj[Obj_UI].push_back(pPannelUI);

	float fPad = 10.f;
	fPOINT fPos = { fPad ,fPad };

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			UI_Tile* pBtnTile = new UI_Tile;
			pBtnTile->init();
			pBtnTile->SetPos(fPos);
			pBtnTile->SetSize(fPOINT{ TileSizeX,TileSizeY });
			pBtnTile->SetTileindex(FirstTileUIIdx + i * 3 + j);
			pPannelUI->AddChild(pBtnTile);
			fPos.x += fPad + TileSizeX;
		}
		fPos.x = fPad;
		fPos.y += fPad + TileSizeY;
	}
}

void Stage_Maptool::SetNextTileUI()
{
	pPannelUI->ResetChild();

	FirstTileUIIdx += 9;
	float fPad = 10.f;
	fPOINT fPos = { fPad ,fPad };

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			UI_Tile* pBtnTile = new UI_Tile;
			pBtnTile->init();
			pBtnTile->SetPos(fPos);
			pBtnTile->SetSize(fPOINT{ TileSizeX,TileSizeY });
			pBtnTile->SetTileindex(FirstTileUIIdx + i * 3 + j);
			pPannelUI->AddChild(pBtnTile);
			fPos.x += fPad + TileSizeX;
		}
		fPos.x = fPad;
		fPos.y += fPad + TileSizeY;
	}
}

void Stage_Maptool::SetPrevTileUI()
{
	pPannelUI->ResetChild();

	FirstTileUIIdx -= 9;
	float fPad = 10.f;
	fPOINT fPos = { fPad ,fPad };

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			UI_Tile* pBtnTile = new UI_Tile;
			pBtnTile->init();
			pBtnTile->SetPos(fPos);
			pBtnTile->SetSize(fPOINT{ TileSizeX,TileSizeY });
			pBtnTile->SetTileindex(FirstTileUIIdx + i * 3 + j);
			pPannelUI->AddChild(pBtnTile);
			fPos.x += fPad + TileSizeX;
		}
		fPos.x = fPad;
		fPos.y += fPad + TileSizeY;
	}
}

void Stage_Maptool::KeyCheck()
{
	if (true == KeyManager::Manager().GetKeyState(KEY_TAB, STATE_TAB))
	{
		DialogBox(NULL, MAKEINTRESOURCE(IDD_TILENUM), g_hWnd, PROC_TILENUM);
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_F9, STATE_TAB))
	{
		//SAVE
		wchar_t szFilter[] = L"TileData (*.data) |*.data;| All Files(*.*)|*.*;||";
		CFileDialog dlg(FALSE, NULL, NULL, OFN_EXPLORER, szFilter);

		wstring strpath = PathManager::GetResPath();

		strpath += L"\\TileData";

		dlg.m_ofn.lpstrInitialDir = strpath.c_str();

		if (IDOK != dlg.DoModal())
		{
			return;
		}

		wstring Filepath = dlg.GetPathName();

		FILE* pFile = NULL;

		_wfopen_s(&pFile, Filepath.c_str(), L"wb");

		vecObj[Obj_TILE];

		int iTileCnt = (int)vecObj->size();
		fwrite(&iTileCnt, sizeof(int), 1, pFile);

		for (int i = 0; i < vecObj[Obj_TILE].size(); ++i)
		{
			((Tile*)(vecObj[Obj_TILE][i]))->Save(pFile);
		}

		fclose(pFile);
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_F10, STATE_TAB))
	{
		//LOAD
		wchar_t szFilter[] = L"TileData (*.data) |*.data;| All Files(*.*)|*.*;||";
		CFileDialog dlg(TRUE, NULL, NULL, OFN_EXPLORER, szFilter);

		wstring strpath = PathManager::GetResPath();
		strpath += L"\\TileData";

		dlg.m_ofn.lpstrInitialDir = strpath.c_str();

		if (IDOK != dlg.DoModal())
		{
			return;
		}
		wstring Filepath = dlg.GetPathName();

		FILE* pFile = NULL;
		_wfopen_s(&pFile, Filepath.c_str(), L"rb");

		if (pFile == NULL)
			return;
		
		for (int i = 0; i < vecObj[Obj_TILE].size(); ++i)
		{
			delete vecObj[Obj_TILE][i];
			vecObj[Obj_TILE][i] = NULL;
		}
		
		vecObj[Obj_TILE].clear();
		
		int TileCnt = 0;
		fread(&TileCnt, sizeof(int), 1, pFile);
		for (int i = 0; i < TileCnt; ++i)
		{
			Tile* pTile = new Tile;
			pTile->Load(pFile);
			vecObj[Obj_TILE].push_back(pTile);
		}

		fclose(pFile);
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_W, STATE_TAB))
	{
		SetNextTileUI();
	}

	if (true == KeyManager::Manager().GetKeyState(KEY_Q, STATE_TAB))
	{
		SetPrevTileUI();
	}
}

