#include "stdafx.h"
#include "LineMgr.h"

CLineMgr* CLineMgr::pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
}

void CLineMgr::Update(void)
{
	for (auto& iter = m_Line_List.begin(); iter != m_Line_List.end();)
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete<CObj*>(*iter);
			iter = m_Line_List.erase(iter);
		}
		else
		{
			++iter;
		}
	}
		
	
}

void CLineMgr::Late_Update(void)
{
	for (auto& iter : m_Line_List)
	{
		iter->Late_Update();
	}
}

void CLineMgr::Render(HDC _hDC)
{
	for (auto& iter : m_Line_List)
	{
		iter->Render(_hDC);
	}
}

void CLineMgr::Release(void)
{
	for (auto& iter : m_Line_List)
	{
		Safe_Delete<CObj*>(iter);
	}
}
