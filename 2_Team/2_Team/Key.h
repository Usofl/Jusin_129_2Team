#pragma once
#include "Item.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

class CKey :
	public CItem
{
public:
	CKey();
	~CKey();

	virtual void			Initialize(void);
	virtual const int&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC _hDC);
	virtual void			Release(void);
	virtual int Itemtype(void) { return m_iItemtype; }

	virtual void PlayerColiision(void);

private:
	int m_iItemtype;
	INFO m_tPlayerInfo;

	float  m_fShake;
	int	   m_iTime;
	bool   m_bCheck;

	bool  m_bPlayercolli;

	float m_fJumpPower;
	float m_fJumpTime;
};

