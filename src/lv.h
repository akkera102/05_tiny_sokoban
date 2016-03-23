#ifndef LV_H
#define LV_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------
#define LV_MAX_CX			8
#define LV_MAX_CY			8


//---------------------------------------------------------------------------

typedef struct {
	s8  no;
	u8  code[LV_MAX_CX][LV_MAX_CY];
	u8  wall[LV_MAX_CX][LV_MAX_CY];

} ST_LV;



//---------------------------------------------------------------------------
void LvInit(void);
void LvDraw(void);

void LvSetRes(u8 no);
void LvSetResCode(void);
void LvSetResWall(void);

void LvSetCode(u8 x, u8 y, u8 code);
void LvSetCodeTurnChr(u8 x, u8 y);
void LvSetCodeTurnBox(u8 x, u8 y);
u8   LvGetCode(u8 x, u8 y);
s8   LvGetNo(void);

bool LvIsBox(u8 x, u8 y);
bool LvIsChr(u8 x, u8 y);
bool LvIsWall(u8 x, u8 y);
bool LvIsClear(void);


#ifdef __cplusplus
}
#endif
#endif
