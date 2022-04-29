#pragma once
#include "Obj.h"
#include "Bullet.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int		Update(void) override;
	virtual		void	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void		Jumping(void);
	void		OffSet(void);

private:


	POINT					m_tPosin;
	float					m_fDiagonal;


	bool					m_bJump;		// ���� ���� Ȯ��
	float					m_fJumpPower;	// ���� ��
	float					m_fJumpTime;	// ���� �� ���� �ð�


};

// 1. �÷��̾� ���� ����(�÷��̾� �߽����� �����ϴ� ���� �����ϱ�)
// 2. ��ũ�� �̻��� ����
// 3. �÷��̾ ����ٴϴ� ���� ����(���Լ� ���)


// �Լ�		: ���, Input�� Output�� ����		Y = F(X)	-> y = x + 1
// �ﰢ �Լ�  : �����ڵ��� ã�� ����, �غ�, ���� ���̿� ���踦 �ǹ�, ���� ���� �˸� �� ���̿� �������� ���踦 ������ ���� �Լ�
