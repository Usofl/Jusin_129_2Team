#pragma once
#include "NotBeing.h"

class CBlock final
	: public CNotBeing
{
public:
	CBlock();
	virtual ~CBlock();

	// CNotBeing을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int & Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

	inline void Set_BlockCol() { m_bBlockCol = true; }

	inline void Set_Block_Up	(CObj*& _pBlock)	{ m_pBlock_Up = _pBlock;}
	inline void Set_Block_Right(CObj*& _pBlock)	{ m_pBlock_Right = _pBlock;}
	inline void Set_Block_Left	(CObj*& _pBlock)	{ m_pBlock_Left = _pBlock;}

	inline const CObj* Get_Block_Up()			{ return m_pBlock_Up; }
	inline const CObj* Get_Block_Right()		{ return m_pBlock_Right; }
	inline const CObj* Get_Block_Left()		{ return m_pBlock_Left; }

	inline void Set_NoBlock()
	{
		m_pBlock_Up = nullptr;
		m_pBlock_Right = nullptr;
		m_pBlock_Left = nullptr;
	}

private:
	float	m_fJumpPower;
	float	m_fJumpTime;
	bool	m_bBlockCol;

	LINE m_tBlock_Roof;
	CObj* m_Block_RoofLine;	

	LINE m_tBlock_Right;
	CObj* m_Block_RightLine;

	LINE m_tBlock_Left;
	CObj* m_Block_LeftLine;

	CObj* m_pBlock_Up;
	CObj* m_pBlock_Right;
	CObj* m_pBlock_Left;
};