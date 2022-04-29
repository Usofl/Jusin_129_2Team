#pragma once
#include "Obj.h"

class CNotBeing
	: public CObj
{
public:
	CNotBeing();
	virtual ~CNotBeing();

	// CObj을(를) 통해 상속됨
	virtual void			Initialize		(void)		PURE;
	virtual const int&		Update			(void)		PURE;
	virtual void			Late_Update		(void)		PURE;
	virtual void			Render			(HDC _hDC)	PURE;
	virtual void			Release			(void)		PURE;
};

