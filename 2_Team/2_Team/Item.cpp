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
	//int iRand = rand() % 4 + 4;

	m_tGun.left = 700;
	m_tGun.right = 725;
	m_tGun.top = 350;
	m_tGun.bottom = 355;

	m_tLife.left = 650;
	m_tLife.right = 675;
	m_tLife.top = 350;
	m_tLife.bottom = 355;
}

const int & CItem::Update(void)
{
	CCoinMgr::Get_Instance()->Update();
	if (m_iHp <= 0)
		return OBJ_DEAD;
	else
		return OBJ_NOEVENT;

}

void CItem::Late_Update(void)
{
	CCoinMgr::Get_Instance()->Late_Update();
}

void CItem::Render(HDC _hDC)
{
	CCoinMgr::Get_Instance()->Render(_hDC);
	
	// GUN
	Rectangle(_hDC, m_tGun.left - 2, m_tGun.top - 5, m_tGun.right + 2, m_tGun.bottom + 15);
	Rectangle(_hDC, m_tGun.left, m_tGun.top, m_tGun.right, m_tGun.bottom);
	Rectangle(_hDC, m_tGun.left + 20, m_tGun.top, m_tGun.right, m_tGun.bottom + 10);
	MoveToEx(_hDC, m_tGun.left + 13, m_tGun.bottom,nullptr);
	LineTo(_hDC, m_tGun.left + 20, m_tGun.bottom + 3);
	m_iItemtype = ITEM_GUN;
	m_tRect = m_tGun;

	// LIFE
	Rectangle(_hDC, m_tLife.left - 2, m_tLife.top - 5, m_tLife.right + 2, m_tLife.bottom + 15);
	m_iItemtype = ITEM_LIFE;
	m_tRect = m_tLife;
}

void CItem::Release(void)
{
	CCoinMgr::Get_Instance()->Release();
}
