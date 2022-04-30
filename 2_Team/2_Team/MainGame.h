#pragma once
#include "Player.h"
#include "State.h"
#include "M_Cloud.h"
#include "Koopa.h"
#include "Warrior.h"

#include "UI.h"
#include "Coin.h"
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

	TCHAR		m_szFPS[64];	// 멀티 바이트 기반에서는 CHAR로 유니 코드 기반에서는 유니코드로 처리해주는 매크로
	int			m_iFPS;
	DWORD		m_dwFPSTime;

	CState*		m_pState;
	bool        m_Pause;
	DWORD         m_dwTime;

	CUI*		m_pUI;
};

