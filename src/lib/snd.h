#ifndef SND_H
#define SND_H
#ifdef __cplusplus
extern "C" {
#endif

// ISR(TIMER3_COMPA_vect)
// ISR(TIMER1_COMPA_vect)

#include "common.h"

//---------------------------------------------------------------------------
#define SND_MAX_CHANNEL			2

enum {
	SND_OP_PLAY_NOTE = 0x90,
	SND_OP_STOP_NOTE = 0x80,
	SND_OP_RESTART   = 0xe0,
	SND_OP_STOP      = 0xf0,
};

//---------------------------------------------------------------------------
#if defined(ARDUBOY_10)

	#define SND_PIN1 5			// PC6
	#define SND_PIN2 13			// PC7

#elif defined(ARDUBOY_DEVKIT)

	#define SND_PIN1 A2
	#define SND_PIN2 A3

#endif

//---------------------------------------------------------------------------
typedef struct {
	vu8* pPinPort;
	u8   pinMask;
} ST_SND_CH;

typedef struct {
	// Score
	bool isScorePlay;
	bool isScoreCh[SND_MAX_CHANNEL];
	u32  scoreCnt;
	u32  scoreFreqCnt;
	u8*  pScoreStart;
	u8*  pScoreCur;

	// Tone
	bool isTonePlay;
	u32  toneCnt;

	// Pin
	ST_SND_CH ch[SND_MAX_CHANNEL];

} ST_SND;


//---------------------------------------------------------------------------
void SndInit(void);

void SndPlayScore(const u8* p);
void SndStopScore(void);
void SndStepScore(void);

void SndPlayNote(u8 ch, u8 note);
void SndStopNote(u8 ch);
void SndPlayTone(u16 freq, u32 duration);
void SndStopTone(void);

void SndStartTimerCh0(void);
void SndStartTimerCh(u8 ch, u32 freq);
void SndStopTimer(u8 ch);


#ifdef __cplusplus
}
#endif
#endif
