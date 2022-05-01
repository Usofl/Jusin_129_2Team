#pragma once
#include "Item.h"
class CGun :
	public CItem
{
public:
	CGun();
	virtual ~CGun();
public:
	virtual void			Initialize(void);
	virtual const int&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC _hDC);
	virtual void			Release(void);
	virtual int Itemtype(void) { return m_iItemtype; }

private:
	int m_iItemtype;
};

