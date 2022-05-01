#pragma once
#include "NotBeing.h"
#include "Include.h"
#include "ScrollMgr.h"

class CLine final :
	public CNotBeing
{
public:
	CLine();
	CLine(const LINEPOINT& tLeft, const LINEPOINT& tRight);
	CLine(const LINE& _tLine) : m_tLine(_tLine), m_bRender(true) {}
	virtual ~CLine();

	// CNotBeing을(를) 통해 상속됨
	virtual void			Initialize		(void)		override;
	virtual const int&		Update			(void)		override;
	virtual void			Late_Update		(void)		override;
	virtual void			Render			(HDC _hDC)	override;
	virtual void			Release			(void)		override;

	const LINE& Get_LinePoint(void) { return m_tLine; }

	void Set_Line(const LINE& _tLine) { m_tLine = _tLine; }

	void Set_Render(const bool& _bRender) {	m_bRender = _bRender; };

private:
	LINE m_tLine;
	bool m_bRender;
};