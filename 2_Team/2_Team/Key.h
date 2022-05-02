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
	bool GameOver() { return m_bPlayer; }

private:
	int m_iItemtype;
	INFO m_tPlayerInfo;

	float  m_fShake;
	int	   m_iTime;
	
	int    m_iX;
	int    m_iY;

	bool   m_bCheck;
	bool   m_bKey;
	bool   m_bPlayer;

	bool  m_bPlayercolli;
	bool	m_bBlockCol;

	float m_fJumpPower;
	float m_fJumpTime;
};

