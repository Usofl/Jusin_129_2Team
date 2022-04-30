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
	static bool Collision_Player_LeftWall();
	static bool Collision_Player_RightWall();

public:
	static void Collision_Player_Bullet(std::list<CObj*>& _pPlayer, std::list<CObj*>& _pBullet);

	static void Collision_Player_Coin(CObj& _Obj, std::list<CCoin*>& m_Coin_List);
};