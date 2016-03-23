#ifndef ANIME_H
#define ANIME_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------
#define ANIME_MAX_MOVE_CNT			50


//---------------------------------------------------------------------------

typedef struct {
	s8   tx[ANIME_MAX_MOVE_CNT];
	s8   ty[ANIME_MAX_MOVE_CNT];
	bool isBox[ANIME_MAX_MOVE_CNT];

} ST_ANIME_MOVE;


typedef struct {
	u8   step;
	u8   stepCnt;
	s8   x;						// キャラクタの座標
	s8   y;
	s8   bx;					// ボックスの座標
	s8   by;
	s8   tx;					// 方向
	s8   ty;
	bool isBox;
	bool isEnd;

	u16  move;					// 移動カウンタ
	s8   cnt;					// 移動バッファカウンタ
	s8   cur;					// 移動バッファカーソル
	ST_ANIME_MOVE m;

} ST_ANIME;


//---------------------------------------------------------------------------
void AnimeInit(void);
void AnimeExec(void);
void AnimeExecSub(void);
void AnimeDraw(void);

void AnimeSetChr(u8 bx, u8 by);
u16  AnimeGetMoveCnt(void);

void AnimeCalcMove(s8 tx, s8 ty);
void AnimeCalcMoveU(void);
void AnimeCalcMoveD(void);
void AnimeCalcMoveL(void);
void AnimeCalcMoveR(void);

void AnimeCalcPrev(void);
void AnimeAddHistory(s8 tx, s8 ty, bool isBox);

bool AnimeIsEnd(void);


#ifdef __cplusplus
}
#endif
#endif
