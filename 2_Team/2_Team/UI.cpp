#include "stdafx.h"
#include "UI.h"


CUI::CUI()
	:m_bGun(false), m_iCoin(0)
{
}


CUI::~CUI()
{
}

void CUI::Initialize()
{
	m_tLifeRect.left = 25;
	m_tLifeRect.right = 40;
	m_tLifeRect.top = 5;
	m_tLifeRect.bottom = 20;

	m_tHp.left = 25;
	m_tHp.right = 125;
	m_tHp.top = 50;
	m_tHp.bottom = 60;

	m_tCoinRect.left = 700;
	m_tCoinRect.right = 760;
	m_tCoinRect.top = 20;
	m_tCoinRect.bottom = 50;

	m_tMp.left = 660;
	m_tMp.right = 760;
	m_tMp.top = 530;
	m_tMp.bottom = 560;

	m_tCoin.fX = 730;
	m_tCoin.fY = 35;
	m_tCoin.fCX = 15;
	m_tCoin.fCY = 15;

	m_fAngle = 1.f;

	m_tCoinTextRect.left = m_tCoinRect.left;
	m_tCoinTextRect.right = m_tCoinRect.right;
	m_tCoinTextRect.top = m_tCoinRect.top;
	m_tCoinTextRect.bottom = m_tCoinRect.bottom;

	m_tItemRect.left = 10;
	m_tItemRect.right = 220;
	m_tItemRect.top = 550;
	m_tItemRect.bottom = 590;

	m_tGun.left = 30;
	m_tGun.right = 55;
	m_tGun.top = 561;
	m_tGun.bottom = 566; 
}

void CUI::Update()
{
	m_fAngle += 4.f;
	if (m_iItem == ITEM_GUN)
		m_bGun = true;
}
#define DEGREE (PI / 180.f)
void CUI::Late_Update()
{
	m_tCoinRect.left = (LONG)(m_tCoin.fX - (m_tCoin.fCX * sinf(m_fAngle * DEGREE)));
	m_tCoinRect.right = (LONG)(m_tCoin.fX + (m_tCoin.fCX * sinf(m_fAngle * DEGREE)));
	m_tCoinRect.top = (LONG)(m_tCoin.fY - (m_tCoin.fCY));
	m_tCoinRect.bottom = (LONG)(m_tCoin.fY + (m_tCoin.fCY));
}

void CUI::Render(HDC _hDC)
{
	//DRAW LIFE
	Ellipse(_hDC, m_tLifeRect.left, m_tLifeRect.top, m_tLifeRect.right, m_tLifeRect.bottom);

	MoveToEx(_hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right) * 0.5f), m_tLifeRect.bottom,nullptr);
	LineTo(_hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right) * 0.5f), m_tLifeRect.bottom + 10);

	LineTo(_hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right) * 0.5f - 7), m_tLifeRect.bottom + 20);

	MoveToEx(_hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5), m_tLifeRect.bottom + 10, nullptr);
	LineTo(_hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5 + 7), m_tLifeRect.bottom + 20);

	MoveToEx(_hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5), m_tLifeRect.bottom + 2, nullptr);
	LineTo(_hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5 - 7), m_tLifeRect.bottom + 10);

	MoveToEx(_hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5), m_tLifeRect.bottom + 2, nullptr);
	LineTo(_hDC, (LONG)((m_tLifeRect.left + m_tLifeRect.right)*0.5 + 7), m_tLifeRect.bottom + 10);

	//DRAW LIFE
	TCHAR	Temp[64];
	wsprintf(Temp, L"%d", m_iLife);
	TextOut(_hDC, m_tLifeRect.right + 10, m_tLifeRect.top + 5, TEXT("X"), 1);
	TextOut(_hDC, m_tLifeRect.right + 30, m_tLifeRect.top + 5, Temp, lstrlen(Temp));

	//DRAW COIN
	Ellipse(_hDC, m_tCoinRect.left -15, m_tCoinRect.top, m_tCoinRect.right -15, m_tCoinRect.bottom);
	TCHAR	Dest[64];
	wsprintf(Dest, L"%d", m_iCoin);
	TextOut(_hDC, m_tCoinTextRect.right - 20, m_tCoinTextRect.top + 5, TEXT("X"), 1);
	TextOut(_hDC, m_tCoinTextRect.right, m_tCoinTextRect.top + 5, Dest, lstrlen(Dest));

	//DRAW ITEM
	Rectangle(_hDC, m_tItemRect.left, m_tItemRect.top, m_tItemRect.right, m_tItemRect.bottom);
	if (m_bGun == true)
	{
		//Rectangle(_hDC,m_tItemRect.left + 100, m_tItemRect.top, m_tItemRect.right - 100, m_tItemRect.bottom);
		Rectangle(_hDC, m_tGun.left - 2, m_tGun.top - 5, m_tGun.right + 2, m_tGun.bottom + 15);
		Rectangle(_hDC, m_tGun.left, m_tGun.top, m_tGun.right, m_tGun.bottom);
		Rectangle(_hDC, m_tGun.left + 20, m_tGun.top, m_tGun.right, m_tGun.bottom + 10);
		MoveToEx(_hDC, m_tGun.left + 13, m_tGun.bottom, nullptr);
		LineTo(_hDC, m_tGun.left + 20, m_tGun.bottom + 3);
	}

	//DRAW HP
	Rectangle(_hDC, m_tHp.left, m_tHp.top, m_tHp.right, m_tHp.bottom);
	Rectangle(_hDC, m_tHp.left, m_tHp.top, m_tHp.left + m_iHp, m_tHp.bottom);

	//DRAW MP
	Rectangle(_hDC, m_tMp.left, m_tMp.top, m_tMp.right, m_tMp.bottom);
	Rectangle(_hDC, m_tMp.left, m_tMp.top, m_tMp.left + m_iMp, m_tMp.bottom);
}

void CUI::Release()
{
}