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

private:
	POINT m_Mouse;
	INFO m_MouseInfo;
	RECT m_MouseRect;
	float m_fMouseAngle;

	RECT m_StartRect;
	RECT m_ExitRect;

	RECT m_Colli;

	int        m_iState;

};

