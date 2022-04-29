#pragma once
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

	TCHAR		m_szFPS[64];	// ��Ƽ ����Ʈ ��ݿ����� CHAR�� ���� �ڵ� ��ݿ����� �����ڵ�� ó�����ִ� ��ũ��
	int			m_iFPS;
	DWORD		m_dwFPSTime;
};
