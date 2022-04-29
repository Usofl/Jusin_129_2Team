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
	m_hDC = GetDC(g_hWnd);

	CBeing* player = new CPlayer;
	OBJMGR->Add_Being(BEING_PLAYER, player);

	OBJMGR->Initialize();
}

void CMainGame::Update(void)
{
	OBJMGR->Update();
}

void CMainGame::Late_Update(void)
{
	OBJMGR->Late_Update();
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
