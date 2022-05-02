#include "stdafx.h"
#include "Counter_Bullet.h"


CCounter_Bullet::CCounter_Bullet()
{
}

CCounter_Bullet::CCounter_Bullet(const INFO& _tInfo)
	: m_fCounter_Time(0.f)
{
	m_tInfo = _tInfo;

	m_fSpeed = 15.f;
}

CCounter_Bullet::~CCounter_Bullet()
{
	Release();
}

void CCounter_Bullet::Initialize(void)
{
	m_iHp = 1;
	m_fAngle = ACOSF(m_tInfo.fX, m_tInfo.fY, PLAYER->Get_Info().fX, PLAYER->Get_Info().fY);

	if (m_tInfo.fY > PLAYER->Get_Info().fY)
	{
		m_fAngle *= -1.f;
	}

	if (m_tInfo.fX > PLAYER->Get_Info().fX)
	{
		m_iReverse = -1;
	}
	else
	{
		m_iReverse = 1;
	}
}

const int & CCounter_Bullet::Update(void)
{
	if (0 >= m_iHp)
	{
		return OBJ_DEAD;
	}

	m_fCounter_Time += 0.2f;

	float fy = m_fSpeed * m_fCounter_Time * sinf(m_fAngle) - (0.5f * GRAVITY * (m_fCounter_Time * m_fCounter_Time));
	float fx = (m_fSpeed * 1.5f) * cosf(m_fAngle);

	m_tInfo.fX += (fx * m_iReverse);
	m_tInfo.fY -= fy;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCounter_Bullet::Late_Update(void)
{
	if (m_tInfo.fY > WINCY)
	{
		m_iHp = 0;
	}
}

void CCounter_Bullet::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CCounter_Bullet::Release(void)
{
}
