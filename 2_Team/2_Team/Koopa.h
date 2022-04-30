#pragma once
#include "Being.h"
#include "Monster.h"
#include "Koopa_Bullet.h"


class CKoopa :
	public CMonster
{
public:
	CKoopa();
	virtual ~CKoopa();

public:
	virtual void Initialize(void) override;
	virtual const int&  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	void		Jumping();

private:
	bool					m_bJump;		// ���� ���� Ȯ��
	float					m_fJumpPower;	// ���� ��
	float					m_fJumpTime;	// ���� �� ���� �ð�

	float					m_fShootPower;	// �� ��� ��
	float					m_fShootTime;	// �Ѿ� ä�� �ð�
	float					m_fShootAngle;
};

