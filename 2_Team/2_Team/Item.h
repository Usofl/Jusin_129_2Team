#pragma once
#include "NotBeing.h"
class CItem :
	public CNotBeing
{
public:
	CItem();
	virtual ~CItem();

	virtual void			Initialize(void)			PURE;
	virtual const int&		Update(void)				PURE;
	virtual void			Late_Update(void)			PURE;
	virtual void			Render(HDC _hDC)			PURE;
	virtual void			Release(void)				PURE;
	virtual void PlayerColiision(void)					PURE;

	virtual int Itemtype(void) { return m_iItemtype; }

	void Set_Hp(void) { m_iHp = 0; }

private:
	int  m_iItemtype;
};

