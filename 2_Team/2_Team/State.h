#pragma once
#include "Include.h"

class CState
{
public:
	CState();
	~CState();

	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	const int& Get_State() { return m_iState; }
	const void Pause(HDC _hDC) { TextOut(_hDC, WINCX / 2 - 100, WINCY / 2, TEXT("�ð�������"), 5); }
	void Set_Pause(int _State) { m_iState = _State; }
	void Get_Life(int _Life) { m_iLife = _Life; }
	void Get_Coin(int _Coin) { m_iCoin = _Coin; }

private:
	POINT m_tMouse;
	INFO m_tMouseInfo;
	RECT m_tMouseRect;
	float m_fMouseAngle;

	RECT m_tStartRect;
	RECT m_tExitRect;

	RECT m_tColli;

	int        m_iState;
	
	int			m_iLife;
	int			m_iCoin;

};

