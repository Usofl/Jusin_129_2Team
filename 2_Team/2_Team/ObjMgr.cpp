#include "stdafx.h"
#include "ObjMgr.h"
#include "Collision.h"
#include "Player.h"
#include "LineFactory.h"
#include "BlockFactory.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}

void CObjMgr::Initialize(void)
{
	LINEPOINT _Linepoint[5] = 
	{
		{ 000,400 },
		{ 800,400 },
		{ 000,320 },
		{ 400,320 },
		{ 700,100 }
	};
	m_NotBeing_list[NOTBEING_LINE].push_back(CLineFactory::Create_Line(_Linepoint[0], _Linepoint[1]));
	m_NotBeing_list[NOTBEING_LINE].push_back(CLineFactory::Create_Line(_Linepoint[2], _Linepoint[3]));
	m_NotBeing_list[NOTBEING_LINE].push_back(CLineFactory::Create_Line(_Linepoint[3], _Linepoint[4]));

	m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(200, 0));
	m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(250, 100));
	m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(300, 200));
	m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(350, 300));


	for (auto& iterlist : m_NotBeing_list)
	{
		for (auto& iter : iterlist)
		{
			iter->Initialize();
		}
	}

	for (auto& iterlist : m_Being_list)
	{
		for (auto& iter : iterlist)
		{
			iter->Initialize();
		}
	}
}

void CObjMgr::Update(void)
{
	for (int i = 0; i < NOTBEING_END; ++i)
	{
		for (auto& iter = m_NotBeing_list[i].begin(); iter != m_NotBeing_list[i].end();)
		{
			if ((*iter)->Update() == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_NotBeing_list[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}



	for (int i = 0; i < BEING_END; ++i)
	{
		for (auto& iter = m_Being_list[i].begin(); iter != m_Being_list[i].end();)
		{
			if ((*iter)->Update() == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_Being_list[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}		
	}



}

void CObjMgr::Late_Update(void)
{
	for (auto& iterlist : m_NotBeing_list)
	{
		for (auto& iter : iterlist)
		{
			iter->Late_Update();
		}
	}

	for (auto& iterlist : m_Being_list)
	{
		for (auto& iter : iterlist)
		{
			iter->Late_Update();
		}
	}

	CCollision::Collision_Player_Block(OBJMGR->Get_Being_list(BEING_PLAYER), OBJMGR->Get_NotBeing_list(NOTBEING_BLOCK));
}

void CObjMgr::Render(HDC _hdc)
{
	for (auto& iterlist : m_NotBeing_list)
	{
		for (auto& iter : iterlist)
		{
			iter->Render(_hdc);
		}
	}

	for (auto& iterlist : m_Being_list)
	{
		for (auto& iter : iterlist)
		{
			iter->Render(_hdc);
		}
	}
}

void CObjMgr::Release(void)
{
}
