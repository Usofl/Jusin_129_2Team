#pragma once
#include "Being.h"
#include "Collision.h"
#include "ObjMgr.h"
#include "GomuFactory.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"

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
	inline bool& Get_Jumping(void) { return m_bJump; }

	void Jumping(void);
	void SetBody(void);
	void OffSet(void);

	bool Get_Pool() { return m_bPool;}
	int Set_Coin() { return m_iCoin; }
	int Set_Life() { return m_iLife; }
	void PlayerCoinColli(void);
	void Get_ItemType(int _Itemtype);

	void Set_Jump() { m_bJump = false; }
	void Set_Right_Move(bool _bMove) { m_bRight_Move = _bMove; }
	void Set_Left_Move(bool _bMove) { m_bLeft_Move = _bMove; }

private:
	void Key_Input(void);
	const bool& Front_Leg(void) { return m_tLeft_Leg.x > m_tRight_Leg.x; }

private:
	bool m_bChange;
	bool m_bJump;
	bool m_bPool;
	bool m_bBalloon;

	int   m_iReverse;
	int   m_iCoin;
	int   m_iLife;
	int   m_iItemtype;
	float m_fJumpTime;
	float m_fJumpPower;
	float m_fJumpAngle;

	bool m_bRight_Move;
	bool m_bLeft_Move;

	POINT m_tLeft_Leg;
	POINT m_tRight_Leg;
};

