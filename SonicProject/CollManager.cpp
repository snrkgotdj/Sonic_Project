#include "stdafx.h"
#include "CollManager.h"
#include "Stage.h"
#include "StageManager.h"
#include "OBJ.h"
#include "Collider.h"

bool CollManager::Collision(Collider* _left, Collider* _right)
{
	fPOINT leftpos = _left->GetPos();
	fPOINT rightpos = _right->GetPos();
	fPOINT leftsize = _left->GetSize();
	fPOINT rightsize = _right->GetSize();

	if (abs(leftpos.x - rightpos.x) < (leftsize.x + rightsize.x) && abs(leftpos.y - rightpos.y) < (leftsize.y + rightsize.y))
		return true;
	
	else
		return false;
}

void CollManager::update()
{
	Stage* CurStage = StageManager::Manager().GetCurStage();

	for (int i = 0; i < VecColPair.size(); ++i)
	{
		const vector<OBJ*>& leftlist = CurStage->GetListObj(VecColPair[i].left);
		const vector<OBJ*>& rightlist = CurStage->GetListObj(VecColPair[i].right);
		vector<OBJ*>::const_iterator leftiter = leftlist.begin();
		for (; leftiter != leftlist.end(); ++leftiter)
		{
			vector<OBJ*>::const_iterator rightiter = rightlist.begin();
			for (; rightiter != rightlist.end(); ++rightiter)
			{
				if (0 == (*leftiter)->HasCollider() || 0 == (*rightiter)->HasCollider())
					return;

				Collider* leftCol = (*leftiter)->GetCollider();
				Collider* rightCol = (*rightiter)->GetCollider();

				COL_ID col_id;
				col_id.leftID = leftCol->GetID();
				col_id.rightID = rightCol->GetID();

				map<DWORD, bool>::iterator iter = mapColID.find(col_id.dwID);
				if (true == Collision(leftCol, rightCol) )
				{
					if (iter == mapColID.end())
					{
						mapColID.insert(make_pair(col_id.dwID, true));
						leftCol->enterCollision(rightCol);
						rightCol->enterCollision(leftCol);
					}

					if (iter != mapColID.end() && false == (*iter).second)
					{
						(*iter).second = true;
						leftCol->enterCollision(rightCol);
						rightCol->enterCollision(leftCol);
					}

					if (iter != mapColID.end() && true == (*iter).second)
					{
						leftCol->onCollision(rightCol);
						rightCol->onCollision(leftCol);
					}
					if (iter != mapColID.end() && false == (*iter).second)
					{
						(*iter).second = true;
						leftCol->enterCollision(rightCol);
						rightCol->enterCollision(leftCol);
					}
				}

				else if (false == Collision(leftCol, rightCol))
				{
					if (iter != mapColID.end() && true == (*iter).second)
					{
						(*iter).second = false;
						leftCol->exitCollision(rightCol);
						rightCol->exitCollision(leftCol);
					}

					else if (iter == mapColID.end())
					{
						continue;
					}
				}
					
			}
		}
	}
}

void CollManager::clear()
{
	VecColPair.clear();
}

CollManager::CollManager()
{
}


CollManager::~CollManager()
{
}
