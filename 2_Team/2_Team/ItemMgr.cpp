#include "stdafx.h"
#include "ItemMgr.h"
CItemMgr*	CItemMgr::m_pInstance = nullptr;

CItemMgr::CItemMgr()
{
}


CItemMgr::~CItemMgr()
{
}

void CItemMgr::Initialize(void)
{
	m_Itemlist.push_back(new CItem);
	for (auto& iter : m_Itemlist)
	{
		iter->Initialize();
	}
}

void CItemMgr::Update(void)
{
	for (auto& iter = m_Itemlist.begin(); iter != m_Itemlist.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CItem*>(*iter);
			iter = m_Itemlist.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CItemMgr::Late_Update(void)
{
	for (auto& iter : m_Itemlist)
	{
		iter->Late_Update();
	}
}

void CItemMgr::Render(HDC hDC)
{
	for (auto& iter : m_Itemlist)
	{
		iter->Render(hDC);
	}
}

void CItemMgr::Release(void)
{
	for (auto& iter : m_Itemlist)
	{
		iter->Release();
	}
}
