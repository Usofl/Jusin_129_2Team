#include "stdafx.h"
#include "Collision.h"
#include "Line.h"
#include "Player.h"
#include "ObjMgr.h"
#include "UiMgr.h"
#include "KeyMgr.h"
#include "Block.h"
#include "Coin.h"
#include "Ladder.h"
#include "Key.h"
#include "GomuFactory.h"


CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

bool CCollision::Collision_Line(const CObj& _Obj, const std::list<CObj*>& m_Line_List, float& _fY)
{
	LINEPOINT _Line_Left{0,0};
	LINEPOINT _Line_Right{0,0};
	float _fLine_Y(0.f);

	if (m_Line_List.empty())
	{
		return false;
	}
	
	CObj*		pTarget = nullptr;

	for (auto& _Line : m_Line_List)
	{
		CLine* line = static_cast<CLine*>(_Line);

		_Line_Left = line->Get_LinePoint().tLeft;
		_Line_Right = line->Get_LinePoint().tRight;

		if (_Obj.Get_Info().fX >= _Line_Left.fX && _Obj.Get_Info().fX <= _Line_Right.fX)
		{
			_fLine_Y = ((_Line_Right.fY - _Line_Left.fY) / (_Line_Right.fX - _Line_Left.fX)) 
						* (_Obj.Get_Info().fX - _Line_Left.fX)	+ _Line_Left.fY;

			if (_Obj.Get_Info().fY - 20.f <= _fLine_Y)
			{
				if (pTarget && _fY > _fLine_Y)
				{
					pTarget = line;
					_fY = _fLine_Y;
				}
				else if (!pTarget)
				{
					pTarget = line;
					_fY = _fLine_Y;
				}
			}
		}
	}

	if (nullptr == pTarget)
	{
		_fY = WINCY;
		return false;
	}

	return true;
}

void CCollision::Collision_Player_RightWall()
{
	for (auto& iter : OBJMGR->Get_NotBeing_list(NOTBEING_WALL))
	{
		CLine* line = static_cast<CLine*>(iter);
		POINT& fLeft_Leg = static_cast<CPlayer*>(PLAYER)->Get_Left_Leg();
		//벽vs플레이어
		if (PLAYER->Get_Info().fY > line->Get_LinePoint().tLeft.fY &&
			PLAYER->Get_Info().fY < line->Get_LinePoint().tRight.fY
			)
		{
			if (PLAYER->Get_Info().fX> line->Get_LinePoint().tLeft.fX
				&&
				PLAYER->Get_Info().fX - (PLAYER->Get_Info().fCX * 0.5f) + 5.f < line->Get_LinePoint().tLeft.fX)
			{
				static_cast<CPlayer*>(PLAYER)->Set_Left_Move(true);
				return;
			}
		}
	}
	static_cast<CPlayer*>(PLAYER)->Set_Left_Move(false);
	return;
}

void CCollision::Collision_Player_LeftWall()
{
	for (auto& iter : OBJMGR->Get_NotBeing_list(NOTBEING_WALL))
	{
		CLine* line = static_cast<CLine*>(iter);
		POINT& fLeft_Leg = static_cast<CPlayer*>(PLAYER)->Get_Left_Leg();
		//벽vs플레이어
		if (PLAYER->Get_Info().fY > line->Get_LinePoint().tLeft.fY &&
			PLAYER->Get_Info().fY < line->Get_LinePoint().tRight.fY
			)
		{
			if (PLAYER->Get_Info().fX < line->Get_LinePoint().tLeft.fX
				&&
				PLAYER->Get_Info().fX + (PLAYER->Get_Info().fCX * 0.5f - 5.f) > line->Get_LinePoint().tLeft.fX)
			{
				static_cast<CPlayer*>(PLAYER)->Set_Right_Move(true);
				return;
			}
		}
	}
	static_cast<CPlayer*>(PLAYER)->Set_Right_Move(false);
	return;
} 

void CCollision::Collision_Player_Ladder()
{
	CPlayer* player = static_cast<CPlayer*>(PLAYER);

	for (auto& iter : OBJMGR->Get_NotBeing_list(NOTBEING_LADDER))
	{
		if ((LONG)player->Get_Info().fX <= iter->Get_Rect().right &&
			(LONG)player->Get_Info().fX >= iter->Get_Rect().left &&
			(LONG)player->Get_Info().fY <= iter->Get_Rect().bottom &&
			(LONG)player->Get_Info().fY >= iter->Get_Rect().top)
		{
			if (KEYMGR->Key_Pressing(VK_UP))
			{
				player->Clim_Ladder();
			}
		}
	}
}

