#include "stdafx.h"
#include "Room.h"


CRoom::CRoom()
{
}


CRoom::~CRoom()
{
}

void CRoom::Initialize(void)
{
	m_tInfo.fX = 1200;
	m_tInfo.fY = 300;
	m_tInfo.fCX = 200;
	m_tInfo.fCY = 300;
	m_iItemtype = ITEM_ROOM;
}

const int & CRoom::Update(void)
{
	if (m_iHp == 0)
	{

	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CRoom::Late_Update(void)
{
}

void CRoom::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	Ellipse(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom - 50 + iScrollY);//문위
	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + 100 + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);//문
	MoveToEx(_hDC, m_tRect.left + 100 + iScrollX, m_tRect.top + 100 + iScrollY, nullptr);//문중앙
	LineTo(_hDC, m_tRect.left + 100 + iScrollX, m_tRect.bottom + iScrollY);

	Rectangle(_hDC, m_tRect.left + 70 + iScrollX, m_tRect.top + 200 + iScrollY, m_tRect.right - 70 + iScrollX, m_tRect.bottom - 100 + iScrollY);
}
// 500 

void CRoom::Release(void)
{
}
