#include "stdafx.h"
#include "Line.h"
#include "Include.h"


CLine::CLine()
{
}

CLine::CLine(const LINEPOINT& tLeft, const LINEPOINT& tRight)
	: m_tLine(tLeft, tRight)
	, m_bRender(true)
{

}

CLine::~CLine()
{
}

void CLine::Initialize(void)
{
}

const int& CLine::Update(void)
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return OBJ_NOEVENT;
}

void CLine::Late_Update(void)
{
}

void CLine::Render(HDC _hDC)
{
	if (m_bRender)
	{
		int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
		int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

		MoveToEx(_hDC, (LONG)m_tLine.tLeft.fX + iScrollX, (LONG)m_tLine.tLeft.fY + iScrollY, nullptr);
		LineTo(_hDC, (LONG)m_tLine.tRight.fX + iScrollX, (LONG)m_tLine.tRight.fY + iScrollY);
	}
}

void CLine::Release(void)
{
}