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
	m_tInfo.fY -= m_fShootPower * m_fShootTime - (7.5 * m_fShootTime * m_fShootTime * 0.5f);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCloud_Bullet::Late_Update(void)
{
	if (m_tInfo.fY + (m_tInfo.fCY * 1.5 ) >= WINCY)
	{
		Set_Hp(0);
	}
}

void CCloud_Bullet::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CCloud_Bullet::Release(void)
{
}
