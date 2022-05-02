#include "stdafx.h"
#include "ObjMgr.h"
#include "Gigant_Fistol.h"


CGigant_Fistol::CGigant_Fistol()
{
}

CGigant_Fistol::CGigant_Fistol(const POINT & _tPoint, const int & _iReverse, const unsigned int& _iSize)
{
	m_tInfo.fX = (float)_tPoint.x;
	m_tInfo.fY = (float)_tPoint.y;

	m_tInfo.fCX = 30.f * _iSize;
	m_tInfo.fCY = 15.f * _iSize;

	m_iHp = 10 * _iSize;
	m_iAtt = 4 * _iSize;

	m_iReverse = _iReverse;
}

CGigant_Fistol::~CGigant_Fistol()
{
}

void CGigant_Fistol::Initialize(void)
{
	m_fSpeed = 7.f;
	m_uiArea = (unsigned int)(m_tInfo.fCX / m_fSpeed) - 7;

	m_iHp = 30;
}

const int & CGigant_Fistol::Update(void)
{
	if (0 >= m_iHp)
	{
		return OBJ_DEAD;
	}

	if (m_uiArea)
	{
		m_tInfo.fX += (m_fSpeed * m_iReverse);
		m_AreaStack.push(m_tInfo.fX);
		--m_uiArea;
	}
	else
	{
		m_tInfo.fX = m_AreaStack.top();
		m_AreaStack.pop();
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CGigant_Fistol::Late_Update(void)
{
	if (m_AreaStack.empty())
	{
		m_iHp = 0;
	}
}

void CGigant_Fistol::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	if (1 != m_iReverse)
	{
		long lTemp = m_tRect.left;
		m_tRect.left = m_tRect.right;
		m_tRect.right = lTemp;
	}
	
	MoveToEx(_hDC, (LONG)(PLAYER->Get_Info().fX) + iScrollX, (LONG)(PLAYER->Get_Info().fY) + iScrollY, nullptr);
	LineTo(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY);
	MoveToEx(_hDC, (LONG)(PLAYER->Get_Info().fX) + iScrollX, (LONG)(PLAYER->Get_Info().fY) + iScrollY, nullptr);
	LineTo(_hDC, m_tRect.left + iScrollX, m_tRect.bottom + iScrollY);

	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 220, 177));
	OldBrush = (HBRUSH)SelectObject(_hDC, MyBrush);

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	SelectObject(_hDC, OldBrush);
	DeleteObject(MyBrush);

	MoveToEx(_hDC, m_tRect.right + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.3f) + iScrollY, nullptr);
	LineTo(_hDC, m_tRect.right - (LONG)(m_tInfo.fCX * 0.2f * m_iReverse) + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.3f) + iScrollY);

	MoveToEx(_hDC, m_tRect.right + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.5f) + iScrollY, nullptr);
	LineTo(_hDC, m_tRect.right - (LONG)(m_tInfo.fCX * 0.2f * m_iReverse) + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.5f) + iScrollY);

	MoveToEx(_hDC, m_tRect.right + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.7f) + iScrollY, nullptr);
	LineTo(_hDC, m_tRect.right - (LONG)(m_tInfo.fCX * 0.2f * m_iReverse) + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.7f) + iScrollY);
}

void CGigant_Fistol::Release(void)
{
}
