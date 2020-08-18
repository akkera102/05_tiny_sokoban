#include "log.h"
#include "lib/eep.h"

// 0x00 - 0x03   4�o�C�g : �V�O�l�`���iSOUK�j
// 0x05          1�o�C�g : �������ފ����t���O 'W' OK�A���̑� �G���[
// 0x10 - 0x43 �e1�o�C�g : 1-52�}�b�v�̃N���A�t���O  0x01 �N���A�A0x00 �N���A���ĂȂ�
// 0x50          1�o�C�g : Menu.idx
// 0x51          1�o�C�g : Menu.sel

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
	// ���j���[
	EepSeek(0x50);

	EepWrite8(0x00);
	EepWrite8(0x00);

	// ���x��
	EepSeek(0x10);

	u8 i;

	for(i=0; i<TXT_LV_MAX_CNT; i++)
	{
		EepWrite8(0x00);
	}

	// �V�O�l�`��
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
	// ���j���[
	EepSeek(0x50);

	Log.idx = EepRead8();
	Log.sel = EepRead8();

	// ���x��
	EepSeek(0x10);

	u8 i;

	for(i=0; i<TXT_LV_MAX_CNT; i++)
	{
		Log.lvEnd[i] = EepRead8();
	}
}
//---------------------------------------------------------------------------
void LogSaveLvEnd(u8 no)
{
	ASSERT(no < TXT_LV_MAX_CNT);

	EepWriteAdr8(0x5, ' ');
	EepWriteAdr8(0x10 + no, 0x01);
	EepWriteAdr8(0x5, 'W');

	Log.lvEnd[no] = 0x01;
}
//---------------------------------------------------------------------------
void LogSaveMenu(s8 idx, s8 sel)
{
	EepWriteAdr8(0x5, ' ');
	EepWriteAdr8(0x50, idx);
	EepWriteAdr8(0x51, sel);
	EepWriteAdr8(0x5, 'W');

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
	return (Log.lvEnd[no] == 0x01) ? TRUE : FALSE;
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
