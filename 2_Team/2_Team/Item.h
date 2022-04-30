#pragma once
#include "NotBeing.h"
class CItem :
	public CNotBeing
{
public:
	CItem();
	virtual ~CItem();

	virtual void			Initialize(void)		PURE;
	virtual const int&		Update(void)		PURE;
	virtual void			Late_Update(void)		PURE;
	virtual void			Render(HDC _hDC)	PURE;
	virtual void			Release(void)		PURE;
};

