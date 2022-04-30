#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
	: m_dwFPSTime(GetTickCount())
	, m_iFPS(0), m_Pause(false), m_iTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
}


CMainGame::~CMainGame()
{
}

void CMainGame::Initialize(void)
{
	m_pUi = new CUi;
	m_hDC = GetDC(g_hWnd);
	m_pUi->Initialize();
}

void CMainGame::Update(void)
{
	Key_Input();
	if (m_pUi->Get_State() == STATE_GAME)
	{
	}
	else
	{
		m_pUi->Update();
	}
}

void CMainGame::Late_Update(void)
{

	if (m_pUi->Get_State() == STATE_GAME)
	{
	}
	else
		m_pUi->Late_Update();
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	++m_iFPS;

	if (m_dwFPSTime + 1000 < GetTickCount())   // GetTickCount() 1000분의 1초
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwFPSTime = GetTickCount();
	}


	if (m_pUi->Get_State() == STATE_GAME)
	{
		TextOut(m_hDC, WINCX / 2 - 100, WINCY / 2, TEXT("게임 진행중"), 6);
	}
	else
		m_pUi->Render(m_hDC);
}

void CMainGame::Release(void)
{
	Safe_Delete(m_pUi);
}

void CMainGame::Key_Input(void)
{
	if (m_iTime + 200 < GetTickCount())
	{
		if (GetAsyncKeyState('R'))
		{
			if (m_pUi->Get_State() == STATE_GAME)
				m_pUi->Set_Pause(STATE_PAUSE);
			else if (m_pUi->Get_State() == STATE_PAUSE)
				m_pUi->Set_Pause(STATE_GAME);
		}
		m_iTime = GetTickCount();
	}
}
