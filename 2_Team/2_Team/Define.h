#pragma once

#define WINCX 800
#define WINCY 600

#define PURE =0
#define PI 3.141592f

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define RADIAN(x) (x * PI) / 180.f

#define DisX(x1, x2) absf(x1-x2)
#define DisX(y1, y2) absf(y1-y2)

#define DIAGONAL(x1,y1,x2,y2) sqrtf((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

#define ACOSF(x1,y1,x2,y2) (x1-x2) / DIAGONAL(x1,y1,x2,y2)

extern HWND g_hWnd;