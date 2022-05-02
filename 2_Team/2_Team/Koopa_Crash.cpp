#include "stdafx.h"
#include "Koopa_Crash.h"


CKoopa_Crash::CKoopa_Crash()
{
}


CKoopa_Crash::~CKoopa_Crash()
{
}

void CKoopa_Crash::Initialize(void)
{
	m_iHp = 1;
	m_iAtt = 3;

	m_tInfo.fCX = 15;
	m_tInfo.fCY = 15;

	m_fShootPower = 10.f;
	m_fShootTime = 0.f;
	m_fSpeed = 5.f;
}

const int & CKoopa_Crash::Update(void)
{
	if (!m_iHp)
	{
		return OBJ_DEAD;
	}

	m_fShootTime += 0.2;
	m_tInfo.fY -= m_fShootPower * m_fShootTime * sinf(m_fAngle) - (7.5 * m_fShootTime * m_fShootTime * 0.5f);

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CKoopa_Crash::Late_Update(void)
{
	if (m_tInfo.fY + (m_tInfo.fCY * 1.5) >= WINCY)
	{
		Set_Hp(0);
	}
}

void CKoopa_Crash::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CKoopa_Crash::Release(void)
{
}
