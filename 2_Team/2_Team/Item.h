#pragma once
#include "NotBeing.h"
class CItem :
	public CNotBeing
{
public:
	CItem();
	virtual ~CItem();

	virtual void			Initialize(void);
	virtual const int&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC _hDC);
	virtual void			Release(void);
};

