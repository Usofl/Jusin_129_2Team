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
	CCoinMgr::Get_Instance()->Update();
	return 0;
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
