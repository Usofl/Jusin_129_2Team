#include "stdafx.h"
#include "M_Cloud.h"
#include "MonsterFactory.h"

CM_Cloud::CM_Cloud()
	: m_dwCount(GetTickCount())	// ��� �̴ϼȶ����� == iCount ������ GetTickCount(������ �����ĺ����� �ð�) ���� 
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
	// �÷��̾��� x ��ǥ���� ������ ���� => CObjMgr*Ÿ���� instance �� ��ȯ �Ŀ� �����̴� ����Ʈ(�÷��̾�)�� ù��° �� ȣ�� �Ŀ� ������x���� ����
	float fPlayer_X = OBJMGR->Get_Being_list(BEING_PLAYER).front()->Get_Info().fX;

	if (m_dwCount + 100 < GetTickCount())	// dwCount+3000(�뷫 3��) < GetTickCount Ŀ���� (GetTickCount 1 /1000 = 1��)
	{
		if (fabs(m_tInfo.fX - fPlayer_X) < 30.f)	// ���� ���������� x ���� �÷��̾� x ���� �� ���� < 30.f ���� ������, ������ �ѽ�½ð��� ��κоȸ���
		{
			// CObjMgr*Ÿ���� instance �� ��ȯ �Ŀ� Add_Being�Լ� ȣ��(���� �Ѿ�, �Ѿ˻���(������)
			OBJMGR->Add_Being(BEING_MONSTERBULLET, *CMonsterFactory::Create_Bullet(m_tInfo.fX, m_tInfo.fY));
		}
		m_dwCount = GetTickCount(); // �ٽ� �����ؼ� 1�ʷ� �ʱ�ȭ
	}
}


