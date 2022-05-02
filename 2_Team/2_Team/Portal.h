#pragma once
#include "NotBeing.h"
class CPortal final :
	public CNotBeing
{
public:
	CPortal();
	CPortal(float _fX, float _fY) : m_tPortal({ _fX,_fY }) {}
	virtual ~CPortal();

	// CNotBeing을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int & Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

	const LINEPOINT& Get_Portal() {	return m_tPortal; }
	

private:
	LINEPOINT m_tPortal;
};

