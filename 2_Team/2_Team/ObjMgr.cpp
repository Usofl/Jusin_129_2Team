#include "stdafx.h"
#include "ObjMgr.h"
#include "Collision.h"
#include "Player.h"
#include "LineFactory.h"


CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}

void CObjMgr::Initialize(void)
{
	LINEPOINT _Linepoint[2] = 
	{
		{200,400},
		{600,400}
	};
	m_NotBeing_list[NOTBEING_LINE].push_back(CLineFactory::Create_Line(_Linepoint[0], _Linepoint[1]));

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

	//CCollision::Collision_Line(m_Being_list[BEING_PLAYER], m_NotBeing_list[NOTBEING_LINE]);
	CCollision::Collision_Player_Line(m_Being_list[BEING_PLAYER], m_NotBeing_list[NOTBEING_LINE],
		static_cast<CPlayer*>(m_Being_list[BEING_PLAYER].front())->Get_Right_Leg(),
		static_cast<CPlayer*>(m_Being_list[BEING_PLAYER].front())->Get_Left_Leg()
	);

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
