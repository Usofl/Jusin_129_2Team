#pragma once
#include "Being.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "Collision.h"

class CWarrior :
	public CMonster
{
public:
	CWarrior();
	virtual ~CWarrior();

public:
	virtual void Initialize(void) override;
	virtual const int&  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	POINT		m_tSword;

	// 대각선? 소드길이
	float		m_fDiagonal;

	// 반전, 몹 뒤집기
	int			m_iTurn;

	RECT rc{ 250, 280 , 350, 320 };

private:
	bool					m_bJump;		
	float					m_fJumpPower;	
	float					m_fJumpTime;	
};

