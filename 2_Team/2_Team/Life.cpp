#include "stdafx.h"
#include "Life.h"


CLife::CLife()
	:m_iItemtype(ITEM_LIFE)
{
}


CLife::~CLife()
{
}

void CLife::Initialize(void)
{
	m_tRect.left = 700;
	m_tRect.right = 725;
	m_tRect.top = 350;
	m_tRect.bottom = 355;
	m_iItemtype = ITEM_LIFE;
}

const int & CLife::Update(void)
{
	if (m_iHp <= 0)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CLife::Late_Update(void)
{
}

void CLife::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left - 2, m_tRect.top - 5, m_tRect.right + 2, m_tRect.bottom + 15);
	/*Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Rectangle(_hDC, m_tRect.left + 20, m_tRect.top, m_tRect.right, m_tRect.bottom + 10);
	MoveToEx(_hDC, m_tRect.left + 13, m_tRect.bottom, nullptr);
	LineTo(_hDC, m_tRect.left + 20, m_tRect.bottom + 3);*/
}

void CLife::Release(void)
{
}
