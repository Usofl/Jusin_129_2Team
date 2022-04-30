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
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.

	float _fY(0.f); // ������ �ִ� ��ǥ
	bool bLineCol = CCollision::Collision_Line(*this, CObjMgr::Get_Instance()->Get_NotBeing_list(NOTBEING_LINE), _fY);
	//������ ������ �ִ� ����.
	_fY -= m_tInfo.fCY * 0.5f;
	if (m_bAir)
	{
		m_tInfo.fY += GRAVITY * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.2f;
		if (bLineCol && m_tInfo.fY - m_tInfo.fCY * 0.5f >= _fY)
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
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CBlock::Release(void)
{
}
