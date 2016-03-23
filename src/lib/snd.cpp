#include "snd.h"
#include <Arduino.h>
#include <avr/power.h>
#include "oled.h"

//---------------------------------------------------------------------------
PROGMEM const unsigned int SndMidiNoteFreq[128] = {
	16,17,18,19,21,22,23,24,26,28,29,31,33,35,37,39,41,44,46,49,52,55,58,62,65,
	69,73,78,82,87,92,98,104,110,117,123,131,139,147,156,165,175,185,196,208,220,
	233,247,262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,659,
	698,740,784,831,880,932,988,1047,1109,1175,1245,1319,1397,1480,1568,1661,1760,
	1865,1976,2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951,4186,
	4435,4699,4978,5274,5588,5920,6272,6645,7040,7459,7902,8372,8870,9397,9956,
	10548,11175,11840,12544,13290,14080,14917,15804,16744,17740,18795,19912,21096,
	22351,23680,25088
};

//---------------------------------------------------------------------------
ST_SND Snd;

//---------------------------------------------------------------------------
void SndInit(void)
{
	_Memset(&Snd,   0x00, sizeof(ST_SND));

	pinMode(SND_PIN_CH1, OUTPUT);
	pinMode(SND_PIN_CH2, OUTPUT);

	Snd.ch[0].pPinPort = portOutputRegister(digitalPinToPort(SND_PIN_CH1));
	Snd.ch[0].pinMask  = digitalPinToBitMask(SND_PIN_CH1);
	Snd.ch[1].pPinPort = portOutputRegister(digitalPinToPort(SND_PIN_CH2));
	Snd.ch[1].pinMask  = digitalPinToBitMask(SND_PIN_CH2);

	TCCR3A = 0;
	TCCR3B = 0;
	TCCR1A = 0;
	TCCR1B = 0;

	bitWrite(TCCR3B, WGM32, 1);
	bitWrite(TCCR3B, CS30,  1);
	bitWrite(TCCR1B, WGM12, 1);
	bitWrite(TCCR1B, CS10,  1);

	power_timer3_enable();
	power_timer1_enable();
}
//---------------------------------------------------------------------------
void SndPlayScore(const u8* p)
{
	Snd.pScoreStart  = (u8*)p;
	Snd.pScoreCur    = (u8*)p;
	Snd.scoreCnt     = 1;
	Snd.scoreFreqCnt = 0;
	Snd.isScoreCh[0] = FALSE;
	Snd.isScoreCh[1] = FALSE;
	Snd.isScorePlay  = TRUE;

	SndStartTimerCh0();
}
//---------------------------------------------------------------------------
void SndStopScore(void)
{
	SndStopTimer(0);
	SndStopTimer(1);

	Snd.isScorePlay = FALSE;
}
//---------------------------------------------------------------------------
void SndStepScore(void)
{
	for(;;)
	{
		u8 cmd = __LPM(Snd.pScoreCur++);

		u8 op  = cmd & 0xf0;
		u8 ch  = cmd & 0x0f;

		switch(op)
		{
		case SND_OP_PLAY_NOTE:
			SndPlayNote(ch, __LPM(Snd.pScoreCur++));
			break;

		case SND_OP_STOP_NOTE:
			SndStopNote(ch);
			break;

		case SND_OP_RESTART:
			Snd.pScoreCur = Snd.pScoreStart;
			break;

		case SND_OP_STOP:
			SndStopScore();
			return;

		default:
			if(op < 0x80)
			{
				// wait count in msec.
				u16 duration = ((u16)cmd << 8) | __LPM(Snd.pScoreCur++);
				Snd.scoreCnt = ((u32)Snd.scoreFreqCnt * duration + 500) / 1000;

				if(Snd.scoreCnt == 0)
				{
					Snd.scoreCnt = 1;
				}
				return;
			}

			_SystemError("[Snd %x %x]", cmd, Snd.pScoreCur - Snd.pScoreStart);
		}
	} // for(;;)
}
//---------------------------------------------------------------------------
void SndPlayNote(u8 ch, u8 note)
{
	if(ch == 1 && Snd.isTonePlay == TRUE)
	{
		return;
	}


	u16 freq = __LPM_word(SndMidiNoteFreq + note);

	if(ch == 0)
	{
		Snd.scoreFreqCnt = freq;
	}

	Snd.isScoreCh[ch] = TRUE;
	SndStartTimerCh(ch, F_CPU / freq);
}
//---------------------------------------------------------------------------
void SndStopNote(u8 ch)
{
	Snd.isScoreCh[ch] = FALSE;

	*Snd.ch[ch].pPinPort &= ~Snd.ch[ch].pinMask;
}
//---------------------------------------------------------------------------
void SndPlayTone(u16 freq, u32 duration)
{
	if(Snd.isTonePlay == TRUE)
	{
		return;
	}
	Snd.isTonePlay = TRUE;


	u32 cnt = 2 * freq * duration / 1000;

	if(cnt == 0)
	{
		return;
	}
	Snd.toneCnt = cnt;


	SndStartTimerCh(1, F_CPU / freq / 2);
}
//---------------------------------------------------------------------------
void SndStopTone(void)
{
	SndStopTimer(1);

	Snd.isTonePlay = FALSE;
}
//---------------------------------------------------------------------------
void SndStartTimerCh0(void)
{
	TCCR3B = (TCCR3B & 0xf8) | 0x01;
	OCR3A  = 0xffff;

	bitWrite(TIMSK3, OCIE3A, 1);
}
//---------------------------------------------------------------------------
void SndStartTimerCh(u8 ch, u32 freq)
{
	// timer ck/1
	u32 ocr = freq;
	u8  pre = 0x01;

	if(ocr > 0xffff)
	{
		// ck/64
		ocr /= 64;
		pre  = 0x03;
	}
	ocr--;


	if(ch == 0)
	{
		TCCR3B = (TCCR3B & 0xf8) | pre;
		OCR3A  = ocr;
		bitWrite(TIMSK3, OCIE3A, 1);
	}
	else
	{
		TCCR1B = (TCCR1B & 0xf8) | pre;
		OCR1A  = ocr;
		bitWrite(TIMSK1, OCIE1A, 1);
	}
}
//---------------------------------------------------------------------------
void SndStopTimer(u8 ch)
{
	if(ch == 0)
	{
		TIMSK3 &= ~(1 << OCIE3A);
	}
	else
	{
		TIMSK1 &= ~(1 << OCIE1A);
	}

	*Snd.ch[ch].pPinPort &= ~Snd.ch[ch].pinMask;
}
//---------------------------------------------------------------------------
// TIMER 3 ch0
ISR(TIMER3_COMPA_vect)
{
	if(Snd.isScoreCh[0] == TRUE)
	{
		*Snd.ch[0].pPinPort ^= Snd.ch[0].pinMask;
	}

	Snd.scoreCnt--;

	if(Snd.scoreCnt == 0)
	{
		SndStepScore();
	}
}
//---------------------------------------------------------------------------
// TIMER 1 ch1
ISR(TIMER1_COMPA_vect)
{
	*Snd.ch[1].pPinPort ^= Snd.ch[1].pinMask;


	if(Snd.isTonePlay == FALSE)
	{
		return;
	}

	if(--Snd.toneCnt == 0)
	{
		SndStopTone();
	}
}
