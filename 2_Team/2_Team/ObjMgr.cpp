#include "stdafx.h"
#include "ObjMgr.h"
#include "Collision.h"
#include "Player.h"
#include "CoinMgr.h"
#include "LineFactory.h"
#include "BlockFactory.h"
#include "TrapFactory.h"
#include "ItemFactory.h"
#include "ItemMgr.h"
#include "MonsterFactory.h"

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

	CObj* player = new CPlayer;
	OBJMGR->Add_Being(BEING_PLAYER, *player);

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
	OBJMGR->Add_Notbeing(ITEM_KEY, *ItemFactory::Create_Key());
	OBJMGR->Add_Notbeing(NOTBEING_ITEM, *ItemFactory::Create_Life());
	OBJMGR->Add_Notbeing(NOTBEING_ITEM, *ItemFactory::Create_Recovery());
	OBJMGR->Add_Notbeing(NOTBEING_ITEM, *ItemFactory::Create_Stamina());
	OBJMGR->Add_Notbeing(NOTBEING_ITEM, *ItemFactory::Create_Gun());
	OBJMGR->Add_Notbeing(NOTBEING_LADDER, *ItemFactory::Create_Ladder());
	OBJMGR->Add_Notbeing(NOTBEING_ROOM, *ItemFactory::Create_Room());
	OBJMGR->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(M_Cloud_TURTLE));
}

void CObjMgr::Update(void)
{	
	if (PLAYER->Update() == OBJ_DEAD)
	{
		Safe_Delete<CObj*>(PLAYER);
		PLAYER = new CPlayer;
		PLAYER->Initialize();
		OBJMGR->Get_NotBeing_list(NOTBEING_TRAP).front()->Set_Pos(50.f,300.f);

		SCROLLMGR->Set_ScrollX(-SCROLLMGR->Get_ScrollX());
		
	}
	else
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



		for (int i = BEING_MONSTER; i < BEING_END; ++i)
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
	CCollision::Collision_Thorn();

	CCollision::Collision_Player_Ladder();
	CCollision::Collision_Player_Block(OBJMGR->Get_Being_list(BEING_PLAYER), OBJMGR->Get_NotBeing_list(NOTBEING_BLOCK));
	CCollision::Collision_Block_Block();

	//CCollision::Collision_Player_Bullet();
	CCollision::Collision_Player_Ladder(*OBJMGR->Get_Being_list(BEING_PLAYER).front()
		, OBJMGR->Get_NotBeing_list(NOTBEING_LADDER));
	CCollision::Collision_Player_Coin(*OBJMGR->Get_Being_list(BEING_PLAYER).front()
		, CCoinMgr::Get_Instance()->Get_Coin_List());
	CCollision::Collision_Player_Item(*OBJMGR->Get_Being_list(BEING_PLAYER).front()
		, OBJMGR->Get_NotBeing_list(NOTBEING_ITEM));
	CCollision::Collision_Player_Key(*OBJMGR->Get_Being_list(BEING_PLAYER).front(), OBJMGR->Get_NotBeing_list(ITEM_KEY));

	CCollision::Collision_Fistol_Monster();
	CCollision::Collision_Gigant_Monster();
	CCollision::Collision_Counter_Monster();

	CCollision::Collision_Player_Room();
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
		for (auto iter = iterlist.begin(); iter != iterlist.end();)
		{
			(*iter)->Release();
			Safe_Delete<CObj*>(*iter);

			iter = iterlist.erase(iter);
		}
	}

	for (auto& iterlist : m_Being_list)
	{
		for (auto iter = iterlist.begin(); iter != iterlist.end();)
		{
			(*iter)->Release();
			Safe_Delete<CObj*>(*iter);

			iter = iterlist.erase(iter);
		}
	}
}
