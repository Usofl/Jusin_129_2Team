#pragma once

#include "Include.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float		Get_ScrollX(void) { return m_fScrollX; }
	float		Get_ScrollY(void) { return m_fScrollY; }

	void		Set_ScrollX(const float& _fX) { m_fScrollX += _fX; }
	void		Set_ScrollY(const float& _fY) { m_fScrollX += _fY; }

public:
	static		CScrollMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScrollMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr*		m_pInstance;
	float					m_fScrollX;
	float					m_fScrollY;
};
