#include "clear.h"
#include "lib/key.h"
#include "lib/oled.h"

//---------------------------------------------------------------------------
ST_CLEAR Clear;


//---------------------------------------------------------------------------
void ClearInit(void)
{
	_Memset(&Clear, 0x00, sizeof(ST_CLEAR));
}
//---------------------------------------------------------------------------
void ClearExec(void)
{
	if(KeyGetTrg() & KEY_B)
	{
		Clear.isEnd = TRUE;
	}
}
//---------------------------------------------------------------------------
void ClearDraw(void)
{
	OledDrawStr(2, 7, "Clear !");
}
//---------------------------------------------------------------------------
bool ClearIsEnd(void)
{
	return Clear.isEnd;
}
