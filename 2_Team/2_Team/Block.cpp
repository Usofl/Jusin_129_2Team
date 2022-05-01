#include "stdafx.h"
#include "Block.h"
#include "Collision.h"
#include "ObjMgr.h"
#include "LineFactory.h"


CBlock::CBlock()
	: m_fJumpTime(0.f)
	, m_fJumpPower(20)
	, m_bBlockCol(false)
	, m_pBlock_Up(nullptr)
	, m_pBlock_Right(nullptr)
	, m_pBlock_Left(nullptr)
{
}


CBlock::~CBlock()
{
}

void CBlock::Initialize(void)
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;
	m_bAir = false;
	
	m_Block_RoofLine = CLineFactory::Create_Line(m_tBlock_Roof);
	m_tBlock_Roof = { {m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.5f - 4.f },{ m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.5f - 4.f } };
	OBJMGR->Add_Notbeing(NOTBEING_LINE, *m_Block_RoofLine);
	static_cast<CLine*>(m_Block_RoofLine)->Set_Render(false);

	m_Block_RightLine = CLineFactory::Create_Line(m_tBlock_Right);
	m_tBlock_Right = { { m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.5f },{ m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY + m_tInfo.fCY * 0.5f} };
	OBJMGR->Add_Notbeing(NOTBEING_WALL, *m_Block_RightLine);
	static_cast<CLine*>(m_Block_RightLine)->Set_Render(false);

	m_Block_LeftLine = CLineFactory::Create_Line(m_tBlock_Left);
	m_tBlock_Left = { { m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.5f },{ m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY + m_tInfo.fCY * 0.5f } };
	OBJMGR->Add_Notbeing(NOTBEING_WALL, *m_Block_LeftLine);
	static_cast<CLine*>(m_Block_LeftLine)->Set_Render(false);
}

const int& CBlock::Update(void)
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	float _fY(0.f); // 라인이 있는 좌표
	float _fCollisionY(0.f);
	//안착할 라인이 있다 없다.
	bool bLineCol = CCollision::Collision_Line(*this, CObjMgr::Get_Instance()->Get_NotBeing_list(NOTBEING_LINE), _fY);
	
	if (m_bBlockCol)
	{
		_fY = _fCollisionY;
	}

	_fY -= m_tInfo.fCY * 0.5f;

	if (m_bAir)
	{
		m_tInfo.fY += GRAVITY * m_fJumpTime * m_fJumpTime * 0.5f * 0.1f;
		m_fJumpTime += 0.2f;
		if (bLineCol && m_tInfo.fY - 10.f > _fY)
		{
			m_bAir = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = _fY;
		}
	}
	else if(m_tInfo.fY < _fY && !m_bBlockCol)
	{
		m_bAir = true;
	}

	m_tBlock_Roof = { { m_tInfo.fX - m_tInfo.fCX * 0.5f-0.3f, m_tInfo.fY - m_tInfo.fCY * 0.5f - 3.f },{ m_tInfo.fX + m_tInfo.fCX * 0.5f + 0.3f, m_tInfo.fY - m_tInfo.fCY * 0.5f - 3.f } };
	static_cast<CLine*>(m_Block_RoofLine)->Set_Line(m_tBlock_Roof);

	m_tBlock_Right = { { m_tInfo.fX - m_tInfo.fCX * 0.5f + 15.f, m_tInfo.fY - m_tInfo.fCY * 0.5f },{ m_tInfo.fX - m_tInfo.fCX * 0.5f + 15.f, m_tInfo.fY + m_tInfo.fCY * 0.5f } };
	static_cast<CLine*>(m_Block_RightLine)->Set_Line(m_tBlock_Right);

	m_tBlock_Left = { { m_tInfo.fX + m_tInfo.fCX * 0.5f - 15.f, m_tInfo.fY - m_tInfo.fCY * 0.5f },{ m_tInfo.fX + m_tInfo.fCX * 0.5f - 15.f, m_tInfo.fY + m_tInfo.fCY * 0.5f } };
	static_cast<CLine*>(m_Block_LeftLine)->Set_Line(m_tBlock_Left);

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBlock::Late_Update(void)
{
	m_bBlockCol = false;
}

void CBlock::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
	MoveToEx(_hDC, m_tRect.left + iScrollX, m_tRect.top, nullptr);
	LineTo(_hDC, m_tRect.right + iScrollX, m_tRect.bottom);

	MoveToEx(_hDC, m_tRect.left + iScrollX, m_tRect.bottom, nullptr);
	LineTo(_hDC, m_tRect.right + iScrollX, m_tRect.top);
}

void CBlock::Release(void)
{
}
