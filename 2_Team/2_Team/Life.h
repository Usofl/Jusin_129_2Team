#pragma once
#include "Item.h"
#include "ScrollMgr.h"

class CLife :
	public CItem
{
public:
	CLife();
	~CLife();
public:
	virtual void			Initialize(void);
	virtual const int&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC _hDC);
	virtual void			Release(void);
	virtual int Itemtype(void) { return m_iItemtype; }
	virtual void PlayerColiision(void) {};

private:
	int m_iItemtype;

	float  m_iShake;
};

