#include "play.h"
#include "lib/oled.h"
#include "lib/key.h"
#include "anime.h"

//---------------------------------------------------------------------------
ST_PLAY Play;


//---------------------------------------------------------------------------
void PlayInit(void)
{
	_Memset(&Play, 0x00, sizeof(ST_PLAY));
}
//---------------------------------------------------------------------------
void PlayExec(void)
{
	switch(Play.act)
	{
	case PLAY_EXEC_GAME:
		PlayExecGame();
		break;

	case PLAY_EXEC_QUIT:
		PlayExecQuit();
		break;

	default:
		ERROR(Play.act);
		break;
	}
}
//---------------------------------------------------------------------------
void PlayExecGame(void)
{
	u8 rep = KeyGetRep();

	if(KeyGetTrg() & KEY_B)
	{
		PlaySetAct(PLAY_EXEC_QUIT);
	}
	else if(rep & KEY_A)
	{
		AnimeCalcPrev();
	}
	else if(rep & KEY_U)
	{
		AnimeCalcMoveU();
	}
	else if(rep & KEY_D)
	{
		AnimeCalcMoveD();
	}
	else if(rep & KEY_L)
	{
		AnimeCalcMoveL();
	}
	else if(rep & KEY_R)
	{
		AnimeCalcMoveR();
	}
}
//---------------------------------------------------------------------------
void PlayExecQuit(void)
{
	u8 trg = KeyGetTrg();

	if(trg & KEY_B)
	{
		PlaySetAct(PLAY_EXEC_GAME);
	}
	else if(trg & KEY_A)
	{
		Play.isEnd = TRUE;
	}
}
//---------------------------------------------------------------------------
void PlayDraw(void)
{
	switch(Play.act)
	{
	case PLAY_EXEC_GAME:
		PlayDrawGame();
		break;

	case PLAY_EXEC_QUIT:
		PlayDrawQuit();
		break;

	default:
		ERROR(Play.act);
		break;
	}
}
//---------------------------------------------------------------------------
void PlayDrawGame(void)
{
	OledDrawStr(1, 0, "Tiny");
	OledDrawStr(2, 1, "Sokoban");

	OledDrawStr(2, 4, "Moves");
	OledDrawStr(3, 5, "%3d", AnimeGetMoveCnt());
}
//---------------------------------------------------------------------------
void PlayDrawQuit(void)
{
	OledDrawStr(1, 0, "Tiny");
	OledDrawStr(2, 1, "Sokoban");

	OledDrawStr(2, 4, "Quit ?");
}
//---------------------------------------------------------------------------
bool PlayIsEnd(void)
{
	return Play.isEnd;
}
//---------------------------------------------------------------------------
void PlaySetAct(u8 act)
{
	Play.act = act;
}
