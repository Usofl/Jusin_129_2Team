#pragma once
#include "Obj.h"
class CBeing :
	public CObj
{
public:
	CBeing();
	virtual ~CBeing();

	

	// CObj��(��) ���� ��ӵ�
	virtual void			Initialize		(void) override;
	virtual const int&		Update			(void) override;
	virtual void			Late_Update		(void) override;
	virtual void			Render			(void) override;
	virtual void			Release			(void) override;

};

