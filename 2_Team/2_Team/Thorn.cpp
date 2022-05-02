#include "stdafx.h"
#include "Thorn.h"
#include "ObjMgr.h"


CThorn::CThorn()
	: m_bBoss(false)
{
}


CThorn::~CThorn()
{
}

void CThorn::Initialize(void)
{
	m_tInfo.fX = 50.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 600.f;

	m_fSpeed = 0.6f;
}

const int & CThorn::Update(void)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (!m_bBoss)
	{
		m_tInfo.fX += m_fSpeed;
	}

	Update_Rect();
	return OBJ_NOEVENT;

}

void CThorn::Late_Update(void)
{
	if (PLAYER->Get_Info().fX > 5550)
	{
		m_tInfo.fX = 5400;
		m_bBoss = true;
	}
}

void CThorn::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	MoveToEx(_hDC, LONG(m_tInfo.fX - 50 + iScrollX), LONG(m_tInfo.fY - 300) + iScrollY, nullptr);
	LineTo(_hDC, LONG(m_tInfo.fX - 50 + iScrollX), LONG(m_tInfo.fY + 300) + iScrollY);
	
	MoveToEx(_hDC, m_tInfo.fX - 50+ iScrollX, m_tInfo.fY - 300 + iScrollY, nullptr);
	LineTo(_hDC, m_tInfo.fX + 50+ iScrollX, m_tInfo.fY - 300 + iScrollY);

	//MoveToEx(_hDC, m_tInfo.fX + 50 + iScrollX, m_tInfo.fY - 300 , nullptr);
	//LineTo(_hDC, m_tInfo.fX + iScrollX, m_tInfo.fY - 300 + 30);
	for (int i = 0; i < 10; ++i)
	{
		MoveToEx(_hDC, LONG(m_tInfo.fX + 50 + iScrollX), LONG(m_tInfo.fY - 300 + i*60) + iScrollY, nullptr);
		LineTo(_hDC, LONG(m_tInfo.fX + iScrollX), LONG(m_tInfo.fY - 300 + 30 + i*60) + iScrollY);

		MoveToEx(_hDC, m_tInfo.fX + iScrollX, m_tInfo.fY - 300 + 30 + i * 60 + iScrollY, nullptr);
		LineTo(_hDC, m_tInfo.fX + 50 + iScrollX, m_tInfo.fY - 300 + 60 + i * 60 + iScrollY);
	}

	MoveToEx(_hDC, LONG(m_tInfo.fX - 50+ iScrollX), LONG(m_tInfo.fY + 300) + iScrollY, nullptr);
	LineTo(_hDC, LONG(m_tInfo.fX + 50+ iScrollX), LONG(m_tInfo.fY + 300) + iScrollY);


}

void CThorn::Release(void)
{
}
