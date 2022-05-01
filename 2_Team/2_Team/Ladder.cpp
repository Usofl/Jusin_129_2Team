#include "stdafx.h"
#include "Ladder.h"


CLadder::CLadder()
	:m_bCount(false)
{
}


CLadder::~CLadder()
{
}

void CLadder::Initialize(void)
{
	m_tRect.left = 670;
	m_tRect.right = 695;
	m_tRect.top = 320;
	m_tRect.bottom = 345;
	m_tColliradder = m_tRect;
}

const int & CLadder::Update(void)
{
	//if (m_iHp == 0)
		//m_tRect.top = 95;
	return OBJ_NOEVENT;
}

void CLadder::Late_Update(void)
{
}

void CLadder::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();
	//45 Â÷ÀÌ³ª¾ßµÊ!
	if (m_iHp == 0)
	{

		if (!m_bCount)
		{
			m_iTime = (GetTickCount());
			m_bCount = true;
		}
		Rectangle(_hDC, m_tColliradder.left + iScrollX, m_tColliradder.top + 10 + iScrollY, m_tColliradder.right + iScrollX, m_tColliradder.bottom - 10 + iScrollY);
		Rectangle(_hDC, m_tColliradder.left - 5 + iScrollX, m_tColliradder.top - 10 + iScrollY, m_tColliradder.left + iScrollX, m_tColliradder.bottom + 10 + iScrollY);
		Rectangle(_hDC, m_tColliradder.right + iScrollX, m_tColliradder.top - 10 + iScrollY, m_tColliradder.right + 5 + iScrollX, m_tColliradder.bottom + 10 + iScrollY);
		for (int i = 0; i < 5; ++i)
		{
			if (m_iTime + 700 + (i * 700) < GetTickCount())
			{
				Rectangle(_hDC, m_tColliradder.left + iScrollX, m_tColliradder.top - 35 - (45 * i) + iScrollY, m_tColliradder.right + iScrollX, m_tColliradder.bottom - 55 - (45 * i) + iScrollY);
				Rectangle(_hDC, m_tColliradder.left - 5 + iScrollX, m_tColliradder.top - 55 - (45 * i) + iScrollY, m_tColliradder.left + iScrollX, m_tColliradder.bottom - 35 - (45 * i) + iScrollY);
				Rectangle(_hDC, m_tColliradder.right + iScrollX, m_tColliradder.top - 55 - (45 * i) + iScrollY, m_tColliradder.right + 5 + iScrollX, m_tColliradder.bottom - 35 - (45 * i) + iScrollY);
			}
		}
	}
	else
	{
		Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom - 10 + iScrollY);
		Rectangle(_hDC, m_tRect.left - 5 + iScrollX, m_tRect.top - 10 + iScrollY, m_tRect.left + iScrollX, m_tRect.bottom + 10 + iScrollY);
		Rectangle(_hDC, m_tRect.right + iScrollX, m_tRect.top - 10 + iScrollY, m_tRect.right + 5 + iScrollX, m_tRect.bottom + 10 + iScrollY);
	}
}

void CLadder::Release(void)
{
}
