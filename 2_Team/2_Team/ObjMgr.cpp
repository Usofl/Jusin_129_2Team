#include "stdafx.h"
#include "ObjMgr.h"
#include "Collision.h"
#include "Player.h"
#include "LineFactory.h"
#include "BlockFactory.h"
#include "TrapFactory.h"
#include "ItemFactory.h"
#include "ItemMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Initialize(void)
{
	LINEPOINT _Linepoint[6] = 
	{
		{ 000,450 },
		{ 800,450 },
		{ 000,320 },
		{ 400,320 },
		{ 700,100 },
		{ 700,450 }
	};
	m_NotBeing_list[NOTBEING_LINE].push_back(CLineFactory::Create_Line(_Linepoint[0], _Linepoint[1]));
	m_NotBeing_list[NOTBEING_LINE].push_back(CLineFactory::Create_Line(_Linepoint[2], _Linepoint[3]));
	m_NotBeing_list[NOTBEING_LINE].push_back(CLineFactory::Create_Line(_Linepoint[3], _Linepoint[4]));

	m_NotBeing_list[NOTBEING_WALL].push_back(CLineFactory::Create_Line(_Linepoint[4], _Linepoint[5]));

	m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(200, 0));
	m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(280, 250));
	m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(360, 250));
	m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(440, 350));
	m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(520, 300));


	m_NotBeing_list[NOTBEING_TRAP].push_back(CTrapFactory::Create_Thorn());

	m_NotBeing_list[NOTBEING_ITEM].push_back(ItemFactory::Create_Gun());
	m_NotBeing_list[NOTBEING_ITEM].push_back(ItemFactory::Create_Life());

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
	for (auto& list_iter : m_NotBeing_list)
	{
		for (auto& iter = list_iter.begin(); iter != list_iter.end();)
		{
			if ((*iter)->Update() == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = list_iter.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	if (PLAYER->Update() == OBJ_DEAD)
	{

	}

	for (int i = BEING_MONSTER; i < BEING_END ; ++i)
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

	CCollision::Collision_Player_LeftWall();
	CCollision::Collision_Player_RightWall();

	CCollision::Collision_Player_Bullet(OBJMGR->Get_Being_list(BEING_PLAYER), OBJMGR->Get_Being_list(BEING_MONSTERBULLET));
		CCollision::Collision_Player_Block(OBJMGR->Get_Being_list(BEING_PLAYER), OBJMGR->Get_NotBeing_list(NOTBEING_BLOCK));
		CCollision::Collision_Block_Block();

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
	for (auto& iterlist : m_NotBeing_list)
	{
		for (auto& iter : iterlist)
		{
			iter->Release();
		}
	}

	for (auto& iterlist : m_Being_list)
	{
		for (auto& iter : iterlist)
		{
			iter->Release();
		}
	}
}
