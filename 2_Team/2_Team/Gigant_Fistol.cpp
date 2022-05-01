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
	if (1 != m_iReverse)
	{
		long lTemp = m_tRect.left;
		m_tRect.left = m_tRect.right;
		m_tRect.right = lTemp;
	}

	MoveToEx(_hDC, (LONG)(PLAYER->Get_Info().fX) + iScrollX, (LONG)(PLAYER->Get_Info().fY), nullptr);
	LineTo(_hDC, m_tRect.left + iScrollX, m_tRect.top);
	MoveToEx(_hDC, (LONG)(PLAYER->Get_Info().fX) + iScrollX, (LONG)(PLAYER->Get_Info().fY), nullptr);
	LineTo(_hDC, m_tRect.left + iScrollX, m_tRect.bottom);

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

	MoveToEx(_hDC, m_tRect.right + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.3f), nullptr);
	LineTo(_hDC, m_tRect.right - (LONG)(m_tInfo.fCX * 0.2f * m_iReverse) + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.3f));

	MoveToEx(_hDC, m_tRect.right + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.5f), nullptr);
	LineTo(_hDC, m_tRect.right - (LONG)(m_tInfo.fCX * 0.2f * m_iReverse) + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.5f));

	MoveToEx(_hDC, m_tRect.right + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.7f), nullptr);
	LineTo(_hDC, m_tRect.right - (LONG)(m_tInfo.fCX * 0.2f * m_iReverse) + iScrollX, m_tRect.top + (LONG)(m_tInfo.fCY * 0.7f));
}

void CGigant_Fistol::Release(void)
{
}
