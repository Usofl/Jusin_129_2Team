#pragma once
#include "Line.h"
#include "Obj.h"

class CLineMgr
{
public:
	CLineMgr();
	~CLineMgr();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(HDC _hDC);
	void Release(void);



private:
	std::list<CObj*> m_Line_List;

public:
	static CLineMgr*& Get_Instance (void)
	{
		if (!pInstance)
			pInstance = new CLineMgr;

		return pInstance;
	}

	static void Destroy_Instance (void)
	{
		if (pInstance)
		{
			Safe_Delete<CLineMgr*>(pInstance);
			pInstance = nullptr;
		}		
	}



private:
	static CLineMgr* pInstance;
};

