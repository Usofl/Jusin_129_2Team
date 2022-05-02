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
		wsprintf(Temp, L"%d", m_iLife - 1);
		TextOut(hDC, WINCX / 2 - 20, WINCY / 2 - 50, TEXT("X"), 1);
		TextOut(hDC, WINCX / 2, WINCY / 2 - 50, Temp, lstrlen(Temp));
	}
	else if (m_iState == STATE_END)
	{
		//g
		HBRUSH MyBrush, OldBrush;
		MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		RoundRect(hDC, 140, 130, 240, 140, 10, 10);
		Rectangle(hDC, 140, 240, 150, 130);
		RoundRect(hDC, 140, 230, 240, 240, 20, 10);
		RoundRect(hDC, 190, 180, 240, 190, 10, 10);
		Rectangle(hDC, 230, 180, 240, 230);
		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);

		//a
		MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		RoundRect(hDC, 290, 120, 370, 130, 5, 5);
		RoundRect(hDC, 290, 170, 370, 180, 5, 5);
		RoundRect(hDC, 285, 120, 300, 230, 20, 20);
		RoundRect(hDC, 360, 120, 375, 230, 20, 20);
		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);

		//m
		MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		RoundRect(hDC, 420, 110, 530, 120, 10, 10);
		RoundRect(hDC, 420, 110, 432, 220, 5, 5);
		RoundRect(hDC, 470, 110, 482, 220, 5, 5);
		RoundRect(hDC, 520, 110, 532, 220, 5, 5);
		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);

		//e
		MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		RoundRect(hDC, 570, 100, 670, 110, 10, 10);
		RoundRect(hDC, 570, 150, 670, 160, 10, 10);
		RoundRect(hDC, 570, 200, 670, 210, 10, 10);
		RoundRect(hDC, 570, 100, 582, 210, 20, 20);
		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);

		//o
		MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		RoundRect(hDC, 140, 300, 150, 410, 10, 10);
		RoundRect(hDC, 240, 300, 250, 410, 10, 10);
		RoundRect(hDC, 140, 300, 250, 310, 10, 10);
		RoundRect(hDC, 140, 400, 250, 410, 10, 10);
		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);

		//V
		MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		RoundRect(hDC, 300, 290, 310, 360, 10, 10);
		RoundRect(hDC, 350, 290, 360, 360, 10, 10);

		RoundRect(hDC, 310, 340, 320, 380, 10, 10);
		RoundRect(hDC, 340, 340, 350, 380, 10, 10);

		RoundRect(hDC, 320, 360, 330, 400, 10, 10);
		RoundRect(hDC, 330, 360, 340, 400, 10, 10);

		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);

		//E
		MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		RoundRect(hDC, 410, 270, 510, 280, 10, 10);
		RoundRect(hDC, 410, 320, 510, 330, 10, 10);
		RoundRect(hDC, 410, 370, 510, 380, 10, 10);
		RoundRect(hDC, 410, 270, 422, 380, 20, 20);
		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);

		//R
		MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		RoundRect(hDC, 550, 250, 640, 260, 10, 10);
		RoundRect(hDC, 550, 300, 640, 310, 10, 10);
		//RoundRect(hDC, 650, 500, 750, 510, 10, 10);
		RoundRect(hDC, 635, 260, 645, 300, 20, 20);
		RoundRect(hDC, 550, 250, 562, 360, 5, 5);
		RoundRect(hDC, 635, 310, 645, 360, 5, 5);
		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);

		MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		RoundRect(hDC, 700, 200, 720, 320, 20, 20);
		Ellipse(hDC, 700, 340, 730, 370);
		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);
		
	}

	else
	{
		MoveToEx(hDC, 100, 100, nullptr);
		LineTo(hDC, 120, 80);
		LineTo(hDC, 200, 80);
		LineTo(hDC, 180, 100);
		LineTo(hDC, 100, 100);
		LineTo(hDC, 100, 120);
		LineTo(hDC, 140, 120);
		LineTo(hDC, 100, 170);
		LineTo(hDC, 120, 180);		//왼쪽 아래
		LineTo(hDC, 150, 150);
		LineTo(hDC, 180, 180);
		LineTo(hDC, 200, 160);		// 오른쪽 아래
		LineTo(hDC, 170, 130);
		LineTo(hDC, 180, 100);
		MoveToEx(hDC, 120, 180, nullptr);
		LineTo(hDC, 140, 180);
		LineTo(hDC, 160, 160);
		MoveToEx(hDC, 200, 160, nullptr);
		LineTo(hDC, 210, 140);
		LineTo(hDC, 190, 120);
		LineTo(hDC, 170, 130);
		MoveToEx(hDC, 190, 120, nullptr);
		LineTo(hDC, 200, 80);
		//ㅠ

		MoveToEx(hDC, 80, 215, nullptr);
		LineTo(hDC, 220, 215);
		LineTo(hDC, 220, 245);
		LineTo(hDC, 195, 245);
		LineTo(hDC, 195, 275);
		LineTo(hDC, 170, 275);
		LineTo(hDC, 170, 245);
		LineTo(hDC, 140, 245);
		LineTo(hDC, 140, 275);
		LineTo(hDC, 115, 275);
		LineTo(hDC, 115, 245);
		LineTo(hDC, 80, 245);
		LineTo(hDC, 80, 215);
		LineTo(hDC, 100, 200);
		LineTo(hDC, 240, 200);
		LineTo(hDC, 220, 215);
		LineTo(hDC, 240, 200);
		LineTo(hDC, 240, 225);	//오른쪽 아래
		LineTo(hDC, 220, 245);
		MoveToEx(hDC, 195, 275, nullptr);
		LineTo(hDC, 210, 260);
		LineTo(hDC, 210, 245);
		MoveToEx(hDC, 140, 275, nullptr);
		LineTo(hDC, 155, 260);
		LineTo(hDC, 155, 245);

		//ㅅ
		MoveToEx(hDC, 330, 100, nullptr);
		LineTo(hDC, 300, 100);
		LineTo(hDC, 270, 170);
		LineTo(hDC, 295, 180);
		LineTo(hDC, 310, 140);
		LineTo(hDC, 325, 180);
		LineTo(hDC, 345, 170);
		LineTo(hDC, 330, 100);
		LineTo(hDC, 350, 85);
		LineTo(hDC, 320, 85);
		LineTo(hDC, 300, 100);		//오른쪽 끝
		MoveToEx(hDC, 295, 180, nullptr);
		LineTo(hDC, 318, 160);
		MoveToEx(hDC, 350, 85, nullptr);
		LineTo(hDC, 365, 150);
		LineTo(hDC, 345, 170);
		MoveToEx(hDC, 380, 60, nullptr);
		LineTo(hDC, 380, 200);
		LineTo(hDC, 410, 200);
		LineTo(hDC, 410, 60);
		LineTo(hDC, 380, 60);		//왼쪽 끝
		LineTo(hDC, 400, 45);
		LineTo(hDC, 430, 45);
		LineTo(hDC, 410, 60);
		LineTo(hDC, 430, 45);
		LineTo(hDC, 430, 185);
		LineTo(hDC, 410, 200);

		//ㄴ
		MoveToEx(hDC, 290, 220, nullptr);
		LineTo(hDC, 290, 280);
		LineTo(hDC, 420, 280);
		LineTo(hDC, 420, 250);
		LineTo(hDC, 420, 250);
		LineTo(hDC, 320, 250);
		LineTo(hDC, 320, 220);
		LineTo(hDC, 290, 220);		//왼쪽 끝
		LineTo(hDC, 305, 205);
		LineTo(hDC, 335, 205);
		LineTo(hDC, 320, 220);
		LineTo(hDC, 335, 205);
		LineTo(hDC, 335, 240);
		LineTo(hDC, 435, 240);
		LineTo(hDC, 435, 270);
		LineTo(hDC, 420, 280);
		MoveToEx(hDC, 320, 250, nullptr);
		LineTo(hDC, 335, 240);
		LineTo(hDC, 435, 240);
		LineTo(hDC, 420, 250);

		HBRUSH MyBrush, OldBrush;
		MyBrush = (HBRUSH)CreateSolidBrush(RGB(150, 75, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);

		Ellipse(hDC, 500, 100, 550, 150);
		Rectangle(hDC, 550, 130, 580, 120);
		Rectangle(hDC, 570, 80, 580, 160);
		Rectangle(hDC, 650, 80, 720, 90);
		Rectangle(hDC, 650, 120, 720, 110);
		Rectangle(hDC, 650, 80, 660, 120);
		Rectangle(hDC, 640, 150, 730, 140);
		Rectangle(hDC, 500, 210, 550, 220);
		Rectangle(hDC, 500, 230, 550, 240);

		Rectangle(hDC, 500, 180, 510, 240);
		Rectangle(hDC, 540, 180, 550, 240);
		Rectangle(hDC, 550, 220, 560, 230);
		Rectangle(hDC, 560, 180, 570, 250);
		Rectangle(hDC, 580, 180, 590, 250);
		Rectangle(hDC, 520, 270, 530, 300);
		Rectangle(hDC, 520, 290, 580, 300);
		Rectangle(hDC, 660, 190, 670, 200);
		Rectangle(hDC, 640, 200, 690, 210);
		Rectangle(hDC, 650, 210, 660, 250);
		Rectangle(hDC, 670, 210, 680, 250);
		Rectangle(hDC, 700, 215, 710, 225);
		Rectangle(hDC, 700, 235, 710, 245);
		Rectangle(hDC, 710, 200, 720, 270);
		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);


		MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 50, 0));
		OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		Ellipse(hDC, -50, -50, 50, 50);

		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);

		MoveToEx(hDC, 60, 20, nullptr);
		LineTo(hDC, 80, 28);
		MoveToEx(hDC, 50, 40, nullptr);
		LineTo(hDC, 70, 55);

		MoveToEx(hDC, 30, 60, nullptr);
		LineTo(hDC, 50, 80);
		MoveToEx(hDC, 15, 70, nullptr);
		LineTo(hDC, 18, 95);
		Rectangle(hDC, m_tStartRect.left, m_tStartRect.top, m_tStartRect.right, m_tStartRect.bottom);
		TextOut(hDC, (LONG)((m_tStartRect.left + m_tStartRect.right) * 0.5f) - 20, (LONG)((m_tStartRect.top + m_tStartRect.bottom) * 0.5f - 10), TEXT("Start!"), 6);
		Rectangle(hDC, m_tExitRect.left, m_tExitRect.top, m_tExitRect.right, m_tExitRect.bottom);
		TextOut(hDC, (LONG)((m_tExitRect.left + m_tExitRect.right) * 0.5f) - 20, (LONG)((m_tExitRect.top + m_tExitRect.bottom) * 0.5f - 10), TEXT("Exit"), 4);

	}
}

void CState::Release()
{
}
