#pragma once
#include "NotBeing.h"
class CLine final :
	public CNotBeing
{
public:
	CLine();
	virtual ~CLine();

	// CNotBeing��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual const int & Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
};