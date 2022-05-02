#include "stdafx.h"
#include "Koopa.h"
#include "MonsterFactory.h"


CKoopa::CKoopa()
	: m_dwCount(GetTickCount())
	, m_dwJumpTiming(GetTickCount())
	, m_bJump(false)
{
}


CKoopa::~CKoopa()
{
}

void CKoopa::Initialize(void)
{
	m_tInfo.fX = 5500.f;
	m_tInfo.fY = 250.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 250.f;

	m_iHp = 300;

	m_iAtt = 3;

	m_fSpeed = 2.f;

	m_fJumpPower = 13.f;
	m_fJumpTime = 0.f;
}

const int& CKoopa::Update(void)
{
	if (0 >= m_iHp)
	{
		return OBJ_DEAD;
	}

	if (m_dwJumpTiming + 7000 < GetTickCount())
	{
		m_bJump = true;
		m_bAir = true;

		m_dwJumpTiming = GetTickCount();
	}

	Jumping();

	Shoot_Bullet();

	//m_tInfo.fX += m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;

}

void CKoopa::Late_Update(void)
{
	if (450 >= m_tRect.left || WINCX - 50 <= m_tRect.right)
	{
		m_fSpeed *= -1.f;
	}

}

void CKoopa::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top - 40 + iScrollY, m_tRect.right + iScrollX, m_tRect.top - 30 + iScrollY);

	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	OldBrush = (HBRUSH)SelectObject(_hDC, MyBrush);

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top - 40 + iScrollY, m_tRect.right - (int)(m_tInfo.fCX * (300.f - m_iHp) / 100.f) + iScrollX, m_tRect.top - 30 + iScrollY);

	SelectObject(_hDC, OldBrush);
	DeleteObject(MyBrush);

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top - 20, m_tRect.right + iScrollX, m_tRect.bottom - 20);
	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CKoopa::Release(void)
{
}

void CKoopa::Jumping(void)
{
	float	fLineY = WINCY;

	float fPlayer_X = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fX;

	m_tInfo.fY += (m_tInfo.fCY * 0.5f);
	bool bLineCol = CCollision::Collision_Line(*this, OBJMGR->Get_NotBeing_list(NOTBEING_LINE), fLineY);
	m_tInfo.fY -= (m_tInfo.fCY * 0.5f);
	fLineY -= (m_tInfo.fCY * 0.5f);


	if (fLineY > m_tInfo.fY)
	{
		m_bAir = true;
	}
	if (m_bJump)
	{
		m_iAtt = 50;
		if (m_tInfo.fX > fPlayer_X)
		{
			m_fJumpTime += 0.1f;
			float fy = m_fJumpPower * m_fJumpTime - (0.5f * (GRAVITY - 4.f) * (m_fJumpTime * m_fJumpTime));
			
			m_tInfo.fY -= fy;
			m_tInfo.fX -= 3.f;
		}
		else if (m_tInfo.fX < fPlayer_X)
		{
			m_fJumpTime += 0.1f;
			float fy = m_fJumpPower * m_fJumpTime - (0.5f * (GRAVITY - 4.f) * (m_fJumpTime * m_fJumpTime));

			m_tInfo.fY -= fy;
			m_tInfo.fX += 3.f;
		}
		if (bLineCol && m_tInfo.fY - 10.f > fLineY)
		{
			m_fJumpTime = 0.f;
			m_bJump = false;
			m_bAir = false;

			m_tInfo.fY = fLineY;
		}
	}
	/*else if (m_bAir)
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
	}*/
}

void CKoopa::Shoot_Bullet(void)
{
	
	if (m_dwCount + 100 < GetTickCount())	// dwCount+3000(대략 3초) < GetTickCount 커질때 (GetTickCount 1 /1000 = 1초)
	{
		// CObjMgr*타입의 instance 를 반환 후에 Add_Being함수 호출(몬스터 총알, 총알생성(정보값)
		
			OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Bullet_Koopa(m_tInfo.fX, m_tInfo.fY));
		
		m_dwCount = GetTickCount(); // 다시 대입해서 1초로 초기화
	}
}


