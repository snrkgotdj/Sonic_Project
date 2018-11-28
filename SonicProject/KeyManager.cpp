#include "stdafx.h"
#include "KeyManager.h"


void KeyManager::init()
{
	for (int i = 0; i < (int)KEY_TYPE::KEY_TYPE_END; ++i)
	{
		arrkey[i].state = KEY_STATE::STATE_NONE;
	}

	arrkey[(int)KEY_TYPE::KEY_1].  key = '1';
	arrkey[(int)KEY_TYPE::KEY_2].key = '2';
	arrkey[(int)KEY_TYPE::KEY_3].key = '3';
	arrkey[(int)KEY_TYPE::KEY_4].key = '4';
	arrkey[(int)KEY_TYPE::KEY_5].key = '5';
	arrkey[(int)KEY_TYPE::KEY_6].key = '6';
	arrkey[(int)KEY_TYPE::KEY_7].key = '7';
	arrkey[(int)KEY_TYPE::KEY_8].key = '8';
	arrkey[(int)KEY_TYPE::KEY_9].key = '9';
	arrkey[(int)KEY_TYPE::KEY_0].key = '0';
	arrkey[(int)KEY_TYPE::KEY_Q].key = 'Q';
	arrkey[(int)KEY_TYPE::KEY_W].key = 'W';
	arrkey[(int)KEY_TYPE::KEY_E].key = 'E';
	arrkey[(int)KEY_TYPE::KEY_R].key = 'R';
	arrkey[(int)KEY_TYPE::KEY_T].key = 'T';
	arrkey[(int)KEY_TYPE::KEY_Y].key = 'Y';
	arrkey[(int)KEY_TYPE::KEY_U].key = 'U';
	arrkey[(int)KEY_TYPE::KEY_I].key = 'I';
	arrkey[(int)KEY_TYPE::KEY_O].key = 'O';
	arrkey[(int)KEY_TYPE::KEY_P].key = 'P';
	arrkey[(int)KEY_TYPE::KEY_A].key = 'A';
	arrkey[(int)KEY_TYPE::KEY_S].key = 'S';
	arrkey[(int)KEY_TYPE::KEY_D].key = 'D';
	arrkey[(int)KEY_TYPE::KEY_F].key = 'F';
	arrkey[(int)KEY_TYPE::KEY_G].key = 'G';
	arrkey[(int)KEY_TYPE::KEY_H].key = 'H';
	arrkey[(int)KEY_TYPE::KEY_J].key = 'J';
	arrkey[(int)KEY_TYPE::KEY_K].key = 'K';
	arrkey[(int)KEY_TYPE::KEY_L].key = 'L';
	arrkey[(int)KEY_TYPE::KEY_Z].key = 'Z';
	arrkey[(int)KEY_TYPE::KEY_X].key = 'X';
	arrkey[(int)KEY_TYPE::KEY_C].key = 'C';
	arrkey[(int)KEY_TYPE::KEY_V].key = 'V';
	arrkey[(int)KEY_TYPE::KEY_B].key = 'B';
	arrkey[(int)KEY_TYPE::KEY_N].key = 'N';
	arrkey[(int)KEY_TYPE::KEY_M].key = 'M';
	arrkey[(int)KEY_TYPE::KEY_UP].key = VK_UP;
	arrkey[(int)KEY_TYPE::KEY_DOWN].key = VK_DOWN;
	arrkey[(int)KEY_TYPE::KEY_LEFT].key = VK_LEFT;
	arrkey[(int)KEY_TYPE::KEY_RIGHT].key = VK_RIGHT;
	arrkey[(int)KEY_TYPE::KEY_LSHIFT].key = VK_LSHIFT;
	arrkey[(int)KEY_TYPE::KEY_RSHIFT].key = VK_RSHIFT;
	arrkey[(int)KEY_TYPE::KEY_SPACE].key = VK_SPACE;
	arrkey[(int)KEY_TYPE::KEY_INSERT].key = VK_INSERT;
	arrkey[(int)KEY_TYPE::KEY_DEL].key = VK_DELETE;
	arrkey[(int)KEY_TYPE::KEY_HOME].key = VK_HOME;
	arrkey[(int)KEY_TYPE::KEY_END].key = VK_END;
	arrkey[(int)KEY_TYPE::KEY_PAGEUP].key = VK_PRIOR;
	arrkey[(int)KEY_TYPE::KEY_PAGEDOWN].key = VK_NEXT;
	arrkey[(int)KEY_TYPE::KEY_ESC].key = VK_ESCAPE;
	arrkey[(int)KEY_TYPE::KEY_F1].key = VK_F1;
	arrkey[(int)KEY_TYPE::KEY_F2].key = VK_F2;
	arrkey[(int)KEY_TYPE::KEY_F3].key = VK_F3;
	arrkey[(int)KEY_TYPE::KEY_F4].key = VK_F4;
	arrkey[(int)KEY_TYPE::KEY_F5].key = VK_F5;
	arrkey[(int)KEY_TYPE::KEY_F6].key = VK_F6;
	arrkey[(int)KEY_TYPE::KEY_F7].key = VK_F7;
	arrkey[(int)KEY_TYPE::KEY_F8].key = VK_F8;
	arrkey[(int)KEY_TYPE::KEY_F9].key = VK_F9;
	arrkey[(int)KEY_TYPE::KEY_F10].key = VK_F10;
	arrkey[(int)KEY_TYPE::KEY_F11].key = VK_F11;
	arrkey[(int)KEY_TYPE::KEY_F12].key = VK_F12;
	arrkey[(int)KEY_TYPE::KEY_NUM0].key = VK_NUMPAD0;
	arrkey[(int)KEY_TYPE::KEY_NUM1].key = VK_NUMPAD1;
	arrkey[(int)KEY_TYPE::KEY_NUM2].key = VK_NUMPAD2;
	arrkey[(int)KEY_TYPE::KEY_NUM3].key = VK_NUMPAD3;
	arrkey[(int)KEY_TYPE::KEY_NUM4].key = VK_NUMPAD4;
	arrkey[(int)KEY_TYPE::KEY_NUM5].key = VK_NUMPAD5;
	arrkey[(int)KEY_TYPE::KEY_NUM6].key = VK_NUMPAD6;
	arrkey[(int)KEY_TYPE::KEY_NUM7].key = VK_NUMPAD7;
	arrkey[(int)KEY_TYPE::KEY_NUM8].key = VK_NUMPAD8;
	arrkey[(int)KEY_TYPE::KEY_NUM9].key = VK_NUMPAD9;
	arrkey[(int)KEY_TYPE::KEY_ENTER].key = VK_RETURN;
	arrkey[(int)KEY_TYPE::KEY_CTRL].key = VK_CONTROL;
	arrkey[(int)KEY_TYPE::KEY_ALT].key = VK_MENU;
	arrkey[(int)KEY_TYPE::KEY_TAB].key = VK_TAB;
	arrkey[(int)KEY_TYPE::KEY_CAPS].key = VK_CAPITAL;
	arrkey[(int)KEY_TYPE::KEY_LBTN].key = VK_LBUTTON;
	arrkey[(int)KEY_TYPE::KEY_RBTN].key = VK_RBUTTON;
	arrkey[(int)KEY_TYPE::KEY_MBTN].key = VK_MBUTTON;
}

