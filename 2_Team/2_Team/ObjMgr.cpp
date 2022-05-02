#include "stdafx.h"
#include "ObjMgr.h"
#include "Collision.h"
#include "Player.h"
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
	OBJMGR->Add_Notbeing(NOTBEING_ITEM, *ItemFactory::Create_Key());
	OBJMGR->Add_Notbeing(NOTBEING_ITEM, *ItemFactory::Create_Life());
	OBJMGR->Add_Notbeing(NOTBEING_ITEM, *ItemFactory::Create_Gun());
	OBJMGR->Add_Notbeing(NOTBEING_LADDER, *ItemFactory::Create_Ladder());
	OBJMGR->Add_Being(BEING_MONSTER, *CMonsterFactory::Create_Monster(M_Cloud_TURTLE));
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

	CCollision::Collision_Player_Ladder();
	CCollision::Collision_Player_Block(OBJMGR->Get_Being_list(BEING_PLAYER), OBJMGR->Get_NotBeing_list(NOTBEING_BLOCK));
	CCollision::Collision_Block_Block();

	CCollision::Collision_Player_Bullet();
	CCollision::Collision_Player_Ladder(*OBJMGR->Get_Being_list(BEING_PLAYER).front()
		, OBJMGR->Get_NotBeing_list(NOTBEING_LADDER));
	//CCollision::Collision_Player_Ladder(OBJ);
	//CCollision::Collision_Key_Line(OBJMGR->Get_NotBeing_list(NOTBEING_ITEM), OBJMGR->Get_NotBeing_list(NOTBEING_LINE));
	//CCollision::Collision_Line(OBJMGR->Get_NotBeing_list(NOTBEING_LINE), OBJMGR->Get_NotBeing_list(NOTBEING_ITEM), 0);
}

void CObjMgr::Render(HDC _hdc)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	for (auto& iterlist : m_NotBeing_list)
	{
		for (auto& iter : iterlist)
		{
			iter->Render(_hdc);
		}
	}

	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
	OldBrush = (HBRUSH)SelectObject(_hdc, MyBrush);

	Ellipse(_hdc, 4300 + iScrollX, 180 + iScrollY, 4400 + iScrollX, 280 + iScrollY);
	Ellipse(_hdc, 4900 + iScrollX, 180 + iScrollY, 5000 + iScrollX, 280 + iScrollY);

	SelectObject(_hdc, OldBrush);
	DeleteObject(MyBrush);

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
