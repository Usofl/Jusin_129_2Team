#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left	= m_tInfo.fX - (m_tInfo.fCX*0.5f);
	m_tRect.top		= m_tInfo.fY - (m_tInfo.fCY*0.5f);
	m_tRect.right	= m_tInfo.fX + (m_tInfo.fCX*0.5f);
	m_tRect.bottom	= m_tInfo.fY + (m_tInfo.fCY*0.5f);
}

