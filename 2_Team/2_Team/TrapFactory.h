#pragma once
#include "Obj.h"
#include "Thorn.h"
class CTrapFactory
{
public:

	CTrapFactory()
	{
	}

	~CTrapFactory()
	{
	}
public:
	static CObj* Create_Thorn()
	{
		CObj* _Temp = new CThorn;
		_Temp->Initialize();
		return _Temp;
	}
};

