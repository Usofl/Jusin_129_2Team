#include "stdafx.h"
#include "Koopa_Bullet.h"


CKoopa_Bullet::CKoopa_Bullet()
	: m_bReverse(false)
{
}


CKoopa_Bullet::~CKoopa_Bullet()
{
}

void CKoopa_Bullet::Initialize(void)
{
	m_iHp = 1;
	m_iAtt = 5;
	m_fSpeed = 10.f;
	m_fAngle = 20.f;

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fShootPower = 6.f;
	m_fShootTime = 0.f;


}

const int & CKoopa_Bullet::Update(void)
{
	if (!m_iHp)
		return OBJ_DEAD;
	

	if (!m_bReverse)
	{
		float fPlayer_X = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fX;
		float fPlayer_Y = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fY;

		float	fWidth = (fabs(fPlayer_X - m_tInfo.fX));
		float	fHeight = (fabs(fPlayer_Y - m_tInfo.fY));

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		float	fRadian = acosf(fWidth / fDiagonal);

		if (fPlayer_Y > m_tInfo.fY)
		{
			fRadian *= -1.f;
		}

		m_fAngle = fRadian;
		m_bReverse = true;
	}

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle);


	//m_fAngle = (fRadian * 180.f) / PI;	

	Update_Rect();

	return OBJ_NOEVENT;
}

void CKoopa_Bullet::Late_Update(void)
{
	if (m_tInfo.fY + (m_tInfo.fCY * 1.5) >= WINCY)
	{
		Set_Hp(0);
	}
}

void CKoopa_Bullet::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	Ellipse(_hDC, m_tRect.left + iScrollX , m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CKoopa_Bullet::Release(void)
{
}
