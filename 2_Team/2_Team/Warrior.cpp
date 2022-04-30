#include "stdafx.h"
#include "Warrior.h"


CWarrior::CWarrior()
{
}


CWarrior::~CWarrior()
{
	Release();
}

void CWarrior::Initialize(void)
{
	m_tInfo.fX = 300.f;
	m_tInfo.fY = 500.f;

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_iHp = 3;

	m_iAtt = 1;

	m_fSpeed = 2.f;

	m_fAngle = 0.f;

	DIAGONAL((float)m_tRect.right, (float)m_tRect.top, (float)m_tRect.right + 20, (float)m_tRect.top + 20);

	m_fDiagonal = 50.f;
}

const int& CWarrior::Update(void)
{
	if (!m_iHp)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CWarrior::Late_Update(void)
{
	if ( 200 >= m_tRect.left || WINCX -200  <= m_tRect.right)
	{
		
		m_fSpeed *= -1.f;
	}

	m_tSword.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
	m_tSword.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));


}

void CWarrior::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top - 20, m_tRect.right, m_tRect.bottom - 20);
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(_hDC, (LONG)m_tInfo.fX + 20, (LONG)m_tInfo.fY - 10, nullptr);
	LineTo(_hDC, (LONG)m_tSword.x, (LONG)m_tSword.y);

	
	//m_fAngle -= 2.f;


}

void CWarrior::Release(void)
{
}
