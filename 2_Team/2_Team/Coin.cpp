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
	m_tInfo.fCX = 19;
	m_tInfo.fCY = 20;
	m_tCoinInfo.fCX = 3;
	m_tCoinInfo.fCY = 16;

	m_iHp = 1;
	m_fAngle = 1.f;
}

const int & CCoin::Update(void)
{
	if (m_iHp <= 0)
		return OBJ_DEAD;

	m_fAngle += 3.f;
	return OBJ_NOEVENT;
}

void CCoin::Late_Update(void)
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.fCX * sinf(RADIAN(m_fAngle))));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.fCX * sinf(RADIAN(m_fAngle))));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.fCY));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.fCY));

	m_tCoin.left = (LONG)(m_tInfo.fX - (m_tCoinInfo.fCX * sinf(RADIAN(m_fAngle))));
	m_tCoin.right = (LONG)(m_tInfo.fX + (m_tCoinInfo.fCX * sinf(RADIAN(m_fAngle))));
	m_tCoin.top = (LONG)(m_tInfo.fY - (m_tCoinInfo.fCY));
	m_tCoin.bottom = (LONG)(m_tInfo.fY + (m_tCoinInfo.fCY));
}

void CCoin::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();
	Ellipse(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	Rectangle(_hDC, m_tCoin.left + iScrollX, m_tCoin.top + iScrollY, m_tCoin.right + iScrollX, m_tCoin.bottom + iScrollY);
}

void CCoin::Release(void)
{
}

void const CCoin::Dead(void)
{
	m_iHp = 0;
}
