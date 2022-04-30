#pragma once
#include "Obj.h"
#include "M_Cloud.h"
#include "Warrior.h"
#include "Koopa.h"


class CMonsterFactory
{
public:

	CMonsterFactory()	{}
	~CMonsterFactory()	{}

public:
	static CObj*	Create_Monster(MONSTER_TYPE _Type)
	{
		CObj* pObj = nullptr;
		switch (_Type)
		{
		case M_Cloud_TURTLE:
			pObj = new CM_Cloud;
			break;
		case WARRIOR_TURTLE:
			pObj = new CWarrior;
			break;
		case BOSS_KOOPA:
			pObj = new CKoopa;
			break;
		}
		pObj->Initialize();

		return pObj;

	}

	static CObj*	Create_Bullet(float _fX, float _fY)
	{
		CObj*	pObj = new CCloud_Bullet;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		
		return pObj;
	}
};

