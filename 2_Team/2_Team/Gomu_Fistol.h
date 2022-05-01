#pragma once
#include "Being.h"
class CGomu_Fistol :
	public CBeing
{
public:
	CGomu_Fistol();
	CGomu_Fistol(const POINT& _tPoint, const int& _iReverse);
	virtual ~CGomu_Fistol();

	// CBeing��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual const int & Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	unsigned int m_uiArea;
	std::stack<float> m_AreaStack;
};

