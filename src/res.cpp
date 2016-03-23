#include "res.h"
#include "res/img.h"
#include "lib/oled.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void ResInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
void ResDrawBox(s8 bx, s8 by)
{
	OledDrawBlock(bx, by, (u8*)bmpBox);
}
//---------------------------------------------------------------------------
void ResDrawBox2(s8 x, s8 y)
{
	OledDrawBlock2(x, y, (u8*)bmpBox);
}
//---------------------------------------------------------------------------
void ResDrawChr(s8 bx, s8 by)
{
	OledDrawBlock(bx, by, (u8*)bmpChr);
}
//---------------------------------------------------------------------------
void ResDrawChr2(s8 x, s8 y)
{
	OledDrawBlock2(x, y, (u8*)bmpChr);
}
//---------------------------------------------------------------------------
void ResDrawSqu(s8 bx, s8 by)
{
	OledDrawBlock(bx, by, (u8*)bmpSqu);
}
//---------------------------------------------------------------------------
void ResDrawBoxOn(s8 bx, s8 by)
{
	OledDrawBlock(bx, by, (u8*)bmpBox_on);
}
//---------------------------------------------------------------------------
void ResDrawChrOn(s8 bx, s8 by)
{
	OledDrawBlock(bx, by, (u8*)bmpChr_on);
}
//---------------------------------------------------------------------------
void ResDrawWall(s8 bx, s8 by, u8 num)
{
	OledDrawBlockWall(bx, by, (u8*)pngWall, num);
}
