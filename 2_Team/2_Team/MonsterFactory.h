#pragma once
#include "Obj.h"
#include "Cloud.h"
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
		case CLOUD_TURTLE:
			pObj = new CCloud;
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

};
