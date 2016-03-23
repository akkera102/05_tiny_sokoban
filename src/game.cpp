#include "game.h"
#include "menu.h"
#include "lv.h"
#include "res.h"
#include "play.h"
#include "anime.h"
#include "log.h"
#include "clear.h"

//---------------------------------------------------------------------------
ST_GAME Game;


//---------------------------------------------------------------------------
void GameInit(void)
{
	_Memset(&Game, 0x00, sizeof(ST_GAME));
}
//---------------------------------------------------------------------------
void GameLoop(void)
{
	switch(Game.act)
	{
	case GAME_EXEC_RESET: GameExecReset(); break;
	case GAME_EXEC_MENU:  GameExecMenu();  break;
	case GAME_EXEC_PLAY:  GameExecPlay();  break;
	case GAME_EXEC_ANIME: GameExecAnime(); break;
	case GAME_EXEC_CLEAR: GameExecClear(); break;

	default:
		ERROR(Game.act);
		break;
	}
}
//---------------------------------------------------------------------------
void GameExecReset(void)
{
	AnimeInit();
	ClearInit();
	MenuInit();
	PlayInit();
	ResInit();
	LogInit();
	LvInit();

	MenuLoad();

	GameSetAct(GAME_EXEC_MENU);
}
//---------------------------------------------------------------------------
void GameExecMenu(void)
{
	LvDraw();
	MenuDraw();

	MenuExec();


	if(MenuIsEnd() == TRUE)
	{
		MenuSave();

		GameSetAct(GAME_EXEC_PLAY);
	}
}
//---------------------------------------------------------------------------
void GameExecPlay(void)
{
	LvDraw();
	PlayDraw();

	PlayExec();


	if(PlayIsEnd() == TRUE)
	{
		GameSetAct(GAME_EXEC_RESET);
	}
	else if(AnimeIsEnd() == FALSE)
	{
		GameSetAct(GAME_EXEC_ANIME);
	}
}
//---------------------------------------------------------------------------
void GameExecAnime(void)
{
	LvDraw();
	PlayDraw();
	AnimeDraw();

	AnimeExec();


	if(AnimeIsEnd() == FALSE)
	{
		return;
	}

	if(LvIsClear() == TRUE)
	{
		GameSetAct(GAME_EXEC_CLEAR);
	}
	else
	{
		GameSetAct(GAME_EXEC_PLAY);
	}
}
//---------------------------------------------------------------------------
void GameExecClear(void)
{
	LvDraw();
	PlayDraw();
	ClearDraw();

	ClearExec();


	if(ClearIsEnd() == TRUE)
	{
		LogSaveLvEnd(LvGetNo());

		GameSetAct(GAME_EXEC_RESET);
	}
}
//---------------------------------------------------------------------------
void GameSetAct(u8 act)
{
	Game.act = act;
}
