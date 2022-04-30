#include "stdafx.h"
#include "M_Bullet.h"


CM_Bullet::CM_Bullet()
{
}


CM_Bullet::~CM_Bullet()
{
	Release();
}

void CM_Bullet::Initialize(void)
{
	m_iHp = 1;

	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 2.f;

	m_fShootPower = 10.f;
	m_fShootTime = 0.f;
}

const int& CM_Bullet::Update(void)
{
	if (!m_iHp)
		return OBJ_DEAD;

	//m_tInfo.fX += m_fSpeed;
	m_fShootTime += 0.2f;
	m_tInfo.fY -= m_fShootPower * m_fShootTime - (GRAVITY * m_fShootTime * m_fShootTime * 0.5f);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CM_Bullet::Late_Update(void)
{

}

void CM_Bullet::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CM_Bullet::Release(void)
{
}
