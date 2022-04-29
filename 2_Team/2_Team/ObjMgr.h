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
	void Update(void);
	void Late_Update(void);
	void Render(HDC _hdc);
	void Release(void);

	void Add_Being(const BEINGOBJ_ID& _ID, CObj* _Instance)
	{
		if (_ID >= BEING_END || _Instance == nullptr)
			return;

		m_Being_list[_ID].push_back(_Instance);
	}
	void Add_Notbeing(const NOTBEINGOBJ_ID& _ID, CObj* _Instance)
	{
		if (_ID >= NOTBEING_END || _Instance == nullptr)
			return;

		m_NotBeing_list[_ID].push_back(_Instance);
	}

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

private:
	static CObjMgr* m_pInstance;
};

