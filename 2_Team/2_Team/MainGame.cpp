#include "stdafx.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "MonsterFactory.h" 
#include "CoinMgr.h"


CMainGame::CMainGame() 
	: m_dwFPSTime(GetTickCount())
	, m_iFPS(0)
	, m_Pause(false)
	, m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
}


CMainGame::~CMainGame()
{
}

void CMainGame::Initialize(void)
{
	m_pState = new CState;
	m_pUI = new CUI;
	m_hDC = GetDC(g_hWnd);

	CObj* player = new CPlayer;
	CObj* Coin = new CCoin;
	OBJMGR->Add_Being(BEING_PLAYER, *player);
	OBJMGR->Add_Notbeing(NOTBEING_ITEM, *Coin);

	OBJMGR->Initialize();
	m_pState->Initialize();
	m_pUI->Initialize();
	CCoinMgr::Get_Instance()->Initialize();

	CObjMgr::Get_Instance()->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(CLOUD_TURTLE));
	CObjMgr::Get_Instance()->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(WARRIOR_TURTLE));
	CObjMgr::Get_Instance()->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(BOSS_KOOPA));



}


void CMainGame::Update(void)
{
	
	Key_Input();
	CCoinMgr::Get_Instance()->Update();
	if (m_pState->Get_State() == STATE_GAME)
	{
		OBJMGR->Update();
		m_pUI->Update();
	}
	else
	{
		m_pState->Update();
	}
}

void CMainGame::Late_Update(void)
{
	OBJMGR->Late_Update();
	CCoinMgr::Get_Instance()->LateUpdate();
	if (m_pState->Get_State() == STATE_GAME)
	{
		m_pUI->Late_Update();
	}
	else
		m_pState->Late_Update();
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
	if (m_pState->Get_State() == STATE_GAME)
	{
		OBJMGR->Render(m_hDC);
		m_pUI->Render(m_hDC);
		CCoinMgr::Get_Instance()->Render(m_hDC);
	}
	else
		m_pState->Render(m_hDC);
}

void CMainGame::Release(void)
{
	Safe_Delete(m_pState);
	CCoinMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
}

void CMainGame::Key_Input(void)
{
	if (m_dwTime + 200 < GetTickCount())
	{
		if (GetAsyncKeyState('R'))
		{
			if (m_pState->Get_State() == STATE_GAME)
				m_pState->Set_Pause(STATE_PAUSE);
			else if (m_pState->Get_State() == STATE_PAUSE)
				m_pState->Set_Pause(STATE_GAME);
		}
		m_dwTime = GetTickCount();
	}
}
