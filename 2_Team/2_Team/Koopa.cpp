#include "stdafx.h"
#include "Koopa.h"
#include "MonsterFactory.h"


CKoopa::CKoopa()
	: m_dwCount(GetTickCount())
	, m_dwJumpTiming(GetTickCount())
	, m_bJump(false)
	, m_fKoopa_speed(5.f)
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

	m_bMove_X = false;

	m_fPlayer_X = 0;
}

const int& CKoopa::Update(void)
{
	if (0 >= m_iHp)
	{
		return OBJ_DEAD;
	}

	if (OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fX >= 5100 && OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fX <= 5700)
	{
		if (m_dwJumpTiming + 7000 < GetTickCount())
		{
			m_bJump = true;
			m_bAir = true;

			m_dwJumpTiming = GetTickCount();
		}

		Jumping();

		Shoot_Bullet();
	}	

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

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top - 40 + iScrollY, m_tRect.left + (int)(m_tInfo.fCX * m_iHp / 300.f) + iScrollX, m_tRect.top - 30 + iScrollY);

	SelectObject(_hDC, OldBrush);
	DeleteObject(MyBrush);

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top - 20 + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom - 20 + iScrollY);
	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CKoopa::Release(void)
{
}

void CKoopa::Jumping(void)
{
	float	fLineY = WINCY;

	if (!m_bMove_X)
	{
		m_fPlayer_X = PLAYER->Get_Info().fX;
		m_bMove_X = true;
	}
		

	m_tInfo.fY += (m_tInfo.fCY * 0.5f);
	bool bLineCol = CCollision::Collision_Line(*this, OBJMGR->Get_NotBeing_list(NOTBEING_LINE), fLineY);
	m_tInfo.fY -= (m_tInfo.fCY * 0.5f);
	fLineY += (m_tInfo.fCY * 0.4f);


	if (fLineY > m_tInfo.fY)
	{
		m_bJump = true;
	}

	//if (5200 >= m_fPlayer_X || 6000 <= m_fPlayer_X)
	{
		if (m_bJump)
		{
			m_iAtt = 10;


			m_fJumpTime += 0.1f;
			float fy = m_fJumpPower * m_fJumpTime - (0.5f * (GRAVITY - 4.f) * (m_fJumpTime * m_fJumpTime));

			m_tInfo.fY -= fy;
			

			if (m_tInfo.fX > m_fPlayer_X)
			{
				m_tInfo.fX -= m_fKoopa_speed;
			}
			else if (m_tInfo.fX < m_fPlayer_X)
			{
				m_tInfo.fX += m_fKoopa_speed;
			}


		/*	if (m_tInfo.fX > m_fPlayer_X)
			{
				m_fJumpTime += 0.1f;
				float fy = m_fJumpPower * m_fJumpTime - (0.5f * (GRAVITY - 4.f) * (m_fJumpTime * m_fJumpTime));

				m_tInfo.fY -= fy;
				m_tInfo.fX -= 3.f;
			}
			else if (m_tInfo.fX < m_fPlayer_X)
			{
				m_fJumpTime += 0.1f;
				float fy = m_fJumpPower * m_fJumpTime - (0.5f * (GRAVITY - 4.f) * (m_fJumpTime * m_fJumpTime));

				m_tInfo.fY -= fy;
				m_tInfo.fX += 3.f;
				
			}*/
			if (bLineCol && m_tInfo.fY - 10.f > fLineY)
			{
				Jump_Crash();
				m_fJumpTime = 0.f;
				m_bJump = false;
				m_bAir = false;
				m_bMove_X = false;
				m_tInfo.fY = fLineY;
				m_fPlayer_X = 0;
			}
		}
	}
}

void CKoopa::Shoot_Bullet(void)
{
	
	if (m_dwCount + 3000 < GetTickCount())	// dwCount+3000(�뷫 3��) < GetTickCount Ŀ���� (GetTickCount 1 /1000 = 1��)
	{
		// CObjMgr*Ÿ���� instance �� ��ȯ �Ŀ� Add_Being�Լ� ȣ��(���� �Ѿ�, �Ѿ˻���(������)
		
			OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Bullet_Koopa(m_tInfo.fX, m_tInfo.fY));
		
		m_dwCount = GetTickCount(); // �ٽ� �����ؼ� 1�ʷ� �ʱ�ȭ
	}
}

void CKoopa::Jump_Crash(void)
{
	OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Crash_Koopa(m_tInfo.fX, m_tInfo.fY + 0, RADIAN(110)));
	OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Crash_Koopa(m_tInfo.fX, m_tInfo.fY + 0, RADIAN(130)));
	OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Crash_Koopa(m_tInfo.fX, m_tInfo.fY + 0, RADIAN(150)));
	OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Crash_Koopa(m_tInfo.fX, m_tInfo.fY + 0, RADIAN(170)));
																									
	OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Crash_Koopa(m_tInfo.fX, m_tInfo.fY + 0, RADIAN(70)));
	OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Crash_Koopa(m_tInfo.fX, m_tInfo.fY + 0, RADIAN(50)));
	OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Crash_Koopa(m_tInfo.fX, m_tInfo.fY + 0, RADIAN(30)));
	OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Crash_Koopa(m_tInfo.fX, m_tInfo.fY + 0, RADIAN(10)));
}


