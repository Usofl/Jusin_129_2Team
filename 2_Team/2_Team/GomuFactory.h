#pragma once
#include "Obj.h"
#include "Gomu_Fistol.h"
#include "Gigant_Fistol.h"
#include "Counter_Bullet.h"

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

	static CObj* Create_Gigant_Fistol(const POINT& _tPoint, const int& _iReverse, const float& _fSize)
	{
		CObj* fistol = new CGigant_Fistol(_tPoint, _iReverse, (unsigned int)_fSize);
		fistol->Initialize();
		return fistol;
	}

	static CObj* Create_Counter_Bullet(const INFO& _tInfo)
	{
		CObj* fistol = new CCounter_Bullet(_tInfo);
		fistol->Initialize();
		return fistol;
	}
};