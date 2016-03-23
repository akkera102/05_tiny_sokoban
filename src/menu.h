#ifndef MENU_H
#define MENU_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------

typedef struct {
	s8   idx;
	s8   sel;
	bool isEnd;

} ST_MENU;



//---------------------------------------------------------------------------
void MenuInit(void);
void MenuExec(void);
void MenuDraw(void);
void MenuSeek(s8 move);

bool MenuIsEnd(void);

void MenuLoad(void);
void MenuSave(void);

#ifdef __cplusplus
}
#endif
#endif
