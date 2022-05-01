#include "stdafx.h"
#include "Gun.h"


CGun::CGun()
	:m_iItemtype(ITEM_GUN)
{
}


CGun::~CGun()
{
}

void CGun::Initialize(void)
{
	m_tRect.left = 450;
	m_tRect.right = 475;
	m_tRect.top = 350;
	m_tRect.bottom = 355;
	
}

const int & CGun::Update(void)
{
	if (m_iHp <= 0)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CGun::Late_Update(void)
{
}

void CGun::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	Rectangle(_hDC, m_tRect.left - 2 + iScrollX, m_tRect.top - 5 + iScrollY, m_tRect.right + 2 + iScrollX, m_tRect.bottom + 15 + iScrollY);
	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	Rectangle(_hDC, m_tRect.left + 20 + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + 10 + iScrollY);
	MoveToEx(_hDC, m_tRect.left + 13 + iScrollX, m_tRect.bottom + iScrollY, nullptr);
	LineTo(_hDC, m_tRect.left + 20 + iScrollX, m_tRect.bottom + 3 + iScrollY);
}

void CGun::Release(void)
{
}
