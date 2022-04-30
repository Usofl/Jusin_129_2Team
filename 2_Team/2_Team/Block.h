#pragma once
#include "NotBeing.h"

class CBlock final
	: public CNotBeing
{
public:
	CBlock();
	virtual ~CBlock();

	// CNotBeing��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual const int & Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	float m_fJumpPower;
	float m_fJumpTime;
};
