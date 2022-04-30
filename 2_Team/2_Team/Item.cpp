#include "stdafx.h"
#include "Item.h"
#include "CoinMgr.h"


CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Initialize(void)
{
	CCoinMgr::Get_Instance()->Initialize();
}

const int & CItem::Update(void)
{
	if (m_iHp <= 0)
		OBJ_DEAD;
	CCoinMgr::Get_Instance()->Update();
	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
	CCoinMgr::Get_Instance()->Late_Update();
}

void CItem::Render(HDC _hDC)
{
	CCoinMgr::Get_Instance()->Render(_hDC);
}

void CItem::Release(void)
{
	CCoinMgr::Get_Instance()->Release();
}
