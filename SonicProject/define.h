#pragma once

extern HWND g_hWnd;
extern HINSTANCE hInst;

extern bool DEBUGRENDER;

#define WindowSizeX 1024
#define WindowSizeY 600

#define M_PI 3.141592653589

#define KnuckleSizeX 31
#define KnuckleSizeY 42
#define KnuckleWalkSizeY 38
#define KnuckleRollSizeY 31
#define KnuckleSitSizeY 25
#define KnuckleBreakSizeY 38
#define KnuckleSpinningSizeX 50
#define KnuckleSpinningSizeY 24
#define KnuckleClimbSizeY 38

#define TailSize 33
#define TailCrouchSize 20

#define TileSizeX  256
#define TileSizeY  256
#define ChangeWtoR 500
#define JUMP_SPEED 900

#define DIR_LEFT 0
#define DIR_RIGHT 1

#define DT TimeManager::Manager().GetDelatTime()

#define SAFE_DEL(T) if( T != NULL) delete T; T= NULL;

#define SAFE_DEL_T(T,_P ,m)\
	T::iterator iter = _P.begin();\
	for(iter; iter!= _P.end(); ++iter) \
	{\
	  if(m == false)\
		SAFE_DEL(*iter);\
	  else if (m == true)\
		SAFE_DEL(iter->second);\
	}



struct fPOINT
{
	float x;
	float y;

	fPOINT operator + (const fPOINT& _other)
	{
		return fPOINT{ x + _other.x, y + _other.y };
	}

	fPOINT operator - (const fPOINT& _other)
	{
		return fPOINT{ x - _other.x, y - _other.y };
	}
};


enum STAGE_TYPE
{
	STAGE_LOGO_SEGA,
	STAGE_LOGO,
	STAGE_SELECT,
	STAGE_MAPTOOL,
	STAGE_START,
	STAGE_ICE,
	STAGE_00,
	STAGE_01,
	STAGE_FINAL,
	STAGE_FINISH,
	STAGE_END,
};

enum OBJ_TYPE
{
	Obj_TILE,
	OBJ_FIRE,
	OBJ_GOAL,
	OBJ_BOSS,
	OBJ_BOSS_01,
	Obj_PLAYER,
	Obj_MONSTER,
	OBJ_SPRING,
	OBJ_ITEM,
	OBJ_SHIELD,
	Obj_UI,
	OBJ_NILL,
	OBJ_RING,
	OBJ_EFFECT,
	OBJ_FEATURE,
	OBJ_STONE,
	OBJ_MISSILE,
	Obj_END
};

enum PLAYER_STATE
{
	PLAYER_STOP,
	PLAYER_iDLE,
	PLAYER_JUMP,
	PLAYER_SIT,
	PLAYER_LOOKUP,
	PLAYER_RIGHTRUN,
	PLAYER_LEFTRUN,
	PLAYER_RIGHTWalK,
	PLAYER_LEFTWalK,
	PLAYER_RIGHTBREAK,
	PLAYER_LEFTBREAK,
	PLAYER_SPINNING,
	PLAYER_BREAK,
	PLAYER_DROP,
	PLAYER_SPIN,
	PLAYER_ROLL,
	PLAYER_MOVE,
	PLAYER_SPINMOVE,
	PLAYER_RIGHTPUSH,
	PLAYER_LEFTPUSH,
	PLAYER_RIGHTCLIMB,
	PLAYER_LEFTCLIMB,
	PLAYER_SPRINGJUMP,
	PLAYER_ENDCLIMB_00,
	PLAYER_ENDCLIMB_01,
	PLAYER_ENDCLIMB_02,
	PLAYER_HITTED,
	PLAYER_FLYING,
	PLAYER_FIRESKILL,
	PLAYER_THUNDERSKILL,
	PLAYER_WATERSKILL,
	PLAYER_FINISH,
	PLAYER_TRANSFORM,
	PLAYER_FINALSTAGE,
	PLAYER_END
};

