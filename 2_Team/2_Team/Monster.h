#pragma once
#include "Being.h"

class CMonster :
	public CBeing
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize(void) PURE;
	virtual const int&  Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release(void) PURE;
};

