#pragma once

#define WINCX 800
#define WINCY 600

#define GAMESIZE 50

#define PURE =0

#define PI 3.1415926535f
#define GRAVITY 9.80665f // 중력값

#define LEGSIZE 40.f // 플레이어 다리 길이

#define NLOG sqrtf(2.f) // 자연 로그 ( 대각선 이동시 사용 )

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define RADIAN(x) (x * PI) / 180.f

#define DisX(x1, x2) absf(x1-x2)
#define DisX(y1, y2) absf(y1-y2)

#define DIAGONAL(x1,y1,x2,y2) sqrtf((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

#define ACOSF(x1,y1,x2,y2) (x1-x2) / DIAGONAL(x1,y1,x2,y2)

extern HWND g_hWnd;