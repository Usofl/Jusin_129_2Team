#pragma once
#include "UI.h"
class CUiMgr
{
private:
	CUiMgr();
	~CUiMgr();
public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	std::list<CUI*>& Get_Uilist() { return m_UiList; }

	static		CUiMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUiMgr;
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
	static CUiMgr*	m_pInstance;
	std::list<CUI*>	m_UiList;
};

