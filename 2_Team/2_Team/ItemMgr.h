#pragma once
#include "Item.h"
class CItemMgr
{
private:
	CItemMgr();
	~CItemMgr();
public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	std::list<CItem*>	Get_Item_List() { return m_Itemlist; }
	static		CItemMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CItemMgr;
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
	static CItemMgr*	m_pInstance;
	std::list<CItem*>	m_Itemlist;
};

