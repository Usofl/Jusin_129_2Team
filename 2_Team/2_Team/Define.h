#pragma once

#define WINCX 800
#define WINCY 600

#define GAMESIZE 50

#define PURE =0
#define	VK_MAX 0xff

#define PI 3.1415926535f
#define GRAVITY 9.80665f

#define LEGSIZE 40.f

#define DEGREE (PI / 180.f)
#define NLOG sqrtf(2.f)

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define RADIAN(x) (x * PI) / 180.f

#define DisX(x1, x2) absf(x1-x2)
#define DisX(y1, y2) absf(y1-y2)

#define DIAGONAL(x1,y1,x2,y2) sqrtf((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

#define ACOSF(x1,y1,x2,y2) (x1-x2) / DIAGONAL(x1,y1,x2,y2)

#define OBJMGR (CObjMgr::Get_Instance())
#define LINEMGR (CLineMgr::Get_Instance())
#define KEYMGR (CKeyMgr::Get_Instance())
#define SCROLLMGR (CScrollMgr::Get_Instance())
#define UIMGR (CUiMgr::Get_Instance())
#define ITEMMGR (CItemMgr::Get_Instance())

extern HWND g_hWnd;