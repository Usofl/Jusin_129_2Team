#pragma once
#include "Obj.h"
#include "Coin.h"

class CoinFactory
{
public:
	CoinFactory()
	{
	}
	~CoinFactory()
	{
	}
public:
	static CObj* Create_Coin()
	{
		CObj* Temp = new CCoin;
		Temp->Initialize();
		return Temp;
	}
	static CObj* Create_Coin(float _fX,float _fY)
	{
		CObj* Temp = new CCoin(_fX,_fY);
		Temp->Initialize();
		return Temp;
	}
};