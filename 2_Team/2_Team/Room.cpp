#include "stdafx.h"
#include "Room.h"
#include "ObjMgr.h"
#include "UiMgr.h"


CRoom::CRoom()
{
}


CRoom::~CRoom()
{
}

void CRoom::Initialize(void)
{
	m_tInfo.fX = 5600;
	m_tInfo.fY = 300;
	m_tInfo.fCX = 200;
	m_tInfo.fCY = 300;
	m_iItemtype = NOTBEING_ROOM;
}

const int & CRoom::Update(void)
{


	Update_Rect();

	return OBJ_NOEVENT;
}

void CRoom::Late_Update(void)
{
	//if(OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Rect().left)
}

void CRoom::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	Ellipse(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom - 50 + iScrollY);//문위
	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + 100 + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);//문
	MoveToEx(_hDC, m_tRect.left + 100 + iScrollX, m_tRect.top + 100 + iScrollY, nullptr);//문중앙
	LineTo(_hDC, m_tRect.left + 100 + iScrollX, m_tRect.bottom + iScrollY);

	Rectangle(_hDC, m_tRect.left + 80 + iScrollX, m_tRect.top + 200 + iScrollY, m_tRect.right - 80 + iScrollX, m_tRect.bottom - 70 + iScrollY);
	Ellipse(_hDC, m_tRect.left + 95 + iScrollX, m_tRect.top + 220 + iScrollY, m_tRect.right - 95 + iScrollX, m_tRect.bottom - 90 + iScrollY);
	Rectangle(_hDC, m_tRect.left + 98 + iScrollX, m_tRect.top + 223 + iScrollY, m_tRect.right - 98 + iScrollX, m_tRect.bottom - 85 + iScrollY);
}

void CRoom::Release(void)
{
}
