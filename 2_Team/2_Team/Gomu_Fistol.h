#pragma once
#include "Being.h"
class CGomu_Fistol :
	public CBeing
{
public:
	CGomu_Fistol();
	CGomu_Fistol(const INFO& _tInfo);
	virtual ~CGomu_Fistol();

	// CBeing을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int & Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
};

