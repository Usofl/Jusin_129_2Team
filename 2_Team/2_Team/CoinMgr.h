#pragma once
#include "Coin.h"

class CCoinMgr
{
private:
	CCoinMgr();
	~CCoinMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		LateUpdate(void);
	void		Render(HDC hDC);
	void		Release(void);


	static		CCoinMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCoinMgr;
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
	static CCoinMgr*	m_pInstance;
	std::list<CCoin*>	m_CoinList;
};

