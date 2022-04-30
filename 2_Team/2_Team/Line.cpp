#include "stdafx.h"
#include "Line.h"
#include "Include.h"


CLine::CLine()
{
}

CLine::CLine(const LINEPOINT& tLeft, const LINEPOINT& tRight)
	:m_tLine(tLeft, tRight)
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
	MoveToEx(_hDC, (LONG)m_tLine.tLeft.fX, (LONG)m_tLine.tLeft.fY, nullptr);
	LineTo(_hDC, (LONG)m_tLine.tRight.fX, (LONG)m_tLine.tRight.fY);
}

void CLine::Release(void)
{
}