#include "stdafx.h"
#include "Recovery.h"


CRecovery::CRecovery()
{
}


CRecovery::~CRecovery()
{
}

void CRecovery::Initialize(void)
{
	m_tInfo.fX = 800;
	m_tInfo.fY = 300;
	m_tInfo.fCX = 30;
	m_tInfo.fCY = 10;
	m_iItemtype = ITEM_RECOVERY;
}

const int & CRecovery::Update(void)
{
	if (m_iHp <= 0)
		return OBJ_DEAD;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CRecovery::Late_Update(void)
{
}

void CRecovery::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();
	Rectangle(_hDC, m_tRect.left - 15 + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right + 15 + iScrollX, m_tRect.bottom - 10 + iScrollY);

	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	OldBrush = (HBRUSH)SelectObject(_hDC, MyBrush);
	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top - 10 + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + 10 + iScrollY);
	
	SelectObject(_hDC, OldBrush);
	DeleteObject(MyBrush);
}

void CRecovery::Release(void)
{
}
