#include "log.h"
#include "lib/eep.h"

// 0x00 - 0x03   4バイト : シグネチャ（SOUK）
// 0x04          1バイト : 書き込む完了フラグ 'W' OK、その他 エラー
// 0x10 - 0x43 各1バイト : 1-52マップのクリアフラグ  0x01 クリア、0x00 クリアしてない
// 0x50          1バイト : Menu.idx
// 0x51          1バイト : Menu.sel

//---------------------------------------------------------------------------
ST_LOG Log;


//---------------------------------------------------------------------------
void LogInit(void)
{
	_Memset(&Log, 0x00, sizeof(ST_LOG));


	if(LogIsExist() == TRUE)
	{
		LogLoad();
	}
	else
	{
		LogMake();
	}
}
//---------------------------------------------------------------------------
void LogMake(void)
{
	// メニュー
	EepSeek(0x50);

	EepWrite8(0x00);
	EepWrite8(0x00);

	// レベル
	EepSeek(0x10);

	u8 i;

	for(i=0; i<TXT_LV_MAX_CNT; i++)
	{
		EepWrite8(0x00);
	}

	// シグネチャ
	EepSeek(0);

	EepWrite8('S');
	EepWrite8('O');
	EepWrite8('U');
	EepWrite8('K');
	EepWrite8('W');
}
//---------------------------------------------------------------------------
void LogLoad(void)
{
	// メニュー
	EepSeek(0x50);

	Log.idx = EepRead8();
	Log.sel = EepRead8();

	// レベル
	EepSeek(0x10);

	u8 i;

	for(i=0; i<TXT_LV_MAX_CNT; i++)
	{
		Log.lv[i] = EepRead8();
	}
}
//---------------------------------------------------------------------------
void LogSaveLvEnd(u8 no)
{
	ASSERT(no < TXT_LV_MAX_CNT);

	EeepWriteAdr8(0x5, ' ');
	EeepWriteAdr8(0x10 + no, 0x01);
	EeepWriteAdr8(0x5, 'W');

	Log.lv[no] = 0x01;
}
//---------------------------------------------------------------------------
void LogSaveMenu(s8 idx, s8 sel)
{
	EeepWriteAdr8(0x5, ' ');
	EeepWriteAdr8(0x50, idx);
	EeepWriteAdr8(0x51, sel);
	EeepWriteAdr8(0x5, 'W');

	Log.idx = idx;
	Log.sel = sel;
}
//---------------------------------------------------------------------------
s8 LogGetMenuIdx(void)
{
	return Log.idx;
}
//---------------------------------------------------------------------------
s8 LogGetMenuSel(void)
{
	return Log.sel;
}
//---------------------------------------------------------------------------
bool LogIsLvEnd(u8 no)
{
	return (Log.lv[no] == 0x01) ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
bool LogIsExist(void)
{
	EepSeek(0);

	if(EepRead8() != 'S') return FALSE;
	if(EepRead8() != 'O') return FALSE;
	if(EepRead8() != 'U') return FALSE;
	if(EepRead8() != 'K') return FALSE;
	if(EepRead8() != 'W') return FALSE;

	return TRUE;
}
