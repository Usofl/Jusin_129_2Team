#pragma once
#include "Include.h"
//#include "Pause.h"

class CUi
{
public:
	CUi();
	~CUi();
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();
	//int Key_Input();

	const int& Get_State() { return m_iState; }
	const void Pause(HDC _hDC){ TextOut(_hDC, WINCX / 2 - 100, WINCY / 2, TEXT("시간정지중"), 5); }
	void Set_Pause(int _State) { m_iState = _State; }
	//void Key_Input();

private:
	POINT m_Mouse;
	INFO m_MouseInfo;
	RECT m_MouseRect;
	float m_fMouseAngle;

	RECT m_StartRect;
	RECT m_ExitRect;

	RECT m_Colli;

	int		m_iState;





	//CPause* m_pPause;
};

