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
	m_tRect.left = 2400;
	m_tRect.right = 2425;
	m_tRect.top = 370;
	m_tRect.bottom = 395;
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
	//45 Â÷ÀÌ³ª¾ßµÊ!
	if (m_iHp == 0)
	{

		if (!m_bCount)
		{
			m_iTime = (GetTickCount());
			m_bCount = true;
		}
		Rectangle(_hDC, m_tColliradder.left + iScrollX, m_tColliradder.top + 10, m_tColliradder.right + iScrollX, m_tColliradder.bottom - 10);
		Rectangle(_hDC, m_tColliradder.left - 5 + iScrollX, m_tColliradder.top - 10, m_tColliradder.left + iScrollX, m_tColliradder.bottom + 10);
		Rectangle(_hDC, m_tColliradder.right + iScrollX, m_tColliradder.top - 10, m_tColliradder.right + 5 + iScrollX, m_tColliradder.bottom + 10);
		for (int i = 0; i < 7; ++i)
		{
			if (m_iTime + 700 + (i * 700) < GetTickCount())
			{
				Rectangle(_hDC, m_tColliradder.left + iScrollX, m_tColliradder.top - 35 - (45 * i), m_tColliradder.right + iScrollX, m_tColliradder.bottom - 55 - (45 * i));
				Rectangle(_hDC, m_tColliradder.left - 5 + iScrollX, m_tColliradder.top - 55 - (45 * i), m_tColliradder.left + iScrollX, m_tColliradder.bottom - 35 - (45 * i));
				Rectangle(_hDC, m_tColliradder.right + iScrollX, m_tColliradder.top - 55 - (45 * i), m_tColliradder.right + 5 + iScrollX, m_tColliradder.bottom - 35 - (45 * i));
			}
		}
	}
	else
	{
		Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + 10, m_tRect.right + iScrollX, m_tRect.bottom - 10);
		Rectangle(_hDC, m_tRect.left - 5 + iScrollX, m_tRect.top - 10, m_tRect.left + iScrollX, m_tRect.bottom + 10);
		Rectangle(_hDC, m_tRect.right + iScrollX, m_tRect.top - 10, m_tRect.right + 5 + iScrollX, m_tRect.bottom + 10);
	}
}

void CLadder::Release(void)
{
}
