#include "stdafx.h"
#include "Gomu_Fistol.h"


CGomu_Fistol::CGomu_Fistol()
{
}

CGomu_Fistol::CGomu_Fistol(const INFO & _tInfo)
{
	m_tInfo.fX = _tInfo.fX;
	m_tInfo.fY = _tInfo.fY;
}


CGomu_Fistol::~CGomu_Fistol()
{
}

void CGomu_Fistol::Initialize(void)
{
	m_tInfo.fCX = 75.f;
	m_tInfo.fCY = 5.f;

	m_iHp = 1;
	m_fSpeed = 3.f;
}

const int & CGomu_Fistol::Update(void)
{
	if (!m_iHp)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CGomu_Fistol::Late_Update(void)
{
}

void CGomu_Fistol::Render(HDC _hDC)
{
	MoveToEx(_hDC, m_tRect.left + 10, (LONG)m_tInfo.fY, nullptr);
	LineTo(_hDC, m_tRect.right, (LONG)m_tInfo.fY);
}

void CGomu_Fistol::Release(void)
{
}
