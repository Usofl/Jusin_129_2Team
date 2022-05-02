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
	void Get_Hp(int _Hp) { m_iHp = _Hp; }
	void Get_Mp(int _Mp) { m_iMp = _Mp; }
	void Get_Itemtype(int _Item) { m_iItem = _Item; }

private:
	RECT m_tLifeRect;

	RECT m_tCoinRect;
	INFO m_tCoin;
	float m_fAngle;

	RECT m_tCoinTextRect;

	RECT m_tItemRect;
	RECT m_tGun;
	
	RECT m_tHp;
	RECT m_tMp;

	int m_iCoin;
	int m_iLife;
	int m_iItem;
	int m_iHp;
	int m_iMp;

	bool m_bGun;
};

