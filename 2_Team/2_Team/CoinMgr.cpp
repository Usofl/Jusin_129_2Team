#include "stdafx.h"
#include "CoinMgr.h"
CCoinMgr*		CCoinMgr::m_pInstance = nullptr;

CCoinMgr::CCoinMgr()
{
}


CCoinMgr::~CCoinMgr()
{
	Release();
}

void CCoinMgr::Initialize(void)
{
	INFO tCoinInfo[20]
		= { { 200,150,20,20 },
		{ 210,150,20,20 },
		{ 220,150,20,20 },
		{ 230,150,20,20 },
		{ 240,150,20,20 },
		{ 250,150,20,20 },
		{ 260,150,20,20 },
		{ 270,150,20,20 },
		{ 280,150,20,20 },
		{ 290,150,20,20 },
		{ 300,150,20,20 },
		{ 310,150,20,20 },
		{ 320,150,20,20 },
		{ 330,150,20,20 },
		{ 340,150,20,20 },
		{ 350,150,20,20 },
		{ 360,150,20,20 },
		{ 370,150,20,20 },
		{ 380,150,20,20 },
		{ 390,150,20,20 }
	};

	for (int i = 0; i < 20; ++i)
	{
		m_CoinList.push_back(new CCoin(tCoinInfo[i].fX, tCoinInfo[i].fY));
	}
	
	for (auto& iter : m_CoinList)
	{
		iter->Initialize();
	}
}

void CCoinMgr::Update(void)
{
	for (auto& iter : m_CoinList)
	{
		iter->Update();
	}
}

void CCoinMgr::LateUpdate(void)
{
	for (auto& iter : m_CoinList)
	{
		iter->Late_Update();
	}
}

void CCoinMgr::Render(HDC hDC)
{
	for (auto& iter : m_CoinList)
		iter->Render(hDC);
}

void CCoinMgr::Release(void)
{
	m_CoinList.clear();
}
