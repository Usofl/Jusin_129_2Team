#pragma once
#include "Obj.h"
class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static void Collision_Line(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Line_List);
};

