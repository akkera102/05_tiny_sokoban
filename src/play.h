#ifndef PLAY_H
#define PLAY_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------

enum {
	PLAY_EXEC_GAME,
	PLAY_EXEC_QUIT,
};

//---------------------------------------------------------------------------

typedef struct {
	u8   act;
	bool isEnd;

} ST_PLAY;



//---------------------------------------------------------------------------
void PlayInit(void);

void PlayExec(void);
void PlayExecGame(void);
void PlayExecQuit(void);

void PlayDraw(void);
void PlayDrawGame(void);
void PlayDrawQuit(void);

bool PlayIsEnd(void);
void PlaySetAct(u8 act);


#ifdef __cplusplus
}
#endif
#endif
