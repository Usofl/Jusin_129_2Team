#include "stdafx.h"
#include "GameMap.h"
#include "LineFactory.h"
#include "Include.h"
#include "BlockFactory.h"
#include "ObjMgr.h"
#include "TrapFactory.h"

CGameMap::CGameMap()
{
}


CGameMap::~CGameMap()
{
}

void CGameMap::Map_Maker()
{
	LINEPOINT _Linepoint[6] =
	{
		{ 000,450 },
		{ 800,450 },
		{ 000,320 },
		{ 400,320 },
		{ 700,100 },
		{ 700,450 }
	};

	OBJMGR->Add_Notbeing(NOTBEING_TRAP, *CTrapFactory::Create_Thorn());

	//A
	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({0,550}, {5000,550}));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 0,400 }, { 600,400 }));
	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 600,330 }, { 600,400 }));
	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 600,330 }, { 800,330 }));
	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 800,330 }, { 800,400 }));

	//B
	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 800,400 }, { 1200,400 }));

	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 1200,260 }, { 1200,400 }));

	OBJMGR->Add_Notbeing(NOTBEING_BLOCK, *CBlockFactory::Create(1000, 250));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 1200,260 }, { 1500,260 }));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 1500,260 }, { 2000,400 }));


	//C

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 2000,400 }, { 2500,400 }));

	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 2500,400 }, { 2500,600 }));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 2500,600 }, { 2750,600 }));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 2500,400 }, { 2750,400 }));


	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 2750,400 }, { 2750,600 }));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 2750,400 }, { 3100,400 }));

	OBJMGR->Add_Notbeing(NOTBEING_BLOCK, *CBlockFactory::Create(2930, 100));
	OBJMGR->Add_Notbeing(NOTBEING_BLOCK, *CBlockFactory::Create(3000, 100));
	OBJMGR->Add_Notbeing(NOTBEING_BLOCK, *CBlockFactory::Create(3000, 250));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 2200,50 }, { 2950,50 }));
	// À§¿¡ ¼±

	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 3100,200 }, { 3100,400 }));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 3100,200 }, { 3400,200 }));

	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 3400,200 }, { 3400,600 }));

	//d
	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 3600,400 }, { 3600,600 }));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 3600,400 }, { 3900,400 }));

	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 3900,400 }, { 3900,600 }));
	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 4100,550 }, { 4100,600 }));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 4100,550 }, { 4300,300 }));
	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 4300,300 }, { 4400,300 }));
	
	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 4400,300 }, { 4400,600 }));

	OBJMGR->Add_Notbeing(NOTBEING_WALL, *CLineFactory::Create_Line({ 4900,300 }, { 4900,600 }));

	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 4900,300 }, { 5100,300 }));
	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 5100,300 }, { 5400,500 }));
	OBJMGR->Add_Notbeing(NOTBEING_LINE, *CLineFactory::Create_Line({ 5400,500 }, { 5700,500 }));


	//m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(200, 0));
	//m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(280, 250));
	//m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(360, 250));
	//m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(440, 350));
	//m_NotBeing_list[NOTBEING_BLOCK].push_back(CBlockFactory::Create(520, 300));


	//m_NotBeing_list[NOTBEING_TRAP].push_back(CTrapFactory::Create_Thorn());

	//m_NotBeing_list[NOTBEING_ITEM].push_back(ItemFactory::Create_Gun());
	//m_NotBeing_list[NOTBEING_ITEM].push_back(ItemFactory::Create_Life());
	//m_NotBeing_list[NOTBEING_ITEM].push_back(ItemFactory::Create_Ladder());
	//m_NotBeing_list[NOTBEING_ITEM].push_back(ItemFactory::Create_KEY());

}