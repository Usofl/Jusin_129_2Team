#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame() 
	: m_dwFPSTime(GetTickCount())
	, m_iFPS(0)
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

	if (m_dwFPSTime + 1000 < GetTickCount())   // GetTickCount() 1000ºÐÀÇ 1ÃÊ
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwFPSTime = GetTickCount();
	}
}

void CMainGame::Release(void)
{
}

void CMainGame::Key_Input(void)
{
}
