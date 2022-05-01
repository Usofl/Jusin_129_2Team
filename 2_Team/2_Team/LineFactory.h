#pragma once
#include "Obj.h"
#include "Include.h"
#include "Line.h"

class CLineFactory
{
public:

	CLineFactory()
	{
	}

	~CLineFactory()
	{
	}

public:

	static CObj* Create_Line(const LINEPOINT& _Left, const LINEPOINT& _Right)
	{
		CObj* _Temp = new CLine(_Left, _Right);

		return _Temp;
	}

	static CObj* Create_Line(const LINE& _tLine)
	{
		CObj* _Temp = new CLine(_tLine);

		return _Temp;
	}


	
};

