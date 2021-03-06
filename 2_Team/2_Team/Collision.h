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
	static LINEPOINT* Collision_Portal();

public:
	static void Collision_Player_Bullet(); 
	static void Collision_Player_KOOPA_Bullet();
	static void Collision_Player_Ladder();

	static void Collision_Player_Coin(CObj& _Obj, std::list<CCoin*>& m_Coin_List);
	static void Collision_Player_Item(CObj& _Obj, std::list<CObj*>& m_Item_List);
	static void Collision_Player_Ladder(CObj& _Obj, std::list<CObj*>& m_Ladder_List);
	static void Collision_Fistol_Monster();
	static void Collision_Gigant_Monster();
	static void Collision_Counter_Monster();

	static bool Check_Sphere(CObj& pDest, CObj& pSour);
	static bool Collision_Player_Room();
	static void Collision_Player_Key(CObj& _Obj, std::list<CObj*>& m_Key_List);
	//static void Collision_Sphere(std::list<CObj*>& _Dest, std::list<CObj*>& _Sour);

public:
	static void Collision_Monster_Player();

};