#include "stdafx.h"
#include "CoinMgr.h"
#include "ObjMgr.h"
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
	INFO tCoinInfo[22]
		= { { 2500,28,20,20 },
		{ 2570,28,20,20 },
		{ 2640,28,20,20 },
		{ 2710,28,20,20 },
		{ 2780,28,20,20 },
		{ 2920,28,20,20 },

		{ 3140,160,20,20 },
		{ 3210,160,20,20 },
		{ 3280,160,20,20 },
		{ 3350,160,20,20 },

		{3700,320,20,20},
		{ 3800,320,20,20 },
		// GUN
		{ 1330,210,20,20 },
		{ 1390,210,20,20 },
		{ 1270,210,20,20 },

		{ 1600,240,20,20 },
		{ 1670,260,20,20 },
		{ 1740,280,20,20 },
		{ 1810,300,20,20 },
		{ 1880,320,20,20 },
		{ 1950,340,20,20 }
	};

	for (int i = 0; i < 22; ++i)
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

