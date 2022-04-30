#pragma once
#include "Being.h"
#include "Obj.h"
#include "Monster.h"
#include "M_Bullet.h"

class CCloud :
	public CMonster
{
public:
	CCloud();
	virtual ~CCloud();

public:
	virtual void Initialize(void) override;
	virtual const int&  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

};



