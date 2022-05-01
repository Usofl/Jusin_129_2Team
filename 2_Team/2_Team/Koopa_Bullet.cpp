#include "stdafx.h"
#include "Koopa_Bullet.h"


CKoopa_Bullet::CKoopa_Bullet()
{
}


CKoopa_Bullet::~CKoopa_Bullet()
{
}

void CKoopa_Bullet::Initialize(void)
{
	m_iHp = 1;

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fShootPower = 6.f;
	m_fShootTime = 0.f;
}

const int & CKoopa_Bullet::Update(void)
{
	if (!m_iHp)
		return OBJ_DEAD;


	m_fShootTime += 0.05f;
	m_tInfo.fY -= m_fShootPower * m_fShootTime - (GRAVITY * m_fShootTime * m_fShootTime * 0.5f);
	

	Update_Rect();

	return OBJ_NOEVENT;
}

void CKoopa_Bullet::Late_Update(void)
{
	if (m_tInfo.fY + (m_tInfo.fCY * 1.5) >= WINCY)
	{
		Set_Hp(0);
	}
}

void CKoopa_Bullet::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();

	Ellipse(_hDC, m_tRect.left + iScrollX + iScrollX, m_tRect.top, m_tRect.right + iScrollX + iScrollX, m_tRect.bottom);
}

void CKoopa_Bullet::Release(void)
{
}
