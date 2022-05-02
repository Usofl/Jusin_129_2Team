#include "stdafx.h"
#include "M_Cloud.h"
#include "MonsterFactory.h"

CM_Cloud::CM_Cloud()
	: m_dwCount(GetTickCount())	// 멤버 이니셜라이즈 == iCount 변수에 GetTickCount(윈도우 실행후부터의 시간) 대입 
{
}

CM_Cloud::~CM_Cloud()
{
	Release();
}

void CM_Cloud::Initialize(void)
{
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 50.f;

	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	
	m_fSpeed = 5.f;

	m_iHp = 5;

	m_iAtt = 1;


}

const int& CM_Cloud::Update(void)
{

	if (m_iHp <= 0)
	{
		return OBJ_DEAD;
	}

	Shoot_Bullet();

	m_tInfo.fX += m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CM_Cloud::Late_Update(void)
{
	if (0 >= m_tRect.left || 5000 <= m_tRect.right)
	{
		m_fSpeed *= -1.f;
	}

	
}

void CM_Cloud::Render(HDC _hDC)
{
	int		iScrollX = (int)SCROLLMGR->Get_ScrollX();
	int		iScrollY = (int)SCROLLMGR->Get_ScrollY();

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top - 20 + iScrollY, m_tRect.right + iScrollX, m_tRect.top - 10 + iScrollY);

	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	OldBrush = (HBRUSH)SelectObject(_hDC, MyBrush);

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top - 20 + iScrollY, m_tRect.left + (int)(m_tInfo.fCX * m_iHp / 5.f) + iScrollX, m_tRect.top - 10 + iScrollY);

	SelectObject(_hDC, OldBrush);
	DeleteObject(MyBrush);

	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

}

void CM_Cloud::Release(void)
{
}

void CM_Cloud::Shoot_Bullet(void)
{
	// 플레이어의 x 좌표값을 가지고 왔음 => CObjMgr*타입의 instance 를 반환 후에 움직이는 리스트(플레이어)의 첫번째 를 호출 후에 정보값x값을 대입
	float fPlayer_X = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fX;

	if (m_dwCount + 100 < GetTickCount())	// dwCount+3000(대략 3초) < GetTickCount 커질때 (GetTickCount 1 /1000 = 1초)
	{
		if (fabs(m_tInfo.fX - fPlayer_X) < 30.f)	// 절댓값 구름몬스터의 x 값과 플레이어 x 값을 뺀 값이 < 30.f 보다 작을때, 같으면 총쏘는시간이 대부분안맞음
		{
			// CObjMgr*타입의 instance 를 반환 후에 Add_Being함수 호출(몬스터 총알, 총알생성(정보값)
			OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Bullet(m_tInfo.fX, m_tInfo.fY));
		}
		m_dwCount = GetTickCount(); // 다시 대입해서 1초로 초기화
	}
}


