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
	m_tInfo.fX = 2200.f;
	m_tInfo.fY = 100.f;

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_iHp = 10;

	m_iAtt = 1;

	m_fSpeed = 2.f;

	m_fAngle = 330.f;
	
	m_fDiagonal = 50.f;

	m_iReverse = false;
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

	m_tInfo.fY = fLineY;

	// 몬스터 움직이는 스피드값
	m_tInfo.fX += m_fSpeed;
	
	// 칼 x 좌표 * -1 곱해서 반대로
	m_tSword.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle * PI) / 180.f) * m_iTurn));
	m_tSword.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

	float	fWidth = long(m_tSword.x - m_tInfo.fX);
	float	fHeight = long(m_tSword.y - m_tInfo.fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadian = acosf(fWidth / fDiagonal);

	//m_fAngle = (fRadian * 180.f) / PI;
	
	/*m_fAngle += 1.f;
	if (m_iReverse)
	{
		m_fAngle += 1.f;
	}
	else if (!m_iReverse)
	{
		m_fAngle -= 1.f;
	}

	if (110.f == m_fAngle || 270.f == m_fAngle)
	{
		m_iReverse = !m_iReverse;
	}*/



	Update_Rect();
	return OBJ_NOEVENT;
}

void CWarrior::Late_Update(void)
{
	float fPlayer_X = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fX;

	if (1600.f < fPlayer_X && 2440.f > fPlayer_X)
	{
		if (m_tInfo.fX > fPlayer_X)
		{
			if (0 < m_fSpeed)
			{
				m_iTurn *= -1.f;
				m_fSpeed *= -1.f;
			}
		}
		else if (m_tInfo.fX < fPlayer_X)
		{
			if (0 > m_fSpeed)
			{
				m_iTurn *= -1.f;
				m_fSpeed *= -1.f;
			}
		}
	}
	// 일정 수치 벽에 박으면
	if ( 1600.f >= m_tInfo.fX || 2450.f <= m_tInfo.fX)
	{
		// 스왑
		long lTemp = m_tRect.left;
		m_tRect.left = m_tRect.right;
		m_tRect.right = lTemp;

		// 반전을 위한 변수
		m_iTurn *= -1;
		m_fSpeed *= -1.f;

	}

}

void CWarrior::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top - 40 + iScrollY, m_tRect.right + iScrollX, m_tRect.top - 30 + iScrollY);

	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	OldBrush = (HBRUSH)SelectObject(_hDC, MyBrush);

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top - 40 + iScrollY, m_tRect.left + (int)((m_tInfo.fCX * m_iHp / 10.f)) + iScrollX, m_tRect.top - 30 + iScrollY);

	SelectObject(_hDC, OldBrush);
	DeleteObject(MyBrush);


	Rectangle(_hDC, m_tRect.left - (20 * m_iTurn) + iScrollX, m_tRect.top + iScrollY, m_tRect.right - (20 * m_iTurn) + iScrollX, m_tRect.bottom + iScrollY);
	Ellipse(_hDC, m_tRect.left + iScrollX, m_tRect.top - 20 + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom - 20 + iScrollY);
	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	MoveToEx(_hDC, (LONG)m_tInfo.fX + (20 * m_iTurn) + iScrollX, (LONG)m_tInfo.fY - 10 + iScrollY, nullptr);	// 중심 x 반전 * -1
	LineTo(_hDC, (LONG)m_tSword.x + iScrollX, (LONG)m_tSword.y + iScrollY);

}

void CWarrior::Release(void)
{
}