enum ANI_STATE
{
	ANI_STOP,
	ANI_iDLE,
	ANI_JUMP,
	ANI_SIT,
	ANI_LOOKUP,
	ANI_RUN,
	ANI_WALK,
	ANI_CROUCH,
	ANI_BREAK,
	ANI_SPIN,
	ANI_ROLL,
	ANI_SPINING,
	ANI_SPiNINGTURN_00,
	ANI_SPiNINGTURN_01,
	ANI_SPiNINGTURN_02,
	ANI_CLIMB,
	ANI_DROP,
	ANI_PUSH,
	ANI_ENDCLIMB,
	ANI_SPRINGJUMP,
	ANI_HITTED,
	ANI_RIGHTJUMP,
	ANI_LEFTJUMP,
	ANI_FLY,
	ANI_VICTORY,
	ANI_TRANSFORM,
	ANI_FINALSTAGE,
	ANI_END
};

enum JUMP_STATE
{
	JUMP_ON,
	JUMP_OFF,
};

enum RUN_STATE
{
	RUN_ON,
	RUN_SLOW,
	RUN_STOP,
	RUN_OFF,
};

enum COL_TYPE
{
	COL_RECT,
	COL_CIRCLE,
	COL_END
};

enum CHECK_TYPE
{
	CHECK_TOP,
	CHECK_BOTTOM,
	CHECK_RIGHT,
	CHECK_LEFT,
	CHECK_END
};

enum SHIELD_STATE
{
	SHIELD_FIRE,
	SHIELD_WATER,
	SHIELD_THUNDER,
	SHIELD_END
};

enum MODE_STATE
{
	MODE_PLAY,
	MODE_EDIT,
	MODE_END
};
enum EDIT_MODE
{
	EDIT_RING,
	EDIT_NILL,
	EDIT_SPRING_UP,
	EDIT_SPRING_RIGHT,
	EDIT_SPRING_LEFT,

	EDIT_FIREITEM,
	EDIT_WATERITEM,
	EDIT_THUNDERITEM,
	EDIT_RINGITEM,
	EDIT_LIFEITEM,

	EDIT_NILLWALL_RIGHT,
	EDIT_NILLWALL_LEFT,

	EDIT_END
};

enum Charactor_Mode
{
	KNUCKLE_MODE,
	TAIL_MODE,
	SONIC_MODE,
	END_MODE
};

enum BOSS_STATE
{
	BOSS_APPEAR,
	BOSS_ROLL,
	BOSS_IDLE,
	BOSS_RIGHTDASH,
	BOSS_LEFTDASH,
	BOSS_DASHTURN,
	BOSS_ROLLJUMP,
	BOSS_DIE,
	BOSS_END
};

enum SILVER_ANIM
{
	SILVER_IDLE,
	SILVER_ROLL,
	SILVER_DASH,
	SILVER_DASHTURN,
	SILVER_END
};

enum MOVE_STATE
{
	MOVE_TOP,
	MOVE_BOTTOM,
	MOVE_RIGHT,
	MOVE_LEFT,
	MOVE_END

};

enum COL_DIRECT
{
	COL_TOP,
	COL_BOTTOM,
	COL_RIGHT,
	COL_LEFT,
};

struct ColPair
{
	OBJ_TYPE left;
	OBJ_TYPE right;
};

union COL_ID
{
	DWORD dwID;
	struct
	{
		WORD leftID;
		WORD rightID;
	};
};

class Texture;

struct AniFrame
{
	Texture*	m_pTexture;		// 참조하는 텍스쳐	
	fPOINT		m_ptStartPos;	// 텍스쳐에서 참조하는 위치(픽셀)
	fPOINT		m_ptCropSize;	// Crop Size
	int			m_iDir;			// 이미지 참조 방향
	float		m_fInteval;     // 해당 이미지 유지 시간	
	DWORD		m_RGB;
	bool        m_Fin;
};

