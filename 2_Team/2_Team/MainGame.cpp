#include "stdafx.h"
#include "MainGame.h"

#include "Player.h"
#include "M_Cloud.h"
#include "Koopa.h"
#include "Warrior.h"
#include "Key.h"

#include "MonsterFactory.h" 
#include "GomuFactory.h"

#include "Collision.h"

#include "ObjMgr.h"
#include "ItemMgr.h"
#include "UiMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "CoinMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "GameMap.h"

CMainGame::CMainGame() 
	: m_dwFPSTime(GetTickCount())
	, m_iFPS(0)
	, m_Pause(false)
	, m_dwPauseTime(GetTickCount())
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
	COINMGR->Initialize();

	//CObjMgr::Get_Instance()->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(M_Cloud_TURTLE));
	//CObjMgr::Get_Instance()->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(WARRIOR_TURTLE));
	//CObjMgr::Get_Instance()->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(BOSS_KOOPA));

	CGameMap::Map_Maker(m_hDC);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
}


void CMainGame::Update(void)
{
	Key_Input();

	if (m_pState->Get_State() == STATE_GAME)
	{
		OBJMGR->Update();
		UIMGR->Update();
		COINMGR->Update();
	}
	else
	{
		m_pState->Update();
	}
	 
	CUiMgr::Get_Instance()->Get_Uilist().front()->Get_Life(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Being_list(BEING_PLAYER).front())->Get_Life());
	CUiMgr::Get_Instance()->Get_Uilist().front()->Get_Coin(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Being_list(BEING_PLAYER).front())->Get_Coin());
	m_pState->Get_Life(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Being_list(BEING_PLAYER).front())->Get_Life());
	m_pState->Get_Coin(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Being_list(BEING_PLAYER).front())->Get_Coin());
	UIMGR->Get_Uilist().front()->Get_Hp(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Being_list(BEING_PLAYER).front())->Get_Hp());
	UIMGR->Get_Uilist().front()->Get_Mp(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Being_list(BEING_PLAYER).front())->Get_Mp());
}

void CMainGame::Late_Update(void)
{
	if (m_pState->Get_State() == STATE_GAME)
	{
		OBJMGR->Late_Update();
		UIMGR->Late_Update();
		COINMGR->Late_Update();
	}
	else
	{ 
		m_pState->Late_Update();
	}
		
}

void CMainGame::Render(void)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	BitBlt(hMemDC, 0, 0, WINCX, WINCY, hGroundMemDC, 0, 0, SRCCOPY);

	//Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	if (m_pState->Get_State() == STATE_GAME)
	{
		COINMGR->Render(hMemDC);
		OBJMGR->Render(hMemDC);
		UIMGR->Render(hMemDC);
	}
	else
	{
		m_pState->Render(hMemDC);
	}

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
	Safe_Delete(m_pState);
	CCoinMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
}

void CMainGame::Key_Input(void)
{
	if (m_dwPauseTime + 200 < GetTickCount())
	{
		if (GetAsyncKeyState('R'))
		{
			if (m_pState->Get_State() == STATE_GAME)
				m_pState->Set_State(STATE_PAUSE);
			else if (m_pState->Get_State() == STATE_PAUSE)
				m_pState->Set_State(STATE_GAME);
			else if (m_pState->Get_State() == STATE_OVER)
				m_pState->Set_State(STATE_GAME);
		}
		else if (GetAsyncKeyState('G') && CCollision::Collision_Player_Room)
		{
			if(static_cast<CKey*>(OBJMGR->Get_NotBeing_list(ITEM_KEY).front())->GameOver())
				m_pState->Set_State(STATE_END);
		}
		m_dwPauseTime = GetTickCount();
	}
}