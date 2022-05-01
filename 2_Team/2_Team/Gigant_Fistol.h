#pragma once
#include "Being.h"
class CGigant_Fistol :
	public CBeing
{
public:
	CGigant_Fistol();
	CGigant_Fistol(const POINT& _tPoint, const int& _iReverse, const unsigned int& _iSize);
	~CGigant_Fistol();

	// CBeing을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int & Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	unsigned int m_uiArea;
	std::stack<float> m_AreaStack;
};

