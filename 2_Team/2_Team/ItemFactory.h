#include "Obj.h"
#include "Include.h"
#include "Item.h"
#include "Gun.h"
#include "Life.h"
#include "Ladder.h"
#include "Key.h"
#include "Recovery.h"
#include "Stamina.h"
#include "Room.h"

class ItemFactory
{
public:
	ItemFactory() {};
	~ItemFactory() {};

	static CObj*	Create_Gun()
	{
		CObj* Obj = new CGun;
		Obj->Initialize();
		return Obj;
	}
	static CObj*	Create_Life()
	{
		CObj* Obj = new CLife;
		Obj->Initialize();
		return Obj;
	}
	static CObj*	Create_Ladder()
	{
		CObj* Obj = new CLadder;
		Obj->Initialize();
		return Obj;
	}
	static CObj*	Create_Key()
	{
		CObj* Obj = new CKey;
		Obj->Initialize();
		return Obj;
	}
	static CObj*	Create_Recovery()
	{
		CObj* Obj = new CRecovery;
		Obj->Initialize();
		return Obj;
	}
	static CObj*	Create_Stamina()
	{
		CObj* Obj = new CStamina;
		Obj->Initialize();
		return Obj;
	}
	static CObj*	Create_Room()
	{
		CObj* Obj = new CRoom;
		Obj->Initialize();
		return Obj;
	}
};