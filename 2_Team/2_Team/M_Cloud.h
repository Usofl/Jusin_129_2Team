#pragma once
#include "Being.h"
#include "Obj.h"
#include "Monster.h"
#include "Player.h"
#include "Cloud_Bullet.h"
#include "ObjMgr.h"
#include "Collision.h"

class CM_Cloud :
	public CMonster
{
public:
	CM_Cloud();
	virtual ~CM_Cloud();

public:
	virtual void Initialize(void) override;
	virtual const int&  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	// 시간 저장하는 변수
	DWORD m_dwCount;
};



