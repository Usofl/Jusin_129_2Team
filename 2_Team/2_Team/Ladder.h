#pragma once
#include "Item.h"
#include "ScrollMgr.h"

class CLadder :
	public CItem
{
public:
	CLadder();
	~CLadder();

	virtual void			Initialize(void);
	virtual const int&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC _hDC);
	virtual void			Release(void);
	virtual int Itemtype(void) { return m_iItemtype; }
	virtual void PlayerColiision(void) {};

private:
	RECT m_tColliradder;

	int m_iItemtype;
	int m_iTime;
	bool m_bCount;
};

