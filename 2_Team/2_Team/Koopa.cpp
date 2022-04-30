#include "stdafx.h"
#include "Koopa.h"


CKoopa::CKoopa()
{
}


CKoopa::~CKoopa()
{
}

void CKoopa::Initialize(void)
{
	m_tInfo.fX = 600.f;
	m_tInfo.fY = 300.f;
	
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 300.f;

	m_iHp = 10;

	m_iAtt = 3;

	m_fSpeed = 2.f;
}

const int& CKoopa::Update(void)
{
	if (m_iHp <= 0)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CKoopa::Late_Update(void)
{
	if (550 >= m_tRect.left || WINCX - 50 <= m_tRect.right)
	{
		m_fSpeed *= -1.f;
	}
}

void CKoopa::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top - 20, m_tRect.right, m_tRect.bottom - 20);
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CKoopa::Release(void)
{
}
