#include "stdafx.h"
#include "Block.h"
#include "Collision.h"
#include "ObjMgr.h"


CBlock::CBlock()
{
}


CBlock::~CBlock()
{
}

void CBlock::Initialize(void)
{
}

const int& CBlock::Update(void)
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.

	
	//CCollision::Collision_Line(*this, CObjMgr::Get_Instance()->);
	
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