void CCollision::Collision_Player_Block(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Block_List)
{
	for (auto& _player : m_Obj_List)
	{
		RECT _player_rc = _player->Get_Rect();
		INFO _player_info = _player->Get_Info();
		for (auto& _block : m_Block_List)
		{
			float fWidth = abs(_player_info.fX - _block->Get_Info().fX);
			float fHeight = abs(_player_info.fY - _block->Get_Info().fY);

			float fCX = (_player_info.fCX + _block->Get_Info().fCX) * 0.5f;
			float fCY = (_player_info.fCY + _block->Get_Info().fCY) * 0.5f;

			if (fCX > fWidth && fCY > fHeight)
			{
				float _fChangeX(fCX - fWidth);
				float _fChangeY(fCY - fHeight);
				if (_fChangeX > _fChangeY)
				{
					if (_player_info.fY > _block->Get_Info().fY)
					{
						if (_player_info.fY - _player_info.fCY*0.5f < _block->Get_Info().fY + _block->Get_Info().fCY * 0.5f)
						{
							static_cast<CPlayer*>(_player)->Set_Jump();
						}
					}
				}
				else
				{
					//우
					if(_player_info.fY > _block->Get_Info().fY || static_cast<CPlayer*>(_player)->Get_Pool())
					{
						if (_player_info.fX > _block->Get_Info().fX)
						{
					
							if (static_cast<CPlayer*>(_player)->Get_Pool())
							{
								float _fTemp = _block->Get_Info().fX + 5.f;
								if (static_cast<CBlock*>(_block)->Get_Block_Up() != nullptr)
								{
									static_cast<CPlayer*>(_player)->Set_Left_Move(true);
									static_cast<CPlayer*>(_player)->Set_Right_Move(true);
									return;
								}
								if (Collision_Block_To_RightBlock(_block, _fTemp))
								{
									static_cast<CPlayer*>(_player)->Set_Left_Move(true);
									static_cast<CPlayer*>(_player)->Set_Right_Move(false);
									//return;
								}


								_block->Set_Pos(_block->Get_Info().fX + 5.f, _block->Get_Info().fY);
								if (abs(_player_info.fX - _block->Get_Info().fX) < fCX)
									_block->Set_Pos(_player_info.fX - fCX + 10.f, _block->Get_Info().fY);
							}
							else
							{
								static_cast<CPlayer*>(PLAYER)->Set_Pos(PLAYER->Get_Info().fX + _fChangeX, PLAYER->Get_Info().fY);
								static_cast<CPlayer*>(PLAYER)->SetBody();
							}
						}
						else//좌충돌
						{
							if (static_cast<CPlayer*>(_player)->Get_Pool())
							{
								float _fTemp = _block->Get_Info().fX - 5.f;
								if (static_cast<CBlock*>(_block)->Get_Block_Up() != nullptr)
								{
									static_cast<CPlayer*>(_player)->Set_Left_Move(true);
									static_cast<CPlayer*>(_player)->Set_Right_Move(true);
									return;
								}
								if (Collision_Block_To_LeftBlock(_block, _fTemp))
								{
									static_cast<CPlayer*>(_player)->Set_Right_Move(true);
									static_cast<CPlayer*>(_player)->Set_Left_Move(false);
									//return;
								}
								_block->Set_Pos(_block->Get_Info().fX - 5.f, _block->Get_Info().fY);
								if (abs(_player_info.fX - _block->Get_Info().fX) < fCX)
									_block->Set_Pos(_player_info.fX + fCX - 10.f, _block->Get_Info().fY);
							}
							else
							{
								PLAYER->Set_Pos(PLAYER->Get_Info().fX - _fChangeX, PLAYER->Get_Info().fY);
								static_cast<CPlayer*>(PLAYER)->SetBody();
							}
						}
					}
				}
			}
		}
	}
}

