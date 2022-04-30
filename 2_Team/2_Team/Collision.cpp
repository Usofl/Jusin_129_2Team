#include "stdafx.h"
#include "Collision.h"
#include "Line.h"
#include "Player.h"


CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

void CCollision::Collision_Line(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Line_List)
{
	for (auto& _Obj : m_Obj_List)
	{
		for (auto& _Line : m_Line_List)
		{
			LINEPOINT _Line_Left = static_cast<CLine*>(_Line)->Get_LinePoint().tLeft;
			LINEPOINT _Line_Right = static_cast<CLine*>(_Line)->Get_LinePoint().tRight;
			
			if (_Obj->Get_Info().fX > _Line_Left.fX && _Obj->Get_Info().fX < _Line_Right.fX)
			{
				if (_Obj->Get_Info().fX > _Line_Left.fX && _Obj->Get_Info().fX < _Line_Right.fX)
				{
					float _fY = ((_Line_Right.fY - _Line_Left.fY) / (_Line_Right.fX - _Line_Left.fX)) * (_Obj->Get_Info().fX - _Line_Left.fX) + _Line_Left.fY;
					_Obj->Set_Pos(_Obj->Get_Info().fX, _fY - (_Obj->Get_Info().fCY*0.5f));
					_Obj->Set_Air(true);
				}
			}
		}
		if (_Obj->Get_Air())
		{
			continue;
		}
		_Obj->Set_Air(false);
	}
}

//void CCollision::Collision_Player_Line(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Line_List, POINT& _Player_RightLeg, POINT& _Player_LeftLeg)
//{
//	for (auto& _Obj : m_Obj_List)
//	{
//		for (auto& _Line : m_Line_List)
//		{
//			LINEPOINT _Line_Left = static_cast<CLine*>(_Line)->Get_LinePoint().tLeft;
//			LINEPOINT _Line_Right = static_cast<CLine*>(_Line)->Get_LinePoint().tRight;
//
//			if (_Player_RightLeg.x > _Line_Left.fX && _Player_RightLeg.x < _Line_Right.fX)
//			{
//				if (_Obj->Get_Info().fX > _Line_Left.fX && _Obj->Get_Info().fX < _Line_Right.fX)
//				{
//					float _fY = ((_Line_Right.fY - _Line_Left.fY) / (_Line_Right.fX - _Line_Left.fX)) * (_Player_RightLeg.x - _Line_Left.fX) + _Line_Left.fY;
//					if (!(static_cast<CPlayer*>(m_Obj_List.front())->Get_Jumping()))
//					{						
//						_Player_RightLeg.y = (LONG)_fY;
//						_Player_LeftLeg.y = (LONG)_fY;
//						//static_cast<CPlayer*>(m_Obj_List.front())->Set_Body();
//					}
//					_Obj->Set_Air(true);
//				}
//			}
//		}
//		if (_Obj->Get_Air())
//		{
//			continue;
//		}
//		_Obj->Set_Air(false);
//	}
//}

bool CCollision::Collision_Player_Line(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Line_List, POINT& _Player_RightLeg, POINT& _Player_LeftLeg)
{
	float _fY = 0.f;
	for (auto& _Obj : m_Obj_List)
	{
		for (auto& _Line : m_Line_List)
		{
			LINEPOINT _Line_Left = static_cast<CLine*>(_Line)->Get_LinePoint().tLeft;
			LINEPOINT _Line_Right = static_cast<CLine*>(_Line)->Get_LinePoint().tRight;
			
			if (m_Line_List.empty())
			{
				return false;
			}			

			CObj*		pTarget = nullptr;

			if (_Player_RightLeg.x > _Line_Left.fX && _Player_RightLeg.x < _Line_Right.fX)
			{
				pTarget = _Line;
			}

			if (!pTarget)
			{
				return false;
			}
				
			_fY = ((_Line_Right.fY - _Line_Left.fY) / (_Line_Right.fX - _Line_Left.fX)) * (_Player_RightLeg.x - _Line_Left.fX) + _Line_Left.fY;
			
			if (!(static_cast<CPlayer*>(_Obj)->Get_Jumping()))
			{
				_Player_RightLeg.y = (LONG)_fY;
				_Player_LeftLeg.y = (LONG)_fY;
				//_Obj->Set_Pos(_Obj->Get_Info().fX, _fY - (_Obj->Get_Info().fCY * 0.5f));
			}
			return true;
		}
	}
}



void Collision_Player_Block(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Block_List)
{
	//float fWidth = m_Obj_List
	for (auto& _player : m_Obj_List)
	{
		RECT _player_rc = _player->Get_Rect();
		INFO _player_info = _player->Get_Info();
		for (auto& _block : m_Block_List)
		{
			float fDistanceX = abs(_player_info.fX + _block->Get_Info().fX);
			float fDistanceY = abs(_player_info.fY + _block->Get_Info().fY);

			float fWidth = _player_info.fX + _player_info.fCX * 0.5f + _block->Get_Info().fX + _block->Get_Info().fCX;
			float fHeight = _player_info.fY + _player_info.fCY * 0.5f + _block->Get_Info().fY + _block->Get_Info().fCY;

			if (fDistanceX < fWidth || fDistanceY < fHeight)
			{
				_block->Set_Pos(fWidth- fDistanceX, fHeight- fDistanceY);
			}
		}
	}
}