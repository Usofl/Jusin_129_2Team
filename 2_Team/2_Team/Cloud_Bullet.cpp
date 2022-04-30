#include "stdafx.h"
#include "Cloud_Bullet.h"
#include "Collision.h"
#include "ObjMgr.h"
#include "Player.h"


CCloud_Bullet::CCloud_Bullet()
{
}


CCloud_Bullet::~CCloud_Bullet()
{
	Release();
}

void CCloud_Bullet::Initialize(void)
{
	m_iHp = 1;

	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fShootPower = 6.f;
	m_fShootTime = 0.f;
}

const int& CCloud_Bullet::Update(void)
{
	if (!m_iHp)
		return OBJ_DEAD;

	m_fShootTime += 0.05f;
	m_tInfo.fY -= m_fShootPower * m_fShootTime - (GRAVITY * m_fShootTime * m_fShootTime * 0.5f);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCloud_Bullet::Late_Update(void)
{
}

void CCloud_Bullet::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CCloud_Bullet::Release(void)
{
}
