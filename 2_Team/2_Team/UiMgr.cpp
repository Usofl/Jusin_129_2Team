#include "stdafx.h"
#include "UiMgr.h"
CUiMgr*		CUiMgr::m_pInstance = nullptr;

CUiMgr::CUiMgr()
{
}


CUiMgr::~CUiMgr()
{
}

void CUiMgr::Initialize(void)
{
	m_UiList.push_back(new CUI);
	for (auto& iter : m_UiList)
	{
		iter->Initialize();
	}
}

void CUiMgr::Update(void)
{
	for (auto& iter : m_UiList)
	{
		iter->Update();
	}
}

void CUiMgr::Late_Update(void)
{
	for (auto& iter : m_UiList)
	{
		iter->Late_Update();
	}
}

void CUiMgr::Render(HDC hDC)
{
	for (auto& iter : m_UiList)
	{
		iter->Render(hDC);
	}
}

void CUiMgr::Release(void)
{
}
