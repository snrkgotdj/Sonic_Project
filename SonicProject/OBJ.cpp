#include "stdafx.h"
#include "OBJ.h"
#include "Collider.h"
#include "Animator.h"
#include "KeyManager.h"
#include "Camera.h"



OBJ::OBJ()
	: collider(NULL)
	, Anim(NULL)
	, m_bAlive(true)
	, m_eOBJ_TYPE(Obj_END)
{
}


OBJ::~OBJ()
{
	if (collider != NULL)
	{
		delete collider;
		collider = NULL;
	}
	
	if (Anim != NULL)
	{
		delete Anim;
		Anim = NULL;
	}
}


bool OBJ::isMouseOn(bool _bFixed)
{
	
	if (_bFixed == true)
	{
		fPOINT mouse = KeyManager::Manager().GetMouseCur();
		if (pos.x < mouse.x && mouse.x <= pos.x + size.x
			&&pos.y < mouse.y && mouse.y <= pos.y + size.y)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	else
	{
		fPOINT mouse = KeyManager::Manager().GetMouseCur();
		mouse = Camera::Cam().GetCamMousePos(mouse);

		if (pos.x < mouse.x && mouse.x <= pos.x + size.x
			&&pos.y < mouse.y && mouse.y <= pos.y + size.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void OBJ::Load(FILE * _pFile)
{
	fread(&pos, sizeof(fPOINT), 1, _pFile);
}