#pragma once
#include "Item.h"
#include "Include.h"

class CCoin :
	public CItem
{
public:
	CCoin();
	CCoin(float _m_fX, float _m_fY);
	virtual ~CCoin();

	virtual void			Initialize(void);
	virtual const int&		Update(void);
	virtual void			Late_Update(void);
	virtual void			Render(HDC _hDC);
	virtual void			Release(void);
	virtual void PlayerColiision(void) {};
	void	const			Dead(void);

	INFO	m_tCoinInfo;
	RECT	m_tCoin;
};

