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
				if (pTarget && _fY >= _fLine_Y)
				{
					pTarget = line;
					_fY = _fLine_Y;
				}
				else if(nullptr == pTarget)
				{
					pTarget = line;
					_fY = _fLine_Y;
				}
			}
		}
	}

	if (nullptr == pTarget)
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
			float fWidth = abs(_player_info.fX - _block->Get_Info().fX);
			float fHeight = abs(_player_info.fY - _block->Get_Info().fY);

			float fCX = (_player_info.fCX + _block->Get_Info().fCX) * 0.5f;
			float fCY = (_player_info.fCX + _block->Get_Info().fCX) * 0.5f;

			if (fCX > fWidth && fCY > fHeight)
			{
				float _fChangeX(fCX - fWidth);
				float _fChangeY(fCY - fHeight);
				if (_fChangeX > _fChangeY)
				{
					////상충돌
					//if (_player_info.fY > _block->Get_Info().fY)
					//{
					//	_block->Set_Pos(_block->Get_Info().fX, _block->Get_Info().fY + _fChangeY);
					//}
					//else//하충돌
					//{
					//	_block->Set_Pos(_block->Get_Info().fX, _block->Get_Info().fY - _fChangeY);
					//}
					if (_player_info.fY > _block->Get_Info().fY)
					{

					}
					else//하충돌
					{
						static_cast<CPlayer*>(_player)->Set_Jump();
					}
				}
				else
				{
					//우
					if (_player_info.fX > _block->Get_Info().fX)
					{
					
						if (static_cast<CPlayer*>(_player)->Get_Pool())
						{
							//float _fMoveX = 플레이어 좌표에서 블럭좌표 빼고 간격만큼 빼서 움직인다.
							_block->Set_Pos(_block->Get_Info().fX + 1.f, _block->Get_Info().fY);
							if (abs(_player_info.fX - _block->Get_Info().fX) < fCX)
								_block->Set_Pos(_player_info.fX - fCX + 10.f, _block->Get_Info().fY);
						}
						else
						{
							_block->Set_Pos(_block->Get_Info().fX - _fChangeX, _block->Get_Info().fY);
						}
						
					}
					else//좌충돌
					{
						if (static_cast<CPlayer*>(_player)->Get_Pool())
						{
							_block->Set_Pos(_block->Get_Info().fX - 1.f, _block->Get_Info().fY);
							if (abs(_player_info.fX - _block->Get_Info().fX) < fCX)
								_block->Set_Pos(_player_info.fX + fCX - 10.f, _block->Get_Info().fY);
						}
						else
						{
							_block->Set_Pos(_block->Get_Info().fX + _fChangeX, _block->Get_Info().fY);
						}
					}
				}
			}
		}
	}
}

bool CCollision::Collision_Block_Block(CObj* _Obj, std::list<CObj*>& m_Block_List, float& _fCollisionY)
{
	
	for (auto& _block : m_Block_List)
	{
		if (_block == _Obj)
		{
			continue;
		}

		float fWidth = abs(_Obj->Get_Info().fX - _block->Get_Info().fX);
		float fHeight = abs(_Obj->Get_Info().fY - _block->Get_Info().fY);

		float fCX = (_Obj->Get_Info().fCX + _block->Get_Info().fCX) * 0.5f;
		float fCY = (_Obj->Get_Info().fCX + _block->Get_Info().fCX) * 0.5f;

		if (fCX >= fWidth && fCY >= fHeight)
		{
			float _fChangeX(fCX - fWidth);
			float _fChangeY(fCY - fHeight);
			if (_fChangeX > _fChangeY)
			{
				//상충돌
				if (_Obj->Get_Info().fY > _block->Get_Info().fY)
				{
					_fCollisionY = _block->Get_Info().fY - _block->Get_Info().fCY * 0.5f;
					return true;
				}

				
			}
			else
			{
				//우
				if (_Obj->Get_Info().fX > _block->Get_Info().fX)
				{
					_Obj->Set_Pos(_block->Get_Info().fX + fCX + 1, _Obj->Get_Info().fY);
				}
				else//좌충돌
				{
					_Obj->Set_Pos(_block->Get_Info().fX - fCX - 1, _Obj->Get_Info().fY);
				}
			}

			return false;
		}
		else
		{
			return false;
		}
	}
}