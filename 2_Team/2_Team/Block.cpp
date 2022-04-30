#include "stdafx.h"
#include "Block.h"
#include "Collision.h"
#include "ObjMgr.h"


CBlock::CBlock()
	: m_fJumpTime(0.f)
	, m_fJumpPower(20)
{
}


CBlock::~CBlock()
{
}

void CBlock::Initialize(void)
{
	m_tInfo.fCX = 40;
	m_tInfo.fCY = 40;
	m_bAir = false;
}

const int& CBlock::Update(void)
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	float _fY; // 라인이 있는 좌표
	bool bLineCol = CCollision::Collision_Line(*this, CObjMgr::Get_Instance()->Get_NotBeing_list(NOTBEING_LINE), _fY);
	//안착할 라인이 있다 없다.

	if (m_bAir)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.2f;
		if (bLineCol && m_tInfo.fY > _fY)
		{
			m_bAir = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = _fY;
		}
	}
	else if(m_tInfo.fY < _fY)
	{
		m_bAir = true;
	}

	
	

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBlock::Late_Update(void)
{

}

void CBlock::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBlock::Release(void)
{
}
