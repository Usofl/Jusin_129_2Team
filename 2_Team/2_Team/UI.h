#pragma once
class CUI
{
public:
	CUI();
	~CUI();

	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

	void Get_Coin(int _Coin) { m_iCoin = _Coin; }
	void Get_Life(int _Life) { m_iLife = _Life; }

private:
	RECT m_tLifeRect;

	RECT m_tCoinRect;
	INFO m_tCoin;
	float m_fAngle;

	RECT m_tCoinTextRect;

	int m_iCoin;
	int m_iLife;
};

