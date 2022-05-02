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
	void	Jumping(void);		// 점프함수
	void	Shoot_Bullet(void);	// 총쏘는함수
	void	Jump_Crash(void);


private:
	bool					m_bJump;		// 점프 상태 확인
	float					m_fJumpPower;	// 점프 힘
	float					m_fJumpTime;	// 점프 중 진행 시간

	float					m_fShootPower;	// 총 쏘는 힘
	float					m_fShootTime;	// 총알 채공 시간
	float					m_fShootAngle;
	
	float					m_fKoopa_speed;
	float					m_fPlayer_X;
	bool					m_bMove_X;

	bool					m_bMonsterCol;
	
	DWORD					m_dwCount;
	DWORD					m_dwJumpTiming;
};

