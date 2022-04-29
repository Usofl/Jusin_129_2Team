#pragma once
#include "Being.h"
#include "Monster.h"

class CWarrior :
	public CMonster
{
public:
	CWarrior();
	virtual ~CWarrior();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	POINT		m_tSword;

	float		m_fDiagonal;

	bool		m_bTurn;
};

