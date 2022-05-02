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

	inline POINT& Get_Left_Leg(void) { return m_tLeft_Leg; }
	inline POINT& Get_Right_Leg(void) { return m_tRight_Leg; }
	inline const bool& Get_Jumping(void) { return m_bJump; }
	inline const bool& Get_Balloon(void) { return m_bBalloon; }

	void Jumping(void);
	void SetBody(void);
	void OffSet(void);

	inline const bool& Get_Pool() { return m_bPool;}
	inline const int& Get_Coin() { return m_iCoin; }
	inline const int& Get_Life() { return m_iLife; }
	inline const int& Get_Mp() { return m_iMp; }

	void PlayerCoinColli(void);
	void Put_ItemType(const int& _Itemtype);
	void DOWN_Clim_Ladder(void);
	void UP_Clim_Ladder(void);

	inline void Set_Jump() { m_bJump = false; }
	inline void Set_Right_Move(const bool& _bMove) { m_bRight_Move = _bMove; }
	inline void Set_Left_Move(const bool& _bMove) { m_bLeft_Move = _bMove; }
	inline void Set_Clim(const bool& _bClim) { m_bClim = _bClim; }

	inline	void		Set_Hp(const int& _iHp) 
	{ 
		if (m_dwAttacked + 3000 < GetTickCount())
		{
			m_iHp = _iHp;
			m_dwAttacked = GetTickCount();
		}
	}

private:
	void Key_Input(void);
	const bool& Front_Leg(void) { return m_tLeft_Leg.x > m_tRight_Leg.x; }

private:
	bool m_bChange;
	bool m_bJump;
	bool m_bPool;
	bool m_bBalloon;
	bool m_bCharging;
	bool m_bClim;

	int   m_iCoin;
	int   m_iLife;
	int   m_iMp;
	int   m_iItemtype;
	float m_fJumpTime;
	float m_fJumpPower;
	float m_fJumpAngle;

	float m_fCharging;

	bool m_bRight_Move;
	bool m_bLeft_Move;

	DWORD m_dwAttacked;
	DWORD m_dwGigant;
	DWORD m_dwMP;
	DWORD m_dwBalloon;

	POINT m_tLeft_Leg;
	POINT m_tRight_Leg;
};

