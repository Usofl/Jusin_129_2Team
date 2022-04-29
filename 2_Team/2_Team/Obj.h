#pragma once
#include "Include.h"

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

public:
	inline const int&	Get_Hp		(void)					{ return m_iHp; }
	inline const int&	Get_Att		(void)					{ return m_iAtt; }
	inline const float& Get_Speed	(void)					{ return m_fSpeed; }
	inline const float& Get_Angle	(void)					{ return m_fAngle; }

public:
	inline const INFO&	Get_Info	(void)					{ return m_tInfo; }
	inline const RECT&	Get_Rect	(void)					{ return m_tRect; }

protected:
	INFO m_tInfo;
	RECT m_tRect;

	int m_iHp;
	int m_iAtt;
	float m_fSpeed;
	float m_fAngle;
};

