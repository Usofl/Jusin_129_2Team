#pragma once
//#include "Include.h"
#include "Being.h"
#include "NotBeing.h"

class CObjMgr
{
public:
	CObjMgr();
	~CObjMgr();

	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Render(HDC _hdc);
	void Release(void);

	void Add_Being(const BEINGOBJ_ID& _ID, CObj& _Instance)
	{
		if (_ID >= BEING_END)
			return;

		m_Being_list[_ID].push_back(&_Instance);
	}
	void Add_Notbeing(const NOTBEINGOBJ_ID& _ID, CObj& _Instance)
	{
		if (_ID >= NOTBEING_END)
			return;

		m_NotBeing_list[_ID].push_back(&_Instance);
	}

	std::list<CObj*>& Get_Being_list(const BEINGOBJ_ID& _ID) { return m_Being_list[_ID]; }
	std::list<CObj*>& Get_NotBeing_list(const NOTBEINGOBJ_ID& _ID) { return m_NotBeing_list[_ID]; }

private:
	std::list<CObj*> m_Being_list[BEING_END];
	std::list<CObj*> m_NotBeing_list[NOTBEING_END];

public:
	static CObjMgr*& Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			Safe_Delete<CObjMgr*>(m_pInstance);
			m_pInstance = nullptr;
		}		
	}

	static int& Get_Life()
	{
		return m_iLife;
	}

	static void Set_Life(const int& _life)
	{
		m_iLife = _life;
	}

private:
	static CObjMgr* m_pInstance;
	static int m_iLife;
};

