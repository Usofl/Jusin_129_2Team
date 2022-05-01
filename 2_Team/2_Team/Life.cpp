#include "stdafx.h"
#include "Life.h"


CLife::CLife()
	:m_iItemtype(ITEM_LIFE), m_iShake(0.1f)
{
}


CLife::~CLife()
{
}

void CLife::Initialize(void)
{
	/*m_tRect.left = 500;
	m_tRect.right = 525;
	m_tRect.top = 345;
	m_tRect.bottom = 370;*/
	m_tInfo.fX = 512.5f;
	m_tInfo.fY = 357.5f;

	m_tInfo.fCX = 25.f;
	m_tInfo.fCY = 25.f;
	m_iItemtype = ITEM_LIFE;
}

const int & CLife::Update(void)
{
	if (m_iHp <= 0)
		return OBJ_DEAD;
	//m_tRect.top += m_iShake;
	//m_tRect.bottom += m_iShake;
	m_tInfo.fY += m_iShake;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CLife::Late_Update(void)
{
	if (m_tRect.top == 341 || m_tRect.bottom == 375)
		m_iShake *= - 1.f;
}

void CLife::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();
	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CLife::Release(void)
{
}
