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
	static CObj* Create_Fistol(const POINT& _tPoint, const int& _iReverse)
	{
		CObj* fistol = new CGomu_Fistol(_tPoint, _iReverse);
		fistol->Initialize();
		return fistol;
	}
};