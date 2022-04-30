#pragma once
#include "Being.h"
class CKoopa_Bullet :
	public CBeing
{
public:
	CKoopa_Bullet();
	virtual ~CKoopa_Bullet();

public:
	virtual void Initialize(void) override;
	virtual const int&  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	float					m_fShootPower;	// ÃÑ ½î´Â Èû
	float					m_fShootTime;	// ÃÑ¾Ë Ã¤°ø ½Ã°£
	float					m_fShootAngle;
};

