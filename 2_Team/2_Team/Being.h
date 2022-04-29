#pragma once
#include "Obj.h"
class CBeing :
	public CObj
{
public:
	CBeing();
	virtual ~CBeing();

	

	// CObj을(를) 통해 상속됨
	virtual void			Initialize		(void) PURE;
	virtual const int&		Update			(void) PURE;
	virtual void			Late_Update		(void) PURE;
	virtual void			Render			(HDC _hDC) PURE;
	virtual void			Release			(void) PURE;

};

