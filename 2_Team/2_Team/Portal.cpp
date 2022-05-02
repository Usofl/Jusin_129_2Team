#include "stdafx.h"
#include "Portal.h"


CPortal::CPortal()
{
}


CPortal::~CPortal()
{
}

void CPortal::Initialize(void)
{
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;
}

const int & CPortal::Update(void)
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPortal::Late_Update(void)
{
}

void CPortal::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();
	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
	OldBrush = (HBRUSH)SelectObject(_hDC, MyBrush);
	Ellipse(_hDC, m_tRect.left + iScrollX - 25, m_tRect.top + iScrollY-25, m_tRect.right + iScrollX+25, m_tRect.bottom + iScrollY+25);

	SelectObject(_hDC, OldBrush);
	DeleteObject(MyBrush);
}

void CPortal::Release(void)
{
}
