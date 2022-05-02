#pragma once
#include "Being.h"
#include "ObjMgr.h"
class CKoopa_Crash :
	public CBeing
{
public:
	CKoopa_Crash();
	CKoopa_Crash(float _fAngle) { m_fAngle = _fAngle; }
	virtual ~CKoopa_Crash();

public:
	virtual void Initialize(void) override;
	virtual const int&  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	float					m_fShootPower;	// �� ��� ��
	float					m_fShootTime;	// �Ѿ� ä�� �ð�
	float					m_fShootAngle;

};

