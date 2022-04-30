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

bool CCollision::Collision_Line(const CObj& _Obj, const std::list<CObj*>& m_Line_List, float& _fY)
{
	LINEPOINT _Line_Left{0,0};
	LINEPOINT _Line_Right{0,0};
	float _fLine_Y;

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

		if (_Obj.Get_Info().fX > _Line_Left.fX && _Obj.Get_Info().fX < _Line_Right.fX)
		{
			_fLine_Y = ((_Line_Right.fY - _Line_Left.fY) / (_Line_Right.fX - _Line_Left.fX)) 
						* (_Obj.Get_Info().fX - _Line_Left.fX)	+ _Line_Left.fY;

			if (_Obj.Get_Info().fY > _fLine_Y)
			{
				if (pTarget)
				{
					if (pTarget->Get_Info().fY < _Line->Get_Info().fY)
					{
						pTarget = line;
						_fY = _fLine_Y;
					}
				}
				else
				{
					pTarget = line;
					_fY = _fLine_Y;
				}
			}
		}
	}

	if (!pTarget)
	{
		return false;
	}

	return true;
}

void CCollision::Collision_Player_Block(std::list<CObj*>& m_Obj_List, std::list<CObj*>& m_Block_List)
{
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

			if (fDistanceX < fWidth && fDistanceY < fHeight)
			{
				if (fWidth - fDistanceX > fHeight - fDistanceY)
				{
					//상충돌
					if (_player_info.fY > _block->Get_Info().fY)
					{
						_block->Set_Pos(_block->Get_Info().fX, fHeight - fDistanceY);
					}
					else//하충돌
					{
						_block->Set_Pos(_block->Get_Info().fX, (-1)*(fHeight - fDistanceY));
					}
				}
				else
				{
					//우
					if (_player_info.fX > _block->Get_Info().fX)
					{
						_block->Set_Pos((-1)*(fWidth - fDistanceX), _block->Get_Info().fX);
					}
					else//좌충돌
					{
						_block->Set_Pos((fWidth - fDistanceX), _block->Get_Info().fY);
					}
				}
			}
		}
	}
}