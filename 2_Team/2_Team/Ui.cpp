#include "stdafx.h"
#include "Ui.h"


CUi::CUi()
	:m_iState(STATE_START)
{
}


CUi::~CUi()
{
}

void CUi::Initialize()
{
	m_MouseInfo.fCX = 20;
	m_MouseInfo.fCY = 20;
	m_fMouseAngle = 1.f;

	m_StartRect = { 200, 450, 350, 520 };
	m_ExitRect = { 450, 450, 600, 520 };
}

void CUi::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (IntersectRect(&m_Colli, &m_StartRect, &m_MouseRect))
		{
			m_iState = STATE_GAME;
		}
		else if (IntersectRect(&m_Colli, &m_ExitRect, &m_MouseRect))
		{
			m_iState = STATE_END;
			DestroyWindow(g_hWnd);
		}
	}

		GetCursorPos(&m_Mouse);
		ScreenToClient(g_hWnd, &m_Mouse);

		m_fMouseAngle += 4.f;

		m_MouseRect.left = m_Mouse.x - m_MouseInfo.fCX * sinf((m_fMouseAngle * PI) / 180.f);
		m_MouseRect.right = m_Mouse.x + m_MouseInfo.fCX * sinf((m_fMouseAngle * PI) / 180.f);
		m_MouseRect.top = m_Mouse.y - m_MouseInfo.fCY;
		m_MouseRect.bottom = m_Mouse.y + m_MouseInfo.fCY;
}

void CUi::Late_Update()
{
}

void CUi::Render(HDC hDC)
{
	if (m_iState == STATE_PAUSE)
	{
		TextOut(hDC, WINCX / 2 - 50 , WINCY / 2 - 40, TEXT("PAUSE"), 5);
		TextOut(hDC, WINCX / 2 - 100, WINCY / 2, TEXT("PRESS 'R' TO RESTART"), 20);
	}
	else
	{
		Rectangle(hDC, m_StartRect.left, m_StartRect.top, m_StartRect.right, m_StartRect.bottom);
		TextOut(hDC, (m_StartRect.left + m_StartRect.right) * 0.5f - 20, (m_StartRect.top+ m_StartRect.bottom) * 0.5f, TEXT("Start!"), 6);
		Rectangle(hDC, m_ExitRect.left, m_ExitRect.top, m_ExitRect.right, m_ExitRect.bottom);
		TextOut(hDC, (m_ExitRect.left + m_ExitRect.right) * 0.5f - 20, (m_ExitRect.top + m_ExitRect.bottom) * 0.5f, TEXT("Exit"), 4);

		Rectangle(hDC, m_MouseRect.left, m_MouseRect.top, m_MouseRect.right, m_MouseRect.bottom);
	}
}