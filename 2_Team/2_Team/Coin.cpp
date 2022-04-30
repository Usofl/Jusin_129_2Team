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
	//m_tInfo.fX = 400;
	//m_tInfo.fY = 150;
	m_tInfo.fCX = 20;
	m_tInfo.fCY = 20;

	m_fAngle = 1.f;
}

const int & CCoin::Update(void)
{
	m_fAngle += 4.f;
	return 0;
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
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	Ellipse(_hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CCoin::Release(void)
{
}
