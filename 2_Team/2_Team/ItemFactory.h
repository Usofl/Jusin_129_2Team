#include "Obj.h"
#include "Include.h"
#include "Item.h"
#include "Gun.h"
#include "Life.h"
#include "Ladder.h"
#include "Key.h"

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
	static CObj*	Create_KEY()
	{
		CObj* Obj = new CKey;
		Obj->Initialize();
		return Obj;
	}
};