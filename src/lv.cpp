#include "lv.h"
#include "res/txt.h"
#include "res.h"
#include "anime.h"

//---------------------------------------------------------------------------
ST_LV Lv;


//---------------------------------------------------------------------------
void LvInit(void)
{
	_Memset(&Lv, 0x00, sizeof(ST_LV));
}
//---------------------------------------------------------------------------
void LvDraw(void)
{
	u8 c, w;
	u8 x, y;

	for(y=0; y<LV_MAX_CY; y++)
	{
		for(x=0; x<LV_MAX_CX; x++)
		{
			c = Lv.code[x][y];
			w = Lv.wall[x][y];

			switch(c)
			{
			case '@': ResDrawChr(x, y);     break;
			case '$': ResDrawBox(x, y);     break;
			case '.': ResDrawSqu(x, y);     break;
			case '+': ResDrawChrOn(x, y);   break;
			case '*': ResDrawBoxOn(x, y);   break;
			case '#': ResDrawWall(x, y, w); break;
			case ' ': /* EMPTY */           break;

			default:
				ERROR(Lv.code[x][y]);
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------
void LvSetRes(u8 no)
{
	Lv.no = no;

	LvSetResCode();
	LvSetResWall();
}
//---------------------------------------------------------------------------
void LvSetResCode(void)
{
	u8* p = (u8*)txtLv + Lv.no * TXT_LV_BYTE;
	u8  x, y;

	for(y=0; y<LV_MAX_CY; y++)
	{
		for(x=0; x<LV_MAX_CX; x++)
		{
			Lv.code[x][y] = __LPM(p++);

			if(LvIsChr(x, y) == TRUE)
			{
				AnimeSetChr(x, y);
			}
		}
	}
}
//---------------------------------------------------------------------------
void LvSetResWall(void)
{
	const s8 tx[8] = {-1,  0,  1, -1,  1, -1,  0,  1};
	const s8 ty[8] = {-1, -1, -1,  0,  0,  1,  1,  1};

	u8 bit;
	s8 dx, dy;
	s8 x, y;
	u8 i;

	for(y=0; y<LV_MAX_CY; y++)
	{
		for(x=0; x<LV_MAX_CX; x++)
		{
			if(Lv.code[x][y] != '#')
			{
				continue;
			}

			bit = 0;

			for(i=0; i<8; i++)
			{
				dx = x + tx[i];
				dy = y + ty[i];

				// ŽÎ‚ß•ûŒü
				if(i == 0 || i == 2 || i == 5 || i == 7)
				{
					continue;
				}

				if(dx < 0 || dx >= LV_MAX_CX)
				{
					continue;
				}

				if(dy < 0 || dy >= LV_MAX_CY)
				{
					continue;
				}

				if(Lv.code[dx][dy] != '#')
				{
					continue;
				}

				bit |= 1 << i;
			}

			Lv.wall[x][y] = bit;
		}
	}
}
//---------------------------------------------------------------------------
void LvSetCode(u8 x, u8 y, u8 code)
{
	Lv.code[x][y] = code;
}
//---------------------------------------------------------------------------
void LvSetCodeTurnChr(u8 x, u8 y)
{
	switch(Lv.code[x][y])
	{
	case '@': Lv.code[x][y] = ' '; break;
	case ' ': Lv.code[x][y] = '@'; break;
	case '+': Lv.code[x][y] = '.'; break;
	case '.': Lv.code[x][y] = '+'; break;

	default:
		ERROR(Lv.code[x][y]);
		break;
	}
}
//---------------------------------------------------------------------------
void LvSetCodeTurnBox(u8 x, u8 y)
{
	switch(Lv.code[x][y])
	{
	case '$': Lv.code[x][y] = ' '; break;
	case ' ': Lv.code[x][y] = '$'; break;
	case '*': Lv.code[x][y] = '.'; break;
	case '.': Lv.code[x][y] = '*'; break;

	default:
		ERROR(Lv.code[x][y]);
		break;
	}
}
//---------------------------------------------------------------------------
u8 LvGetCode(u8 x, u8 y)
{
	return Lv.code[x][y];
}
//---------------------------------------------------------------------------
s8 LvGetNo(void)
{
	return Lv.no;
}
//---------------------------------------------------------------------------
bool LvIsBox(u8 x, u8 y)
{
	return (Lv.code[x][y] == '$' || Lv.code[x][y] == '*') ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
bool LvIsChr(u8 x, u8 y)
{
	return (Lv.code[x][y] == '@' || Lv.code[x][y] == '+') ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
bool LvIsWall(u8 x, u8 y)
{
	return (Lv.code[x][y] == '#') ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
bool LvIsClear(void)
{
	u8 x, y;

	for(y=0; y<LV_MAX_CY; y++)
	{
		for(x=0; x<LV_MAX_CX; x++)
		{
			if(Lv.code[x][y] == '$')
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}
