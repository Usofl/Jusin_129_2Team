#include "stdafx.h"
#include "Thorn.h"


CThorn::CThorn()
{
}


CThorn::~CThorn()
{
}

void CThorn::Initialize(void)
{
	m_tInfo.fX = 50.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCX = 600.f;

	m_fSpeed = 0.3f;
}

const int & CThorn::Update(void)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	m_tInfo.fX += m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;

}

void CThorn::Late_Update(void)
{
}

void CThorn::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();

	MoveToEx(_hDC, LONG(m_tInfo.fX - 50 + iScrollX), LONG(m_tInfo.fY - 300), nullptr);
	LineTo(_hDC, LONG(m_tInfo.fX - 50 + iScrollX), LONG(m_tInfo.fY + 300));
	
	MoveToEx(_hDC, m_tInfo.fX - 50+ iScrollX, m_tInfo.fY - 300, nullptr);
	LineTo(_hDC, m_tInfo.fX + 50+ iScrollX, m_tInfo.fY - 300);

	//MoveToEx(_hDC, m_tInfo.fX + 50 + iScrollX, m_tInfo.fY - 300 , nullptr);
	//LineTo(_hDC, m_tInfo.fX + iScrollX, m_tInfo.fY - 300 + 30);
	for (int i = 0; i < 10; ++i)
	{
		MoveToEx(_hDC, LONG(m_tInfo.fX + 50 + iScrollX), LONG(m_tInfo.fY - 300 + i*60), nullptr);
		LineTo(_hDC, LONG(m_tInfo.fX + iScrollX), LONG(m_tInfo.fY - 300 + 30 + i*60));

		MoveToEx(_hDC, m_tInfo.fX + iScrollX, m_tInfo.fY - 300 + 30 + i * 60, nullptr);
		LineTo(_hDC, m_tInfo.fX + 50 + iScrollX, m_tInfo.fY - 300 + 60 + i * 60);
	}

	MoveToEx(_hDC, LONG(m_tInfo.fX - 50+ iScrollX), LONG(m_tInfo.fY + 300), nullptr);
	LineTo(_hDC, LONG(m_tInfo.fX + 50+ iScrollX), LONG(m_tInfo.fY + 300));


}

void CThorn::Release(void)
{
}
