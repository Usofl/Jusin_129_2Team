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
		= { { 200,350,20,20 },
		{ 210,350,20,20 },
		{ 220,350,20,20 },
		{ 230,350,20,20 },
		{ 240,350,20,20 },
		{ 250,350,20,20 },
		{ 260,350,20,20 },
		{ 270,350,20,20 },
		{ 280,350,20,20 },
		{ 290,350,20,20 },
		{ 300,350,20,20 },
		{ 310,350,20,20 },
		{ 320,350,20,20 },
		{ 330,350,20,20 },
		{ 340,350,20,20 },
		{ 350,350,20,20 },
		{ 360,350,20,20 },
		{ 370,350,20,20 },
		{ 380,350,20,20 },
		{ 390,350,20,20 }
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
	for (auto& iter = m_CoinList.begin(); iter != m_CoinList.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CCoin*>(*iter);
			iter = m_CoinList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CCoinMgr::Late_Update(void)
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
}

