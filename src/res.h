#ifndef RES_H
#define RES_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void ResInit(void);

void ResDrawBox(s8 bx, s8 by);
void ResDrawBox2(s8 x, s8 y);
void ResDrawChr(s8 bx, s8 by);
void ResDrawChr2(s8 x, s8 y);
void ResDrawSqu(s8 bx, s8 by);
void ResDrawBoxOn(s8 bx, s8 by);
void ResDrawChrOn(s8 bx, s8 by);
void ResDrawWall(s8 bx, s8 by, u8 num);


#ifdef __cplusplus
}
#endif
#endif
