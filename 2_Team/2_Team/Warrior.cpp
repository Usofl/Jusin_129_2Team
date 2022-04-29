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

	m_fDiagonal = 100.f;
}

int CWarrior::Update(void)
{
	if (m_iHp <= 0)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += m_fSpeed;

	Update_Rect();
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
	MoveToEx(_hDC, (float)m_tInfo.fX + 20.f, (float)m_tInfo.fY - 10.f, nullptr);
	LineTo(_hDC, (int)m_tSword.x, (int)m_tSword.y);

	
	m_fAngle -= 2.f;
	if (!m_bTurn)
	{
		m_fAngle -= 5.f;
		if (m_fAngle <= 120.f)
		{
			m_bTurn = true;
		}
		else
		{
			m_fAngle += 5.f;
			if (m_fAngle >= 240.f)
			{
				m_bTurn = false;
			}
		}
	}

}

void CWarrior::Release(void)
{
}
