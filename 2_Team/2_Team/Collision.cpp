#include "stdafx.h"
#include "Collision.h"
#include "Line.h"


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

void CCollision::Collision_Player_Line(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Line_List, POINT& _Player_RightLeg, POINT& _Player_LeftLeg)
{
	for (auto& _Obj : m_Obj_List)
	{
		for (auto& _Line : m_Line_List)
		{
			LINEPOINT _Line_Left = static_cast<CLine*>(_Line)->Get_LinePoint().tLeft;
			LINEPOINT _Line_Right = static_cast<CLine*>(_Line)->Get_LinePoint().tRight;

			if (_Player_RightLeg.x > _Line_Left.fX && _Player_RightLeg.x < _Line_Right.fX)
			{
				if (_Obj->Get_Info().fX > _Line_Left.fX && _Obj->Get_Info().fX < _Line_Right.fX)
				{
					float _fY = ((_Line_Right.fY - _Line_Left.fY) / (_Line_Right.fX - _Line_Left.fX)) * (_Player_RightLeg.x - _Line_Left.fX) + _Line_Left.fY;
					//_Obj->Set_Pos(_Obj->Get_Info().fX, _fY - (_Obj->Get_Info().fCY*0.5f));
					_Player_RightLeg.y = (LONG)_fY;
					_Player_LeftLeg.y = (LONG)_fY;
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