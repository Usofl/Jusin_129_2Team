#include "stdafx.h"
#include "Player.h"
#include "Collision.h"
#include "ObjMgr.h"
#include "GomuFactory.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "CoinMgr.h"
#include "KeyMgr.h"

CPlayer::CPlayer()
	: m_bChange(false)
	, m_bJump(false)
	, m_bPool(false)
	, m_bLeft_Move(false)
	, m_bRight_Move(false)
	, m_bCharging(false)
	, m_dwGigant(GetTickCount())
	, m_fJumpTime(0.f)
	, m_fJumpAngle(90.f)
	, m_fCharging(0.f)
	, m_tLeft_Leg({ 0,0 })
	, m_tRight_Leg({ 0,0 })
	, m_iCoin(0)
	, m_iLife(3)
	, m_iMp(100)
	, m_iHp(100)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = WINCX * 0.5f;
	m_tInfo.fY = WINCY * 0.5f;

	m_tInfo.fCX = 75.f;
	m_tInfo.fCY = 75.f;
	
	m_iHp = 10;

	m_iReverse = 1;

	m_fAngle = asinf((m_tInfo.fCY * 0.5f) / LEGSIZE);

	m_tLeft_Leg = { (LONG)(m_tInfo.fX - LEGSIZE * cos(m_fAngle)) , (LONG)(m_tInfo.fY + LEGSIZE * sin(m_fAngle)) };
	m_tRight_Leg = { (LONG)(m_tInfo.fX + LEGSIZE * cos(m_fAngle)) , (LONG)(m_tInfo.fY + LEGSIZE * sin(m_fAngle)) };

	m_bAir = true;
	m_iCoin = 0;
	m_iReverse = 1;

	m_fJumpPower = 25.f;
	m_fSpeed = 2.f;
}

const int& CPlayer::Update(void)
{
	if (0 >= m_iHp)
	{
		return OBJ_DEAD;
	}

	Key_Input();

	Jumping();
	OffSet();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{

}

void CPlayer::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();

	//Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 212, 0));
	OldBrush = (HBRUSH)SelectObject(_hDC, MyBrush);
	Ellipse(_hDC, m_tRect.left + (int)(m_tInfo.fCX * 0.25f) + iScrollX, m_tRect.top - (int)(m_tInfo.fCY * 0.5f)
		, m_tRect.right - (int)(m_tInfo.fCX * 0.25f) + iScrollX, m_tRect.bottom - (int)((m_tInfo.fCY / 3.f) * 2.3f));
	
	Ellipse(_hDC, m_tRect.left + (int)(m_tInfo.fCX * 0.1f) + iScrollX, m_tRect.top - (int)(m_tInfo.fCY * 0.4f)
		, m_tRect.right - (int)(m_tInfo.fCX * 0.1f) + iScrollX, m_tRect.bottom - (int)((m_tInfo.fCY / 3.f) * 2.3f));
	SelectObject(_hDC, OldBrush);
	DeleteObject(MyBrush);

	Ellipse(_hDC, m_tRect.left + (int)(m_tInfo.fCX * 0.25f) + iScrollX, m_tRect.top - (int)(m_tInfo.fCY * 0.3f)
		, m_tRect.right - (int)(m_tInfo.fCX * 0.25f) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.8f));

	MoveToEx(_hDC, m_tRect.right - (int)(m_tInfo.fCX * 0.3f) - 1 + iScrollX, m_tRect.top + 1, nullptr);
	LineTo(_hDC, m_tRect.right - (int)(m_tInfo.fCX * 0.46f) - 1 + iScrollX, m_tRect.top + 1);

	MoveToEx(_hDC, (int)(m_tInfo.fX) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.8f), nullptr);
	LineTo(_hDC, (int)(m_tInfo.fX) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.7f));

	if (OBJMGR->Get_Being_list(BEING_GOMUFISTOL).empty())
	{
		// ����
		LineTo(_hDC, m_tRect.left + (int)(m_tInfo.fCX * 0.2f) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.4f));
		MoveToEx(_hDC, (int)(m_tInfo.fX) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.7f), nullptr);
		// ������
		LineTo(_hDC, m_tRect.right - (int)(m_tInfo.fCX * 0.2f) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.4f));
		MoveToEx(_hDC, (int)(m_tInfo.fX) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.7f), nullptr);
	}
	else
	{
		// ����
		LineTo(_hDC, (int)(m_tInfo.fX) - ((int)(m_tInfo.fCX * 0.2f) * m_iReverse) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.6f));
		LineTo(_hDC, (int)(m_tInfo.fX) + ((int)(m_tInfo.fCX * 0.05f) * m_iReverse) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.5f));
		MoveToEx(_hDC, (int)(m_tInfo.fX) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.7f), nullptr);
		LineTo(_hDC, (int)(m_tInfo.fX) - ((int)(m_tInfo.fCX * 0.1f) * m_iReverse) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.55f));
		LineTo(_hDC, (int)(m_tInfo.fX) + ((int)(m_tInfo.fCX * 0.05f) * m_iReverse) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.5f));
		MoveToEx(_hDC, (int)(m_tInfo.fX) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.7f), nullptr);
	}

	LineTo(_hDC, (int)(m_tInfo.fX) + iScrollX, (int)(m_tInfo.fY));

	LineTo(_hDC, m_tLeft_Leg.x + iScrollX, m_tLeft_Leg.y);
	MoveToEx(_hDC, (int)(m_tInfo.fX) + iScrollX, (int)(m_tInfo.fY), nullptr);
	LineTo(_hDC, m_tRight_Leg.x + iScrollX, m_tRight_Leg.y);

	if (m_bBalloon)
	{
		Ellipse(_hDC, m_tRect.left + iScrollX, m_tRect.top + (int)(m_tInfo.fCY * 0.1f)
			, m_tRect.right + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.1f));

		// ����
		MoveToEx(_hDC, (int)m_tRect.left + (int)(m_tInfo.fCX * 0.1f) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.7f), nullptr);
		LineTo(_hDC, m_tRect.left - (int)(m_tInfo.fCX * 0.2f) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.6f));
		MoveToEx(_hDC, (int)m_tRect.right - (int)(m_tInfo.fCX * 0.1f) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.7f), nullptr);
		// ������
		LineTo(_hDC, m_tRect.right + (int)(m_tInfo.fCX * 0.2f) + iScrollX, m_tRect.bottom - (int)(m_tInfo.fCY * 0.6f));
	}
}

