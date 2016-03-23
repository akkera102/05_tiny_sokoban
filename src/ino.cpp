#include "ino.h"
#include "lib/sys.h"
#include "game.h"

//---------------------------------------------------------------------------
void setup(void)
{
	SysInit();

	GameInit();
}
//---------------------------------------------------------------------------
void loop(void)
{
	if(SysLoop() == FALSE)
	{
		return;
	}

	GameLoop();

	SysLoopEnd();
}
