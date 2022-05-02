#pragma once
#include "State.h"

class CMainGame
{
public:
	CMainGame();
	virtual ~CMainGame();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(void);
	void Release(void);

public:
	void Key_Input(void); 

private:
	HDC		m_hDC;

	TCHAR		m_szFPS[64];
	int			m_iFPS;
	DWORD		m_dwFPSTime;

	CState*		m_pState;
	bool        m_Pause;
	DWORD       m_dwPauseTime;

};

