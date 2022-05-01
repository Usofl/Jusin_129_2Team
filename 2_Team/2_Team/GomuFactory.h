#pragma once
#include "Obj.h"
#include "Gomu_Fistol.h"

class CGomuFactory
{
public:
	CGomuFactory()
	{
	}
	~CGomuFactory()
	{
	}
public:
	static CObj* Create_Fistol(const INFO& _tInfo)
	{
		CObj* fistol = new CGomu_Fistol(_tInfo);
		fistol->Initialize();
		return fistol;
	}
};