#pragma once
#include "Being.h"
class CBullet :
	public CBeing
{
public:
	CBullet();
	virtual ~CBullet();

public:


public:
	virtual void Initialize(void) override;
	virtual const int&  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

};

