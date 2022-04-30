#include "stdafx.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "MonsterFactory.h" 
#include "ItemMgr.h"
#include "UiMgr.h"


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
	m_hDC = GetDC(g_hWnd);

	CObj* player = new CPlayer;
	OBJMGR->Add_Being(BEING_PLAYER, *player);

	OBJMGR->Initialize();
	m_pState->Initialize();
	UIMGR->Initialize();
	ITEMGR->Initialize();

	CObjMgr::Get_Instance()->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(CLOUD_TURTLE));
	CObjMgr::Get_Instance()->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(WARRIOR_TURTLE));
	CObjMgr::Get_Instance()->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(BOSS_KOOPA));
}


void CMainGame::Update(void)
{
	
	Key_Input();
	if (m_pState->Get_State() == STATE_GAME)
	{
		OBJMGR->Update();
		UIMGR->Update();
		ITEMGR->Update();
	}
	else
	{
		m_pState->Update();
	}
	
	CUiMgr::Get_Instance()->Get_Uilist().front()->Get_Life(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Being_list(BEING_PLAYER).front())->Set_Life());
	CUiMgr::Get_Instance()->Get_Uilist().front()->Get_Coin(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Being_list(BEING_PLAYER).front())->Set_Coin());

}

void CMainGame::Late_Update(void)
{
	if (m_pState->Get_State() == STATE_GAME)
	{
		OBJMGR->Late_Update();
		UIMGR->Late_Update();
		ITEMGR->Late_Update();
	}
	else
		m_pState->Late_Update();
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	++m_iFPS;

	if (m_dwFPSTime + 1000 < GetTickCount())   // GetTickCount() 1000���� 1��
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwFPSTime = GetTickCount();
	}
	if (m_pState->Get_State() == STATE_GAME)
	{
		OBJMGR->Render(m_hDC);
		CItemMgr::Get_Instance()->Render(m_hDC);
		UIMGR->Render(m_hDC);
	}
	else
		m_pState->Render(m_hDC);
}

void CMainGame::Release(void)
{
	Safe_Delete(m_pState);
	ITEMGR->Destroy_Instance();
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
