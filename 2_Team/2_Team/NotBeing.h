#pragma once
#include "Obj.h"

class CNotBeing
	: public CObj
{
public:
	CNotBeing();
	virtual ~CNotBeing();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) PURE;
	virtual int Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(void) PURE;
	virtual void Release(void) PURE;
};

