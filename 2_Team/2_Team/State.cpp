#include "stdafx.h"
#include "State.h"

CState::CState()
{
}


CState::~CState()
{
}

void CState::Initialize()
{
	m_tMouseInfo.fCX = 20;
	m_tMouseInfo.fCY = 20;
	m_fMouseAngle = 1.f;

	m_tStartRect = { 200, 430, 350, 500 };
	m_tExitRect = { 450, 430, 600, 500 };
}

void CState::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (IntersectRect(&m_tColli, &m_tStartRect, &m_tMouseRect))
		{
			m_iState = STATE_GAME;
		}
		else if (IntersectRect(&m_tColli, &m_tExitRect, &m_tMouseRect))
		{
			DestroyWindow(g_hWnd);
			//m_iState = STATE_OVER;
		}
	}

	GetCursorPos(&m_tMouse);
	ScreenToClient(g_hWnd, &m_tMouse);

	m_fMouseAngle += 4.f;

}

void CState::Late_Update()
{
	m_tMouseRect.left = m_tMouse.x - (LONG)(m_tMouseInfo.fCX * sinf(RADIAN(m_fMouseAngle)));
	m_tMouseRect.right = m_tMouse.x + (LONG)(m_tMouseInfo.fCX * sinf(RADIAN(m_fMouseAngle)));
	m_tMouseRect.top = m_tMouse.y - (LONG)(m_tMouseInfo.fCY);
	m_tMouseRect.bottom = m_tMouse.y + (LONG)(m_tMouseInfo.fCY);
}

void CState::Render(HDC hDC)
{
	if (m_iState == STATE_PAUSE)
	{
		TextOut(hDC, WINCX / 2 - 50, WINCY / 2 - 40, TEXT("PAUSE"), 5);
		TextOut(hDC, WINCX / 2 - 100, WINCY / 2, TEXT("PRESS 'R' TO RESTART"), 20);
	}
	else if (m_iState == STATE_OVER)
	{
		RECT m_tLifeRect;
		m_tLifeRect.left = 345;
		m_tLifeRect.right = 360;
		m_tLifeRect.top = 235;
		m_tLifeRect.bottom = 250;
		Ellipse(hDC, m_tLifeRect.left, m_tLifeRect.top, m_tLifeRect.right, m_tLifeRect.bottom);

		MoveToEx(hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5f), m_tLifeRect.bottom, nullptr);
		LineTo(hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5f), m_tLifeRect.bottom + 10);

		LineTo(hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5f - 7), m_tLifeRect.bottom + 20);

		MoveToEx(hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5f), m_tLifeRect.bottom + 10, nullptr);
		LineTo(hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5f + 7), m_tLifeRect.bottom + 20);

		MoveToEx(hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5f), m_tLifeRect.bottom + 2, nullptr);
		LineTo(hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5f - 7), m_tLifeRect.bottom + 10);

		MoveToEx(hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5f), m_tLifeRect.bottom + 2, nullptr);
		LineTo(hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5f + 7), m_tLifeRect.bottom + 10);

		TCHAR	Temp[64];
		TextOut(hDC, WINCX / 2 - 100, WINCY / 2, TEXT("PRESS 'R' TO RESTART"), 20);
		wsprintf(Temp, L"%d", m_iLife);
		TextOut(hDC, WINCX / 2 - 20, WINCY / 2 - 50, TEXT("X"), 1);
		TextOut(hDC, WINCX / 2, WINCY / 2 - 50, Temp, lstrlen(Temp));
	}
	else if (m_iState == STATE_END)
	{
		TextOut(hDC, WINCX / 2 - 50 , WINCY / 2, TEXT("���� ����"), 5);
	}

	else
	{
		Rectangle(hDC, m_tStartRect.left, m_tStartRect.top, m_tStartRect.right, m_tStartRect.bottom);
		TextOut(hDC, (LONG)((m_tStartRect.left + m_tStartRect.right) * 0.5f) - 20, (LONG)((m_tStartRect.top + m_tStartRect.bottom) * 0.5f - 10), TEXT("Start!"), 6);
		Rectangle(hDC, m_tExitRect.left, m_tExitRect.top, m_tExitRect.right, m_tExitRect.bottom);
		TextOut(hDC, (LONG)((m_tExitRect.left + m_tExitRect.right) * 0.5f) - 20, (LONG)((m_tExitRect.top + m_tExitRect.bottom) * 0.5f - 10), TEXT("Exit"), 4);

		Rectangle(hDC, m_tMouseRect.left, m_tMouseRect.top, m_tMouseRect.right, m_tMouseRect.bottom);
	}
}

void CState::Release()
{
}
