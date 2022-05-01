#include "Obj.h"
#include "Include.h"
#include "Item.h"
#include "Gun.h"
#include "Life.h"

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
};