void CPlayer::Release(void)
{
}

void CPlayer::Jumping(void)
{
	float		fLineY = WINCY;

	m_tInfo.fY += (m_tInfo.fCY * 0.5f);
	bool		bLineCol = CCollision::Collision_Line(*this, OBJMGR->Get_NotBeing_list(NOTBEING_LINE), fLineY);
	m_tInfo.fY -= (m_tInfo.fCY * 0.5f);
	fLineY -= (m_tInfo.fCY * 0.5f);

	if (fLineY - 20.f > m_tInfo.fY)
	{
		m_bAir = true;
	}

	if (m_bJump && m_bAir)
	{
		m_fJumpTime += 0.2f;

		float fy = m_fJumpPower * m_fJumpTime * sinf(RADIAN(m_fJumpAngle)) - (0.5f * GRAVITY * (m_fJumpTime * m_fJumpTime));
		float fx = (m_fSpeed * 2.f) * cosf(RADIAN(m_fJumpAngle));

		m_tInfo.fX += (fx * m_iReverse);
		m_tInfo.fY -= fy;

		if (bLineCol && m_tInfo.fY - 10.f > fLineY)
		{
			m_fJumpTime = 0.f;
			m_bJump = false;
			m_bAir = false;

			m_tInfo.fY = fLineY;
		}

		SetBody();

		return;
	}
	else if (m_bAir)
	{
		m_fJumpTime += 0.2f;
		m_tInfo.fY += (0.5f * GRAVITY * (m_fJumpTime * m_fJumpTime));

		if (bLineCol && m_tInfo.fY - 10.f > fLineY)
		{
			m_fJumpTime = 0.f;
			m_bJump = false;
			m_bAir = false;

			m_tInfo.fY = fLineY;
		}

		SetBody();
	}

	else if (bLineCol)
	{
		m_tInfo.fY = fLineY;
		m_tRight_Leg.y = (LONG)(fLineY + (m_tInfo.fCY * 0.5f));
		m_tLeft_Leg.y = (LONG)(fLineY + (m_tInfo.fCY * 0.5f));
	}
}

