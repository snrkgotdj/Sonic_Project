#pragma once
enum KEY_TYPE
{
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_T,
	KEY_Y,
	KEY_U,
	KEY_I,
	KEY_O,
	KEY_P,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_Z,
	KEY_X,
	KEY_C,
	KEY_V,
	KEY_B,
	KEY_N,
	KEY_M,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_SPACE,
	KEY_INSERT,
	KEY_DEL,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_ESC,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_NUM0,
	KEY_NUM1,
	KEY_NUM2,
	KEY_NUM3,
	KEY_NUM4,
	KEY_NUM5,
	KEY_NUM6,
	KEY_NUM7,
	KEY_NUM8,
	KEY_NUM9,
	KEY_ENTER,
	KEY_CTRL,
	KEY_ALT,
	KEY_TAB,
	KEY_CAPS,
	KEY_LBTN,
	KEY_RBTN,
	KEY_MBTN,
	KEY_TYPE_END
};

enum KEY_STATE
{
	STATE_TAB,
	STATE_HOLD,
	STATE_AWAY,
	STATE_NONE,
};

struct KEY
{
	int key;
	KEY_STATE state;
};

class KeyManager
{
private:
	KEY arrkey[KEY_TYPE_END];
	fPOINT MouseCur;

public:
	void init();
	void update();

public:
	bool GetKeyState(KEY_TYPE _key, KEY_STATE _state);
	fPOINT GetMouseCur() { return MouseCur; }

public:
	static KeyManager& Manager()
	{
		static KeyManager inst;
		return inst;
	}
public:
	KeyManager();
	~KeyManager();
};

