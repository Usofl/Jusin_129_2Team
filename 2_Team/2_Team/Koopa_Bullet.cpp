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
}

void CKoopa_Bullet::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CKoopa_Bullet::Release(void)
{
}
