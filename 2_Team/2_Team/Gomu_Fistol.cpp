#include "stdafx.h"
#include "ObjMgr.h"
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
	m_iAtt = 1;
}

const int & CGomu_Fistol::Update(void)
{
	if (m_uiArea)
	{
		m_tInfo.fX += (m_fSpeed * m_iReverse);
		m_AreaStack.push(m_tInfo.fX);
		--m_uiArea;
	}
	else
	{
		if (0 >= m_iHp && m_AreaStack.empty())
		{
			return OBJ_DEAD;
		}

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
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	MoveToEx(_hDC, m_tRect.left + (10 * m_iReverse) + iScrollX, (LONG)m_tInfo.fY + iScrollY, nullptr);
	LineTo(_hDC, m_tRect.right + iScrollX, (LONG)m_tInfo.fY + iScrollY);
}

void CGomu_Fistol::Release(void)
{
}
