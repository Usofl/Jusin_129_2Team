#include "stdafx.h"
#include "MainGame.h"
#include "ObjMgr.h"


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

	CObj* player = new CPlayer;
	OBJMGR->Add_Being(BEING_PLAYER, player);

	OBJMGR->Initialize();
	m_pUi->Initialize();
}

void CMainGame::Update(void)
{
	OBJMGR->Update();
}
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
	OBJMGR->Late_Update();
}

	if (m_pUi->Get_State() == STATE_GAME)
	{
	}
	else
		m_pUi->Late_Update();
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	OBJMGR->Render(m_hDC);

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
