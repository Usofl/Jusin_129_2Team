#pragma once
#include "Obj.h"
#include "Portal.h"

class CPortalFactory
{
public:

	CPortalFactory()
	{
	}

	~CPortalFactory()
	{
	}

public:
	static CObj* Create(float _fX, float _fY, float _fPortalX, float _fPortalY)
	{
		CObj* _Temp = new CPortal(_fPortalX, _fPortalY);
		_Temp->Initialize();
		_Temp->Set_Pos(_fX, _fY);
		return _Temp;
	}
};

