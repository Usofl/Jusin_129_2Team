#pragma once
#include "Obj.h"
class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static void Collision_Line(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Line_List);
	static bool Collision_Player_Line(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Line_List, POINT& _Player_RightLeg, POINT& _Player_LeftLeg);
	static void Collision_Player_Block(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Block_List);
};

