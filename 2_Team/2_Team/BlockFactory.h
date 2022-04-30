#pragma once
#include "Obj.h"
#include "Block.h"

class CBlockFactory
{
public:
	CBlockFactory() {}
	~CBlockFactory() {}

public:
	static CObj* Create(float _fX, float _fY)
	{
		CObj* _Temp = new CBlock;
		_Temp->Initialize();
		_Temp->Set_Pos(_fX, _fY);
		return _Temp;
	}
};