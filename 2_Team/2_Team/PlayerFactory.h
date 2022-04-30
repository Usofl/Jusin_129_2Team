#pragma once
#include "Obj.h"

class CPlayerFactory
{
public:

	CPlayerFactory()
	{
	}

	~CPlayerFactory()
	{
	}

public:
	static CObj* Create_Player()
	{
		CObj* Temp = new CPlayer;
		Temp->Initialize();
		return Temp;
	}
};

