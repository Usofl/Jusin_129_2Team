#pragma once
#include "Obj.h"
#include "Line.h"
class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static bool Collision_Line(const CObj& _Obj, const std::list<CObj*>& m_Line_List, float& _fX);
	static void Collision_Player_Block(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Block_List);
	static bool Collision_Block_Block(const CObj& _Obj, std::list<CObj*>& m_Block_List);

};