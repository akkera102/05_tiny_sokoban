#ifndef CLEAR_H
#define CLEAR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	bool isEnd;

} ST_CLEAR;



//---------------------------------------------------------------------------
void ClearInit(void);
void ClearExec(void);
void ClearDraw(void);

bool ClearIsEnd(void);

#ifdef __cplusplus
}
#endif
#endif
