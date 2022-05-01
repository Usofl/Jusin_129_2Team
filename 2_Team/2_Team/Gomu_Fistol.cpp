#include "stdafx.h"
#include "Gomu_Fistol.h"


CGomu_Fistol::CGomu_Fistol()
{
}

CGomu_Fistol::CGomu_Fistol(const POINT & _tPoint, const int& _iReverse)
{
	m_tInfo.fX = (float)_tPoint.x;
	m_tInfo.fY = (float)_tPoint.y;
	m_iReverse = _iReverse;
}


CGomu_Fistol::~CGomu_Fistol()
{
}

void CGomu_Fistol::Initialize(void)
{
	m_tInfo.fCX = 75.f + Random_Num(-10, 10);
	m_tInfo.fCY = 5.f;

	m_fSpeed = 3.f;
	m_uiArea = (unsigned int)(m_tInfo.fCX / m_fSpeed) - 7;

	m_iHp = 1;
}

const int & CGomu_Fistol::Update(void)
{
	if (!m_iHp)
	{
		return OBJ_DEAD;
	}

	if (m_uiArea)
	{
		m_tInfo.fX += (m_fSpeed * m_iReverse);
		m_AreaStack.push(m_tInfo.fX);
		--m_uiArea;
	}
	else
	{
		m_tInfo.fX = m_AreaStack.top();
		m_AreaStack.pop();
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CGomu_Fistol::Late_Update(void)
{
	if (m_AreaStack.empty())
	{
		m_iHp = 0;
	}
}

void CGomu_Fistol::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();

	MoveToEx(_hDC, m_tRect.left + 10 + iScrollX, (LONG)m_tInfo.fY, nullptr);
	LineTo(_hDC, m_tRect.right + iScrollX, (LONG)m_tInfo.fY);
}

void CGomu_Fistol::Release(void)
{
}
