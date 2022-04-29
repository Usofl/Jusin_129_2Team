#pragma once
#include "Being.h"
class CPlayer :
	public CBeing
{
public:
	CPlayer();
	virtual ~CPlayer();

	// CBeing을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int& Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	void Key_Input(void);
	const bool& Front_Leg(void) { return m_tLeft_Leg.x > m_tRight_Leg.x; }

private:
	bool m_bChange;
	bool m_bJump;

	int   m_iReverse;
	float m_fJumpTime;
	float m_fJumpPower;
	float m_fJumpAngle;

	POINT m_tLeft_Leg;
	POINT m_tRight_Leg;
};

