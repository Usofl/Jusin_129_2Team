#pragma once
#include "Obj.h"
#include "Line.h"
#include "Coin.h"

class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static bool Collision_Line(const CObj& _Obj, const std::list<CObj*>& m_Line_List, float& _fX);
	static void Collision_Player_Block(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Block_List);
	static void Collision_Block_Block();
	static void Collision_Player_LeftWall();
	static void Collision_Player_RightWall();
	static void Collision_Thorn();
	//static void Collision_Block_Wall();
	static bool Collision_Block_To_LeftBlock(CObj* _Obj, float _fTemp);
	static bool Collision_Block_To_RightBlock(CObj* _Obj, float _fTemp);

public:
	static void Collision_Player_Bullet(); 
	static void Collision_Player_Ladder();

	static void Collision_Player_Coin(CObj& _Obj, std::list<CCoin*>& m_Coin_List);
	static void Collision_Player_Item(CObj& _Obj, std::list<CObj*>& m_Item_List);
	static void Collision_Key_Line(std::list<CObj*>& m_Item_List, std::list<CObj*>& m_Line_List);
	static void Collision_Player_Ladder(CObj& _Obj, std::list<CObj*>& m_Ladder_List);

	static bool Check_Sphere(CObj& pDest, CObj& pSour);
	static void Collision_Sphere(std::list<CObj*>& _Dest, std::list<CObj*>& _Sour);

	
};