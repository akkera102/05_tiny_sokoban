#ifndef KEY_H
#define KEY_H
#ifdef __cplusplus
extern "C" {
#endif

#include <pins_arduino.h>
#include "common.h"

//---------------------------------------------------------------------------
#define KEY_PIN_L				9
#define KEY_PIN_R				5
#define KEY_PIN_U				8
#define KEY_PIN_D				10
#define KEY_PIN_A				A0		// pins_arduino.h
#define KEY_PIN_B				A1

#define KEY_REPEAT_CNT			18

enum {
	KEY_A = (1 << 0),
	KEY_B = (1 << 1),
	KEY_R = (1 << 2),
	KEY_U = (1 << 4),
	KEY_L = (1 << 5),
	KEY_D = (1 << 6),

	KEY_ALL = (KEY_U | KEY_D | KEY_L | KEY_R | KEY_A | KEY_B),
};

//---------------------------------------------------------------------------
typedef struct {
	u8 cnt;
	u8 trg;
	u8 off;
	u8 rep;
	s8 repCnt;

} ST_KEY;

//---------------------------------------------------------------------------
void KeyInit(void);
void KeyLoop(void);

u8   KeyGetCnt(void);
u8   KeyGetTrg(void);
u8   KeyGetOff(void);
u8   KeyGetRep(void);


#ifdef __cplusplus
}
#endif
#endif
