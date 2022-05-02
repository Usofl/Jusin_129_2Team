#include "stdafx.h"
#include "Stamina.h"


CStamina::CStamina()
{
}


CStamina::~CStamina()
{
}

void CStamina::Initialize(void)
{
	m_tInfo.fX = 3750;
	m_tInfo.fY = 320;
	m_tInfo.fCX = 30;
	m_tInfo.fCY = 15;
	m_iItemtype = ITEM_STAMINA;
}

const int & CStamina::Update(void)
{
	if (m_iHp <= 0)
		return OBJ_DEAD;
	Update_Rect();
	return OBJ_NOEVENT;
}


void CStamina::Late_Update(void)
{
}

void CStamina::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
	OldBrush = (HBRUSH)SelectObject(_hDC, MyBrush);
	Ellipse(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	SelectObject(_hDC, OldBrush);
	DeleteObject(MyBrush);

	MoveToEx(_hDC, m_tRect.left + 14 + iScrollX, m_tRect.top + iScrollY, nullptr);
	LineTo(_hDC, m_tRect.left + 14 + iScrollX, m_tRect.bottom + iScrollY);
	MoveToEx(_hDC, m_tRect.left + 16 + iScrollX, m_tRect.top + iScrollY, nullptr);
	LineTo(_hDC, m_tRect.left + 16 + iScrollX, m_tRect.bottom + iScrollY);
}

void CStamina::Release(void)
{
}
