#include "menu.h"
#include "lib/oled.h"
#include "lib/key.h"
#include "res/txt.h"
#include "lv.h"
#include "log.h"

//---------------------------------------------------------------------------
ST_MENU Menu;


//---------------------------------------------------------------------------
void MenuInit(void)
{
	_Memset(&Menu, 0x00, sizeof(ST_MENU));
}
//---------------------------------------------------------------------------
void MenuExec(void)
{
	if(KeyGetTrg() & KEY_A)
	{
		Menu.isEnd = TRUE;
		return;
	}

	u8 rep = KeyGetRep();

	if(rep & KEY_U)
	{
		if(Menu.sel <= 0)
		{
			MenuSeek(-1);
		}
		else
		{
			Menu.sel--;
		}
	}
	else if(rep & KEY_D)
	{
		if(Menu.sel >= 6)
		{
			MenuSeek(1);
		}
		else
		{
			Menu.sel++;
		}
	}
	else if(rep & KEY_L)
	{
		MenuSeek(-7);
	}
	else if(rep & KEY_R)
	{
		MenuSeek(7);
	}

	if(Menu.idx + Menu.sel != LvGetNo())
	{
		LvSetRes(Menu.idx + Menu.sel);
	}
}
//---------------------------------------------------------------------------
void MenuDraw(void)
{
	OledDrawStr(1, 0, "Level");
	OledDrawChr(0, 1 + Menu.sel, 0x10);

	u8 no;
	s8 y;


	for(y=0; y<7; y++)
	{
		no = Menu.idx + y;

		OledDrawStr(1, y + 1, "%02d %s", no + 1, (LogIsLvEnd(no) == TRUE) ? "Clear" : "");
	}
}
//---------------------------------------------------------------------------
void MenuSeek(s8 move)
{
	Menu.idx += move;

	if(Menu.idx < 0)
	{
		Menu.idx = 0;
		Menu.sel = 0;
	}

	if(Menu.idx >= TXT_LV_MAX_CNT - 7)
	{
		Menu.idx = TXT_LV_MAX_CNT - 7;
		Menu.sel = 6;
	}
}
//---------------------------------------------------------------------------
bool MenuIsEnd(void)
{
	return Menu.isEnd;
}
//---------------------------------------------------------------------------
void MenuLoad(void)
{
	Menu.idx = LogGetMenuIdx();
	Menu.sel = LogGetMenuSel();

	LvSetRes(Menu.idx + Menu.sel);
}
//---------------------------------------------------------------------------
void MenuSave(void)
{
	LogSaveMenu(Menu.idx, Menu.sel);
}
