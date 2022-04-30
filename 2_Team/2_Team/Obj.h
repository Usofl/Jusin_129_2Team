#pragma once
#include "Include.h"
#include "ScrollMgr.h"

class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void		Initialize	(void)		PURE;
	virtual const int&	Update		(void)		PURE;
	virtual void		Late_Update	(void)		PURE;
	virtual void		Render		(HDC _hDC)	PURE;
	virtual void		Release		(void)		PURE;

	void				Update_Rect	(void);

public:
	inline	void		Set_Hp		(const int& _iHp)		{ m_iHp = _iHp;	}
	inline	void		Set_Att		(const int& _iAtt)		{ m_iAtt = _iAtt; }
	inline	void		Set_Speed	(const float& _fSpeed)	{ m_fSpeed = _fSpeed; }
	inline	void		Set_Angle	(const float& _fAngle)	{ m_fAngle = _fAngle; }
	inline	void		Set_Air		(const bool& _bAir)		{ m_bAir = _bAir; }

public:
	inline const int&	Get_Hp		(void)	const				{ return m_iHp; }
	inline const int&	Get_Att		(void)	const				{ return m_iAtt; }
	inline const float& Get_Speed	(void)	const 				{ return m_fSpeed; }
	inline const float& Get_Angle	(void)	const				{ return m_fAngle; }
	inline const bool&	Get_Air		(void)	const				{ return m_bAir; }

public:
	inline const INFO&	Get_Info	(void)	const				{ return m_tInfo; }
	inline const RECT&	Get_Rect	(void)	const				{ return m_tRect; }

	inline void Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }

protected:
	INFO m_tInfo;
	RECT m_tRect;

	int m_iHp;
	int m_iAtt;
	float m_fSpeed;
	float m_fAngle;

	bool m_bAir;
};

