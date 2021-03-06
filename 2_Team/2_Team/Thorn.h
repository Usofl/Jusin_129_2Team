#pragma once
#include "NotBeing.h"
class CThorn :
	public CNotBeing
{
public:
	CThorn();
	virtual ~CThorn();

	// CNotBeing을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int & Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	bool m_bBoss;
};

