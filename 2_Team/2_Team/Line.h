#pragma once
#include "NotBeing.h"
#include "Include.h"

class CLine final :
	public CNotBeing
{
public:
	CLine();
	CLine(const LINEPOINT& tLeft, const LINEPOINT& tRight);
	CLine(std::list<LINEPOINT> _LinePoint_List)
	{
		//for ()
	}
	virtual ~CLine();

	// CNotBeing을(를) 통해 상속됨
	virtual void			Initialize		(void)		override;
	virtual const int&		Update			(void)		override;
	virtual void			Late_Update		(void)		override;
	virtual void			Render			(HDC _hDC)	override;
	virtual void			Release			(void)		override;

	const LINE& Get_LinePoint(void) { return m_tLine; };

private:
	LINE m_tLine;
	bool m_bWall;
};