void CPlayer::SetBody(void)
{
	m_fAngle = asinf((m_tInfo.fCY * 0.5f) / LEGSIZE);

	m_tLeft_Leg = { (LONG)(m_tInfo.fX - LEGSIZE * cos(m_fAngle)) , (LONG)(m_tInfo.fY + LEGSIZE * sin(m_fAngle)) };
	m_tRight_Leg = { (LONG)(m_tInfo.fX + LEGSIZE * cos(m_fAngle)) , (LONG)(m_tInfo.fY + LEGSIZE * sin(m_fAngle)) };
}

void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iItv = 100;


	if (iOffSetX - iItv > m_tInfo.fX + iScrollX)
	{ 
		SCROLLMGR->Set_ScrollX(m_fSpeed);
	}

	if (iOffSetX + iItv < m_tInfo.fX + iScrollX)
	{
		SCROLLMGR->Set_ScrollX(-m_fSpeed);
	}
}

void CPlayer::PlayerCoinColli()
{
	++m_iCoin;
	if (m_iCoin == 30)
	{
		m_iCoin = 0;
		m_iLife++;
	}
}

void CPlayer::Put_ItemType(const int& _Itemtype)
{
	m_iItemtype = _Itemtype;

	switch (m_iItemtype)
	{
	case ITEM_GUN:
		break;
	case ITEM_LIFE:
		m_iLife++;
		break;
	case ITEM_KEY:
		break;
	case ITEM_BOX:
		break;
	default:
		break;
	}
}