bool CCollision::Collision_Block_To_LeftBlock(CObj* _Obj, float _fTemp)
{
	for (auto& _block : OBJMGR->Get_NotBeing_list(NOTBEING_BLOCK))
	{
		if (_Obj == _block)
		{
			continue;
		}

		float fWidth = abs(_fTemp - _block->Get_Info().fX);
		float fHeight = abs(_Obj->Get_Info().fY - _block->Get_Info().fY);

		float fCX = (_Obj->Get_Info().fCX + _block->Get_Info().fCX) * 0.5f + 5.f;
		float fCY = (_Obj->Get_Info().fCY + _block->Get_Info().fCY) * 0.5f + 5.f;

		if (fCX > fWidth && fCY > fHeight)
		{
			float _fChangeX(fCX - fWidth);
			float _fChangeY(fCY - fHeight);
			if (_fChangeX < _fChangeY)
			{
				if (_Obj->Get_Info().fY + 0.5f >= _block->Get_Info().fY)
				{
					//우충돌
					if (_fTemp < _block->Get_Info().fX)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool CCollision::Collision_Block_To_RightBlock(CObj* _Obj, float _fTemp)
{
	for (auto& _block : OBJMGR->Get_NotBeing_list(NOTBEING_BLOCK))
	{

		if (_Obj == _block)
		{
			continue;
		}

		float fWidth = abs(_fTemp - _block->Get_Info().fX);
		float fHeight = abs(_Obj->Get_Info().fY - _block->Get_Info().fY);

		float fCX = (_Obj->Get_Info().fCX + _block->Get_Info().fCX) * 0.5f + 5.f;
		float fCY = (_Obj->Get_Info().fCY + _block->Get_Info().fCY) * 0.5f + 5.f;

		if (fCX > fWidth && fCY > fHeight)
		{
			float _fChangeX(fCX - fWidth);
			float _fChangeY(fCY - fHeight);
			if (_fChangeX < _fChangeY)
			{
				if (_Obj->Get_Info().fY >= _block->Get_Info().fY)
				{
					if (_fTemp > _block->Get_Info().fX)
					{
						//_Obj->Set_Pos(_block->Get_Info().fX - _fChangeX, _block->Get_Info().fY);
						return true;
					}
				}
			}
		}
	}
	return false;
}

void CCollision::Collision_Block_Block()
{
	std::list<CObj*>& m_Block_List = OBJMGR->Get_NotBeing_list(NOTBEING_BLOCK);
	
	CBlock* _block1_casting = nullptr;
	CBlock* _block2_casting = nullptr;

	for (auto& _block : m_Block_List)
	{

		for (auto& _block_2 : m_Block_List)
		{
			_block1_casting = static_cast<CBlock*>(_block);
			//_block2_casting = static_cast<CBlock*>(_block_2);
			if (_block == _block_2)
			{
				continue;
			}

			float fWidth = fabs((_block)->Get_Info().fX - (_block_2)->Get_Info().fX);
			float fHeight = fabs((_block)->Get_Info().fY - (_block_2)->Get_Info().fY);

			float fCX = ((_block)->Get_Info().fCX + (_block_2)->Get_Info().fCX) * 0.5f;
			float fCY = ((_block)->Get_Info().fCY + (_block_2)->Get_Info().fCY) * 0.5f + 50.f;

			if (fCX > fWidth && fCY > fHeight)
			{
				float _fChangeX(fCX - fWidth);
				float _fChangeY(fCY - fHeight);

				if (!(_fChangeX > _fChangeY))
				{
					if ((_block)->Get_Info().fX > (_block_2)->Get_Info().fX) //우충돌
					{
						_block1_casting->Set_Block_Left(_block_2);
						//static_cast<CPlayer*>(PLAYER)->Set_Left_Move(true);
						//_block->Set_Pos(_block->Get_Info().fX + _fChangeX, _block->Get_Info().fY);
						//_block2_casting->Set_Block_Right(_block);
					}
					else if ((_block)->Get_Info().fX < (_block_2)->Get_Info().fX) //좌충돌
					{
						_block1_casting->Set_Block_Right(_block_2);
						//static_cast<CPlayer*>(PLAYER)->Set_Right_Move(true);
						//_block->Set_Pos(_block->Get_Info().fX - _fChangeX, _block->Get_Info().fY);
						//_block2_casting->Set_Block_Left(_block);
					}
				}
				else
				{
					if ((_block)->Get_Info().fY > (_block_2)->Get_Info().fY)
					{
						_block1_casting->Set_Block_Up(_block_2);
					}
				}
			}
			else
			{
				_block1_casting->Set_NoBlock();
			}
		}
	}
}

void CCollision::Collision_Player_Bullet()
{
	RECT rc{};
	CPlayer* player = static_cast<CPlayer*>(PLAYER);

	for (auto& Bullet : OBJMGR->Get_Being_list(BEING_MONSTERBULLET))
	{
		if (IntersectRect(&rc, &(player->Get_Rect()), &(Bullet->Get_Rect())))
		{
			if (player->Get_Balloon())
			{
				OBJMGR->Add_Being(BEING_COUNTERBULLET, *CGomuFactory::Create_Counter_Bullet(Bullet->Get_Info())) ;
			}
			else
			{
				static_cast<CItem*>(OBJMGR->Get_NotBeing_list(NOTBEING_ITEM).front())->PlayerColiision();
			}
			Bullet->Set_Hp(0);
		}
	}
}

void CCollision::Collision_Player_Coin(CObj& _Obj, std::list<CCoin*>& m_Coin_List)
{
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	RECT Player_Rc = _Obj.Get_Rect();
	INFO _Player_Info = _Obj.Get_Info();

	INFO Coin_Info;
	RECT Collision = { 0,0,0,0 };

	for (auto& _Coin : m_Coin_List)
	{
		Coin_Info = _Coin->Get_Info();
		
		Collision.left = LONG(Player_Rc.left - Coin_Info.fCX);
		Collision.right = LONG(Player_Rc.right + Coin_Info.fCX);
		Collision.top = LONG(Player_Rc.top - Coin_Info.fCY);
		Collision.bottom = LONG(Player_Rc.bottom + Coin_Info.fCY);

		if ((Coin_Info.fX > Collision.left && Coin_Info.fX < Collision.right) && (Coin_Info.fY < Collision.bottom && Coin_Info.fY > Collision.top))
		{
			player->PlayerCoinColli();
			_Coin->Dead();
		}
	}
}


void CCollision::Collision_Thorn()
{
	if (PLAYER->Get_Info().fX + PLAYER->Get_Info().fCX * 0.5f <
		OBJMGR->Get_NotBeing_list(NOTBEING_TRAP).front()->Get_Info().fX
		+ OBJMGR->Get_NotBeing_list(NOTBEING_TRAP).front()->Get_Info().fCX * 0.5f)
	{
		PLAYER->Set_Hp(0);
	}	
}


void CCollision::Collision_Player_Item(CObj& _Obj, std::list<CObj*>& m_Item_List)
{
	RECT rc;
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	for (auto& _iTEM : m_Item_List)
	{
		if (IntersectRect(&rc, &player->Get_Rect(), &_iTEM->Get_Rect()))
		{
			player->Put_ItemType(static_cast<CItem*>(_iTEM)->Itemtype());
			_iTEM->Set_Hp(0);
			CUiMgr::Get_Instance()->Get_Uilist().front()->Get_Itemtype(static_cast<CItem*>(_iTEM)->Itemtype());
		}
	}
}
void CCollision::Collision_Player_Ladder(CObj& _Obj, std::list<CObj*>& m_Ladder_List)
{
	RECT rc;
	CPlayer* player = static_cast<CPlayer*>(&_Obj);
	for (auto& _iTEM : m_Ladder_List)
	{
		if (IntersectRect(&rc, &player->Get_Rect(), &_iTEM->Get_Rect()))
		{
			_iTEM->Set_Hp(0);
			CUiMgr::Get_Instance()->Get_Uilist().front()->Get_Itemtype(static_cast<CLadder*>(_iTEM)->Itemtype());
		}
	}
}

void CCollision::Collision_Key_Line(std::list<CObj*>& m_Item_List, std::list<CObj*>& m_Line_List)
{
	for (auto& _Line : m_Line_List)
	{
		CLine* line = static_cast<CLine*>(_Line);

		for (auto& _Item : m_Item_List)
		{
			if (line->Get_LinePoint().tLeft.fX < _Item->Get_Info().fX && line->Get_LinePoint().tRight.fX > _Item->Get_Info().fX)
			{
				if (((line->Get_LinePoint().tRight.fY - line->Get_LinePoint().tLeft.fY) / (line->Get_LinePoint().tRight.fX - line->Get_LinePoint().tLeft.fX)
					*(_Item->Get_Info().fX - line->Get_LinePoint().tLeft.fX) + line->Get_LinePoint().tLeft.fY) == _Item->Get_Info().fY)
				{
					static_cast<CItem*>(_Item)->PlayerColiision();
				}
			}
		}
	}
}


//void CCollision::Collision_Block_Wall()
//{
//	for (auto& _block : m_Block_List)
//
//
//	for (auto& iter : OBJMGR->Get_NotBeing_list(NOTBEING_WALL))
//}


