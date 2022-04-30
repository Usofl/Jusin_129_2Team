#include "stdafx.h"
#include "Cloud.h"
#include "ObjMgr.h"
#include "MonsterFactory.h"
#include "M_Bullet.h"

CCloud::CCloud()
{
}


CCloud::~CCloud()
{
	Release();
}

void CCloud::Initialize(void)
{
	m_tInfo.fX = 250.f;
	m_tInfo.fY = 400.f;

	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fAngle = 45.f;
		
	m_fSpeed = 3.f;

	m_iHp = 5;

	m_iAtt = 1;
}

const int& CCloud::Update(void)
{
	if (m_iHp <= 0)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState('D'))
	{
		CObjMgr::Get_Instance()->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Bullet(m_tInfo.fX, m_tInfo.fY));
		
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCloud::Late_Update(void)
{
	if (0 >= m_tRect.left || WINCX <= m_tRect.right)
	{
		m_fSpeed *= -1.f;
	}
}

void CCloud::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}
void CCloud::Release(void)
{
}