void KeyManager::update()
{
	for (int i = 0; i < (int)KEY_TYPE::KEY_TYPE_END; ++i)
	{
		if (GetAsyncKeyState(arrkey[i].key) & 0x8000)
		{
			if (KEY_STATE::STATE_NONE == arrkey[i].state
				|| KEY_STATE::STATE_AWAY == arrkey[i].state)
				// 이전에는 안눌렸거나 키를 땐 상황, 현재 키가 눌림
				arrkey[i].state = STATE_TAB;
			else
				arrkey[i].state = STATE_HOLD;
		}
		else // 현재 키가 안눌림
		{
			if (KEY_STATE::STATE_NONE == arrkey[i].state)
				continue;

			if (KEY_STATE::STATE_AWAY == arrkey[i].state)
				arrkey[i].state = STATE_NONE;
			else
				arrkey[i].state = STATE_AWAY;
		}
	}

	POINT point{};
	GetCursorPos(&point);
	ScreenToClient(g_hWnd, &point);
	
	MouseCur.x = (float)point.x;
	MouseCur.y = (float)point.y;
}

bool KeyManager::GetKeyState(KEY_TYPE _key, KEY_STATE _state)
{

	if (arrkey[_key].state == _state)
	{
		return true;
	}
	return false;
}

KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}
