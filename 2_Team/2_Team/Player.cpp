#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
	: m_bChange(false)
	, m_bJump(false)
	, m_iReverse(1)
	, m_fJumpTime(0.f)
	, m_fJumpAngle(45.f)
	, m_tLeft_Leg({ 0,0 })
	, m_tRight_Leg({ 0,0 })
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(void)
{
	//theta = 0.f;

	m_tInfo.fX = WINCX * 0.5f;
	m_tInfo.fY = WINCY - 100.f;

	m_tInfo.fCX = 75.f;
	m_tInfo.fCY = 75.f;

	m_fAngle = asinf((m_tInfo.fCY * 0.5f) / LEGSIZE);

	m_tLeft_Leg = { (LONG)(m_tInfo.fX - LEGSIZE * cos(m_fAngle)) , (LONG)(m_tInfo.fY + LEGSIZE * sin(m_fAngle)) };
	m_tRight_Leg = { (LONG)(m_tInfo.fX + LEGSIZE * cos(m_fAngle)) , (LONG)(m_tInfo.fY + LEGSIZE * sin(m_fAngle)) };

	m_iReverse = 1;

	m_fJumpPower = 20.f;
	m_fSpeed = 2.f;
}

const int& CPlayer::Update(void)
{
	Key_Input();

	if (m_bJump)
	{
		m_fJumpTime += 0.2f;

		float fy = 10.f + m_fJumpPower * m_fJumpTime * sinf(RADIAN(m_fJumpAngle)) - (0.5f * GRAVITY * (m_fJumpTime * m_fJumpTime));
		float fx = m_fJumpPower * cosf(RADIAN(m_fJumpAngle));

		m_tInfo.fX += (fx * m_iReverse);
		m_tInfo.fY -= fy;

		m_fAngle = asinf((m_tInfo.fCY * 0.5f) / LEGSIZE);

		m_tLeft_Leg = { (LONG)(m_tInfo.fX - LEGSIZE * cos(m_fAngle)) , (LONG)(m_tInfo.fY + LEGSIZE * sin(m_fAngle)) };
		m_tRight_Leg = { (LONG)(m_tInfo.fX + LEGSIZE * cos(m_fAngle)) , (LONG)(m_tInfo.fY + LEGSIZE * sin(m_fAngle)) };
		Set_Body();
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	//if (m_tLeft_Leg.y > (WINCY - GAMESIZE))
	if(!m_bAir)
	{
		m_fJumpTime = 0.f;
		m_bJump = false;
	}
}

void CPlayer::Render(HDC _hDC)
{

	Ellipse(_hDC, m_tRect.left + (int)(m_tInfo.fCX * 0.25f), m_tRect.top - (int)(m_tInfo.fCY * 0.5f)
		, m_tRect.right - (int)(m_tInfo.fCX * 0.25f), m_tRect.bottom - (int)((m_tInfo.fCY / 3.f) * 2.3f));

	Ellipse(_hDC, m_tRect.left + (int)(m_tInfo.fCX * 0.1f), m_tRect.top - (int)(m_tInfo.fCY * 0.4f)
		, m_tRect.right - (int)(m_tInfo.fCX * 0.1f), m_tRect.bottom - (int)((m_tInfo.fCY / 3.f) * 2.3f));

	Ellipse(_hDC, m_tRect.left + (int)(m_tInfo.fCX * 0.25f), m_tRect.top - (int)(m_tInfo.fCY * 0.3f)
		, m_tRect.right - (int)(m_tInfo.fCX * 0.25f), m_tRect.bottom - (int)(m_tInfo.fCY * 0.8f));

	MoveToEx(_hDC, (int)(m_tInfo.fX), m_tRect.bottom - (int)(m_tInfo.fCY * 0.8f), nullptr);
	LineTo(_hDC, (int)(m_tInfo.fX), m_tRect.bottom - (int)(m_tInfo.fCY * 0.7f));
	// ¿ÞÆÈ
	LineTo(_hDC, m_tRect.left + (int)(m_tInfo.fCX * 0.2f), m_tRect.bottom - (int)(m_tInfo.fCY * 0.4f));
	MoveToEx(_hDC, (int)(m_tInfo.fX), m_tRect.bottom - (int)(m_tInfo.fCY * 0.7f), nullptr);
	// ¿À¸¥ÆÈ
	LineTo(_hDC, m_tRect.right - (int)(m_tInfo.fCX * 0.2f), m_tRect.bottom - (int)(m_tInfo.fCY * 0.4f));
	MoveToEx(_hDC, (int)(m_tInfo.fX), m_tRect.bottom - (int)(m_tInfo.fCY * 0.7f), nullptr);
	LineTo(_hDC, (int)(m_tInfo.fX), (int)(m_tInfo.fY));

	LineTo(_hDC, m_tLeft_Leg.x, m_tLeft_Leg.y);
	MoveToEx(_hDC, (int)(m_tInfo.fX), (int)(m_tInfo.fY), nullptr);
	LineTo(_hDC, m_tRight_Leg.x, m_tRight_Leg.y);
}

void CPlayer::Release(void)
{
}

void CPlayer::Set_Body(void)
{
	float fX = m_tLeft_Leg.x - m_tInfo.fX;
	m_fAngle = acosf(fX / LEGSIZE);

	m_tInfo.fX = m_tRight_Leg.x + LEGSIZE * cos(m_fAngle);
	m_tInfo.fY = m_tRight_Leg.y - LEGSIZE * sin(m_fAngle);
}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_iReverse = 1;
		if (m_bChange)
		{
			m_tLeft_Leg.x += (LONG)m_fSpeed;

			float fX = m_tLeft_Leg.x - m_tInfo.fX;
			m_fAngle = acosf(fX / LEGSIZE);

			if (m_tInfo.fCX * 0.5f - 10.f <= fabs(m_tLeft_Leg.x - m_tRight_Leg.x) && m_tLeft_Leg.x > m_tRight_Leg.x)
			{
				m_bChange = false;
			}

			m_tInfo.fX = m_tRight_Leg.x + LEGSIZE * cos(m_fAngle);
			m_tInfo.fY = m_tRight_Leg.y - LEGSIZE * sin(m_fAngle);
		}
		else
		{
			m_tRight_Leg.x += (LONG)m_fSpeed;

			float fX = m_tRight_Leg.x - m_tInfo.fX;
			m_fAngle = acosf(fX / LEGSIZE);

			if ((m_tInfo.fCX * 0.5f) - 10.f <= fabs(m_tLeft_Leg.x - m_tRight_Leg.x) && m_tLeft_Leg.x < m_tRight_Leg.x)
			{
				m_bChange = true;
			}
			
			m_tInfo.fX = m_tLeft_Leg.x + LEGSIZE * cos(m_fAngle);
			m_tInfo.fY = m_tLeft_Leg.y - LEGSIZE * sin(m_fAngle);
		}
	}

	else if (GetAsyncKeyState(VK_LEFT))
	{
		m_iReverse = -1;
		if (m_bChange)
		{
			m_tLeft_Leg.x -= (LONG)m_fSpeed;

			float fX = m_tLeft_Leg.x - m_tInfo.fX;
			m_fAngle = acosf(fX / LEGSIZE);

			if ((m_tInfo.fCX * 0.5f) - 10.f <= fabs(m_tLeft_Leg.x - m_tRight_Leg.x) && m_tLeft_Leg.x < m_tRight_Leg.x)
			{
				m_bChange = false;
			}

			m_tInfo.fX = m_tRight_Leg.x + LEGSIZE * cos(-m_fAngle);
			m_tInfo.fY = m_tRight_Leg.y - LEGSIZE * sin(m_fAngle);
		}
		else
		{
			m_tRight_Leg.x -= (LONG)m_fSpeed;

			float fX = m_tRight_Leg.x - m_tInfo.fX;
			m_fAngle = acosf(fX / LEGSIZE);

			if (m_tInfo.fCX * 0.5f - 10.f <= fabs(m_tLeft_Leg.x - m_tRight_Leg.x) && m_tLeft_Leg.x > m_tRight_Leg.x)
			{
				m_bChange = true;
			}

			m_tInfo.fX = m_tLeft_Leg.x + LEGSIZE * cos(-m_fAngle);
			m_tInfo.fY = m_tLeft_Leg.y - LEGSIZE * sin(m_fAngle);
		}

	}

	if (KEYMGR->Key_Up(VK_SPACE))
	{
		m_bJump = true;
	}
}