void CPlayer::Key_Input(void)
{
	if (KEYMGR->Key_Pressing(VK_SHIFT) && !m_bRight_Move && !m_bLeft_Move)
	{
		m_fSpeed = 5.f;
		m_fJumpPower = 27.f;
		m_fJumpAngle = 30.f;
	}
	else
	{
		m_fSpeed = 2.f;
		m_fJumpPower = 15.f;
		m_fJumpAngle = 90.f;
	}

	if (KEYMGR->Key_Pressing('A'))
	{
		m_bPool = true;
	}
	else
	{
		m_bPool = false;
	}

	if (KEYMGR->Key_Pressing('S'))
	{
		m_bBalloon = true;
		m_fJumpPower = 10.f;
		m_fSpeed = 1.f;
	}
	else
	{
		m_bBalloon = false;
	}

	if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		if (KEYMGR->Key_Up(VK_SPACE))
		{
			if (!m_bAir)
			{
				m_bAir = true;
				m_tInfo.fY += 30.f;
			}
		}
	}
	else
	{
		if (KEYMGR->Key_Up(VK_SPACE))
		{
			m_bJump = true;
			m_bAir = true;
		}
	}

	if (KEYMGR->Key_Pressing('D'))
	{
		if (m_dwGigant + 4000 < GetTickCount())
		{
			m_fCharging += 0.1f;
			if (5.f <= m_fCharging)
			{
				m_bCharging = true;

				if (15.f <= m_fCharging)
				{
					POINT tPoint = { (LONG)(m_tInfo.fX + Random_Num(-20, 20)), (LONG)(m_tInfo.fY + Random_Num(-40, 10)) };
					OBJMGR->Add_Being(BEING_GOMUFISTOL, *CGomuFactory::Create_Gigant_Fistol(tPoint, m_iReverse, m_fCharging));

					m_fCharging = 0.f;
					m_dwGigant = GetTickCount();
					SetBody();
				}
			}
		}
	}
	else
	{
		if (5.f <= m_fCharging)
		{
			POINT tPoint = { (LONG)(m_tInfo.fX + Random_Num(-20, 20)), (LONG)(m_tInfo.fY + Random_Num(-40, 10)) };
			OBJMGR->Add_Being(BEING_GOMUFISTOL, *CGomuFactory::Create_Gigant_Fistol(tPoint, m_iReverse, m_fCharging));

			m_fCharging = 0.f;
			m_dwGigant = GetTickCount();
			SetBody();
		}
	}

	if (KEYMGR->Key_Up('D') && !m_bBalloon)
	{
		if (m_bCharging)
		{
			m_bCharging = false;
		}
		else
		{
			POINT tPoint = { (LONG)(m_tInfo.fX + Random_Num(-20, 20)), (LONG)(m_tInfo.fY + Random_Num(-40, 10)) };
			OBJMGR->Add_Being(BEING_GOMUFISTOL, *CGomuFactory::Create_Fistol(tPoint, m_iReverse));
			m_fCharging = 0.f;
		}

		SetBody();
	}

	if (OBJMGR->Get_Being_list(BEING_GOMUFISTOL).empty())
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			m_iReverse = 1;

			if (m_bRight_Move)
			{
				m_fJumpAngle = 90.f;
				return;
			}

			m_fJumpPower = 20.f;
			m_fJumpAngle = 45.f;

			if (m_bChange)
			{
				m_tLeft_Leg.x += (LONG)m_fSpeed;

				float fX((float)(m_tLeft_Leg.x - m_tRight_Leg.x) * 0.5f);
				m_fAngle = acosf(fX / LEGSIZE);

				if (m_tInfo.fCX * 0.5f - 10.f <= fabs(m_tLeft_Leg.x - m_tRight_Leg.x) && m_tLeft_Leg.x > m_tRight_Leg.x)
				{
					m_bChange = false;
				}

				m_tInfo.fX = m_tRight_Leg.x + LEGSIZE * cosf(m_fAngle);
				m_tInfo.fY = m_tRight_Leg.y - LEGSIZE * sinf(m_fAngle);
			}
			else
			{
				m_tRight_Leg.x += (LONG)m_fSpeed;

				float fX((float)(m_tRight_Leg.x - m_tLeft_Leg.x) * 0.5f);
				m_fAngle = acosf(fX / LEGSIZE);

				if ((m_tInfo.fCX * 0.5f) - 10.f <= fabs(m_tLeft_Leg.x - m_tRight_Leg.x) && m_tLeft_Leg.x < m_tRight_Leg.x)
				{
					m_bChange = true;
				}

				m_tInfo.fX = m_tLeft_Leg.x + LEGSIZE * cosf(m_fAngle);
				m_tInfo.fY = m_tLeft_Leg.y - LEGSIZE * sinf(m_fAngle);
			}
		}

		else if (GetAsyncKeyState(VK_LEFT))
		{
			m_iReverse = -1;

			if (m_bLeft_Move)
			{
				m_fJumpAngle = 90.f;
				return;
			}
				

			m_fJumpPower = 20.f;
			m_fJumpAngle = 45.f;


			if (m_bChange)
			{
				m_tLeft_Leg.x -= (LONG)m_fSpeed;

				float fX((float)(m_tLeft_Leg.x - m_tRight_Leg.x) * 0.5f);
				m_fAngle = acosf(fX / LEGSIZE);

				if ((m_tInfo.fCX * 0.5f) - 10.f <= fabs(m_tLeft_Leg.x - m_tRight_Leg.x) && m_tLeft_Leg.x < m_tRight_Leg.x)
				{
					m_bChange = false;
				}

				m_tInfo.fX = m_tRight_Leg.x + LEGSIZE * cosf(-m_fAngle);
				m_tInfo.fY = m_tRight_Leg.y - LEGSIZE * sinf(m_fAngle);
			}
			else
			{
				m_tRight_Leg.x -= (LONG)m_fSpeed;

				float fX((float)(m_tRight_Leg.x - m_tLeft_Leg.x) * 0.5f);
				m_fAngle = acosf(fX / LEGSIZE);

				if (m_tInfo.fCX * 0.5f - 10.f <= fabs(m_tLeft_Leg.x - m_tRight_Leg.x) && m_tLeft_Leg.x > m_tRight_Leg.x)
				{
					m_bChange = true;
				}

				m_tInfo.fX = m_tLeft_Leg.x + LEGSIZE * cosf(-m_fAngle);
				m_tInfo.fY = m_tLeft_Leg.y - LEGSIZE * sinf(m_fAngle);
			}
		}
	}
}
