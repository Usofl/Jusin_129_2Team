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
};

