#pragma once

typedef struct tag_info
{
	float fX;
	float fY;

	float fCY;
	float fCX;
}INFO;

typedef struct tag_pointinfo
{
	float fX;
	float fY;

	tag_pointinfo() {}
	tag_pointinfo(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

typedef struct tag_lineinfo
{
	LINEPOINT tLeft;
	LINEPOINT tRight;

	tag_lineinfo() {}
	tag_lineinfo(LINEPOINT _tLeft, LINEPOINT _tRight) : tLeft(_tLeft), tRight(_tRight) {}

}LINE;