#include "stdafx.h"
#include "Warrior.h"


CWarrior::CWarrior()
	: m_tSword({0,0})
	, m_iTurn(1)
	, m_fDiagonal(0.f)
	
{
}


CWarrior::~CWarrior()
{
	Release();
}

void CWarrior::Initialize(void)
{
	m_tInfo.fX = 300.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_iHp = 3;

	m_iAtt = 1;

	m_fSpeed = 2.f;

	m_fAngle = 0.f;
	
	m_fDiagonal = 50.f;
}

const int& CWarrior::Update(void)
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

		if (bLineCol || m_tInfo.fY - 10.f > fLineY)
		{
			m_fJumpTime = 0.f;
			m_bJump = true;
			m_bAir = true;

			m_tInfo.fY = fLineY;
		}
	}
	else if (m_bAir)
	{
		m_fJumpTime += 0.2f;
		m_tInfo.fY += (0.5f * (GRAVITY - 9.7) * (m_fJumpTime * m_fJumpTime));

		if (bLineCol && m_tInfo.fY - 10.f> fLineY)
		{
			m_fJumpTime = 0.f;
			m_bJump = true;
			m_bAir = true;

			m_tInfo.fY = fLineY;
		}
	}


	// 몬스터 움직이는 스피드값
	m_tInfo.fX += m_fSpeed;
	
	if(rc.left)
	m_fAngle += 1.f;
	
	// 칼 x 좌표 * -1 곱해서 반대로
	m_tSword.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle * PI) / 180.f) * m_iTurn));
	m_tSword.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

	Update_Rect();
	return OBJ_NOEVENT;
}

void CWarrior::Late_Update(void)
{
	// 일정 수치 벽에 박으면
	if ( 200 >= m_tRect.left || WINCX -200  <= m_tRect.right)
	{
		// 스왑
		long lTemp = m_tRect.left;
		m_tRect.left = m_tRect.right;
		m_tRect.right = lTemp;

		// 반전을 위한 변수
		m_iTurn *= -1;
		m_fSpeed *= -1.f;
	}

	if (m_fAngle >= 25.f)
	{
		m_fAngle *= -2.f;
	}

}

void CWarrior::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();

	Rectangle(_hDC, m_tRect.left - (20 * m_iTurn) + iScrollX, m_tRect.top, m_tRect.right - (20 * m_iTurn) + iScrollX, m_tRect.bottom);
	Ellipse(_hDC, m_tRect.left + iScrollX, m_tRect.top - 20, m_tRect.right + iScrollX, m_tRect.bottom - 20);
	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
	MoveToEx(_hDC, (LONG)m_tInfo.fX + (20 * m_iTurn) + iScrollX, (LONG)m_tInfo.fY - 10, nullptr);	// 중심 x 반전 * -1
	LineTo(_hDC, (LONG)m_tSword.x + iScrollX, (LONG)m_tSword.y);

}

void CWarrior::Release(void)
{
}
