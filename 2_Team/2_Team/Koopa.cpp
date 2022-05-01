#include "stdafx.h"
#include "Koopa.h"



CKoopa::CKoopa()
	: m_dwCount(GetTickCount())
{
}


CKoopa::~CKoopa()
{
}

void CKoopa::Initialize(void)
{
	m_tInfo.fX = 600.f;
	m_tInfo.fY = 250.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 250.f;

	m_iHp = 10;

	m_iAtt = 3;

	m_fSpeed = 2.f;

	m_fJumpPower = 15.f;
	m_fJumpTime = 0.f;
}

const int& CKoopa::Update(void)
{
	if (!m_iHp)
	{
		return OBJ_DEAD;
	}

	float	fLineY = WINCY;

	m_tInfo.fY += (m_tInfo.fCY * 0.5f);
	bool bLineCol = CCollision::Collision_Line(*this, OBJMGR->Get_NotBeing_list(NOTBEING_LINE), fLineY);
	m_tInfo.fY -= (m_tInfo.fCY * 0.5f);
	fLineY -= (m_tInfo.fCY * 0.5f);


	if (fLineY - 20.f > m_tInfo.fY)
	{
		m_bAir = true;
	}

	if (m_bJump && m_bAir)
	{
		m_fJumpTime += 0.2f;
		float fy = m_fJumpPower * m_fJumpTime - (0.5f * (GRAVITY - 9.7) * (m_fJumpTime * m_fJumpTime));

		if (bLineCol && m_tInfo.fY - 10.f > fLineY)
		{
			m_fJumpTime = 0.f;
			m_bJump = false;
			m_bAir = false;

			m_tInfo.fY = fLineY;
		}
	}
	else if (m_bAir)
	{
		m_fJumpTime += 0.2f;
		m_tInfo.fY += (0.5f * (GRAVITY - 9.7) * (m_fJumpTime * m_fJumpTime));

		if (bLineCol || m_tInfo.fY - 10.f> fLineY)
		{
			m_fJumpTime = 0.f;
			m_bJump = false;
			m_bAir = false;

			m_tInfo.fY = fLineY;
		}
	}

	//m_tInfo.fX += m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;

}

void CKoopa::Late_Update(void)
{
	if (550 >= m_tRect.left || WINCX - 50 <= m_tRect.right)
	{
		m_fSpeed *= -1.f;
	}

}

void CKoopa::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top - 20, m_tRect.right, m_tRect.bottom - 20);
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}



void CKoopa::Release(void)
{
}


