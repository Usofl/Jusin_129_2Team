#include "stdafx.h"
#include "Key.h"
#include "ObjMgr.h"
#include "Collision.h"


CKey::CKey()
	:m_fShake(0.3f), m_iTime(GetTickCount()) , m_bCheck(false), m_bPlayercolli(false)
{
}


CKey::~CKey()
{
}

void CKey::Initialize(void)
{
	//m_tInfo.fX = 2250.f;
	//m_tInfo.fY = 30.f;
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_bAir = false;
	m_iHp = 1;


	m_fJumpPower = 20.0f;
	m_fJumpTime = 0.f;

	m_iItemtype = ITEM_KEY;
}

const int & CKey::Update(void)
{
	m_tPlayerInfo.fX = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fX;
	m_tPlayerInfo.fY = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fY;
	float _Y = 0.f;

	if (m_iHp == 0 && m_bPlayercolli == false)
	{
		m_tInfo.fX = m_tPlayerInfo.fX - 100;
		m_tInfo.fY = m_tPlayerInfo.fY - 50;
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
		m_tInfo.fX += m_fJumpTime * 5;
		m_fJumpTime += 0.2f;
		bool bLineCol = CCollision::Collision_Line(*this, OBJMGR->Get_NotBeing_list(NOTBEING_LINE), _Y);
		if (bLineCol)
		{
			if (m_tInfo.fY + 40 >= _Y && m_tInfo.fY - 40 <= _Y)
			{
				m_iHp = 1;
				m_bPlayercolli = false;
				m_fJumpTime = 0;
			}
		}
	}	

	if (OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Hp() == 0) 
	{
		m_bPlayercolli = false;
		m_iHp = 1;
		m_tInfo.fX = 100.f;
		m_tInfo.fY = 300.f;
	}
	if (550 <= m_tInfo.fY)
	{
		m_bPlayercolli = false;
		m_iHp = 1;
		m_tInfo.fX = 100.f;
		m_tInfo.fY = 300.f;
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
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	Ellipse(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right - 20 + iScrollX, m_tRect.bottom - 20 + iScrollY);
	Ellipse(_hDC, m_tRect.left + 3 + iScrollX, m_tRect.top + 3 + iScrollY, m_tRect.right - 23 + iScrollX, m_tRect.bottom - 23 + iScrollY);
	Rectangle(_hDC, m_tRect.left + 28 + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right + 20 + iScrollX, m_tRect.bottom - 35 + iScrollY);
	Rectangle(_hDC, m_tRect.left + 65 + iScrollX, m_tRect.top + 15 + iScrollY, m_tRect.right + 20 + iScrollX, m_tRect.bottom - 20 + iScrollY);
	Rectangle(_hDC, m_tRect.left + 58 + iScrollX, m_tRect.top + 15 + iScrollY, m_tRect.right + 15 + iScrollX, m_tRect.bottom - 25 + iScrollY);
}

void CKey::Release(void)
{
}

void CKey::PlayerColiision(void)
{
	if (m_iHp == 0 && m_bPlayercolli == false)
	{
		m_bPlayercolli = true;
	}
}