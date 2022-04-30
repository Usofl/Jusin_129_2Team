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
		= { { 200,450,20,20 },
		{ 210,450,20,20 },
		{ 220,450,20,20 },
		{ 230,450,20,20 },
		{ 240,450,20,20 },
		{ 250,450,20,20 },
		{ 260,450,20,20 },
		{ 270,450,20,20 },
		{ 280,450,20,20 },
		{ 290,450,20,20 },
		{ 300,450,20,20 },
		{ 310,450,20,20 },
		{ 320,450,20,20 },
		{ 330,450,20,20 },
		{ 340,450,20,20 },
		{ 350,450,20,20 },
		{ 360,450,20,20 },
		{ 370,450,20,20 },
		{ 380,450,20,20 },
		{ 390,450,20,20 }
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

