#ifndef LOG_H
#define LOG_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"
#include "res/txt.h"


//---------------------------------------------------------------------------

typedef struct {
	u8 lv[TXT_LV_MAX_CNT];
	s8 idx;
	s8 sel;

} ST_LOG;


//---------------------------------------------------------------------------
void LogInit(void);

void LogMake(void);
void LogLoad(void);
void LogSaveLvEnd(u8 no);
void LogSaveMenu(s8 idx, s8 sel);

s8   LogGetMenuIdx(void);
s8   LogGetMenuSel(void);

bool LogIsLvEnd(u8 no);
bool LogIsExist(void);


#ifdef __cplusplus
}
#endif
#endif
