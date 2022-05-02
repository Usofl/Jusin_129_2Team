#include "stdafx.h"
#include "Key.h"


CKey::CKey()
	:m_fShake(0.3f), m_iTime(GetTickCount()) , m_bCheck(false)
{
}


CKey::~CKey()
{
}

void CKey::Initialize(void)
{
	m_tInfo.fX = 2250.f;
	m_tInfo.fY = 30.f;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fJumpPower = 40.0f;
	m_fJumpTime = 0.f;

	m_iItemtype = ITEM_KEY;
}

const int & CKey::Update(void)
{
	m_tPlayerInfo.fX = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fX;
	m_tPlayerInfo.fY = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fY;

	if (m_iHp == 0)
	{
		m_tInfo.fX = m_tPlayerInfo.fX - 80;
		m_tInfo.fY = m_tPlayerInfo.fY + 30;
		m_tInfo.fY += m_fShake;

		if (m_bCheck == false)
		{
			m_fShake += 0.3f;
		}		
		else
		{
			m_fShake -= 0.3f;
		}
		if (m_fShake >= 12 || m_fShake <= -8)
		{
			m_bCheck = !m_bCheck;
		}
	}

	if (m_bPlayercolli == true && m_iHp == 0)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_tInfo.fX += m_fJumpPower * m_fJumpTime;
		m_fJumpTime += 0.2f;
	}

	return OBJ_NOEVENT;
}

void CKey::Late_Update(void)
{
	Update_Rect();
}
// y ÁßÁ¡ 350 top + 15
void CKey::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	Ellipse(_hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right - 20 + iScrollX, m_tRect.bottom - 20);
	Ellipse(_hDC, m_tRect.left + 3 + iScrollX, m_tRect.top + 3, m_tRect.right - 23 + iScrollX, m_tRect.bottom - 23);
	Rectangle(_hDC, m_tRect.left + 28 + iScrollX, m_tRect.top + 10, m_tRect.right + 20 + iScrollX, m_tRect.bottom - 35);
	Rectangle(_hDC, m_tRect.left + 65 + iScrollX, m_tRect.top + 15, m_tRect.right + 20 + iScrollX, m_tRect.bottom - 20);
	Rectangle(_hDC, m_tRect.left + 58 + iScrollX, m_tRect.top + 15, m_tRect.right + 15 + iScrollX, m_tRect.bottom - 25);
}

void CKey::Release(void)
{
}

void CKey::PlayerColiision(void)
{
	if (m_iHp == 0)
		m_bPlayercolli = true; 
}