#pragma once
#include "Being.h"
#include "Monster.h"
#include "Koopa_Bullet.h"
#include "Collision.h"
#include "ObjMgr.h"
#include "Koopa_Crash.h"




class CKoopa :
	public CMonster
{
public:
	CKoopa();
	virtual ~CKoopa();

public:
	virtual void Initialize(void) override;
	virtual const int& Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

public:
	void	Jumping(void);		// �����Լ�
	void	Shoot_Bullet(void);	// �ѽ���Լ�
	void	Jump_Crash(void);


private:
	bool					m_bJump;		// ���� ���� Ȯ��
	float					m_fJumpPower;	// ���� ��
	float					m_fJumpTime;	// ���� �� ���� �ð�

	float					m_fShootPower;	// �� ��� ��
	float					m_fShootTime;	// �Ѿ� ä�� �ð�
	float					m_fShootAngle;
	
	float					m_fKoopa_speed;
	float					m_fPlayer_X;
	bool					m_bMove_X;

	bool					m_bMonsterCol;
	
	DWORD					m_dwCount;
	DWORD					m_dwJumpTiming;
};

