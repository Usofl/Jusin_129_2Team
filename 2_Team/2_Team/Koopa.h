#pragma once
#include "Being.h"
#include "Monster.h"


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
};

