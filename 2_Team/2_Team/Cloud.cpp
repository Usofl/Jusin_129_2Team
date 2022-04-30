#include "stdafx.h"
#include "Cloud.h"
#include "ObjMgr.h"
#include "MonsterFactory.h"
#include "M_Bullet.h"

CCloud::CCloud()
	: m_dwCount(GetTickCount())	// 멤버 이니셜라이즈 == iCount 변수에 GetTickCount(윈도우 실행후부터의 시간) 대입 
{
}

CCloud::~CCloud()
{
	Release();
}

void CCloud::Initialize(void)
{
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 50.f;

	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	
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

	float fPlayer_X = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fX;

	m_tInfo.fX += m_fSpeed;

	if (m_dwCount + 100 < GetTickCount())	// dwCount+3000(대략 3초) < GetTickCount 커질때 (GetTickCount 1 /1000 = 1초)
	{
		if (fabs(m_tInfo.fX - fPlayer_X) < 30.f)
		{
			OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Bullet(m_tInfo.fX, m_tInfo.fY));
		}
		m_dwCount = GetTickCount(); // 다시 대입해서 1초로 초기화
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


