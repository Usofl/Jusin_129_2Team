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
	CObjMgr::Get_Instance()->Add_Being(BEING_PLAYER, player);

	CObjMgr::Get_Instance()->Initialize();
}

void CMainGame::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
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
	CObjMgr::Get_Instance()->Render(m_hDC);
}

void CMainGame::Release(void)
{
}

void CMainGame::Key_Input(void)
{
}
