#include "stdafx.h"
#include "Coin.h"


CCoin::CCoin()
{
}

CCoin::CCoin(float _m_fX, float _m_fY)
{
	m_tInfo.fX = _m_fX;
	m_tInfo.fY = _m_fY;
}


CCoin::~CCoin()
{
}

void CCoin::Initialize(void)
{
	m_tInfo.fCX = 20;
	m_tInfo.fCY = 20;

	m_iHp = 1;
	m_fAngle = 1.f;
}

const int & CCoin::Update(void)
{
	if (m_iHp <= 0)
		return OBJ_DEAD;

	m_fAngle += 4.f;
	return OBJ_NOEVENT;
}

void CCoin::Late_Update(void)
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.fCX * sinf((m_fAngle * PI) / 180.f)));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.fCX * sinf((m_fAngle * PI) / 180.f)));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.fCY));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.fCY));
}

void CCoin::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CCoin::Release(void)
{
}

void const CCoin::Dead(void)
{
	m_iHp = 0;
}
