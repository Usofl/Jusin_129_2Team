#pragma once
#include "Being.h"
#include "ObjMgr.h"

class CCounter_Bullet :
	public CBeing
{
public:
	CCounter_Bullet();
	CCounter_Bullet(const INFO& _tInfo);
	virtual ~CCounter_Bullet();

	// CBeing을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int & Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	float m_fAngle;
	float m_fCounter_Time;
};

