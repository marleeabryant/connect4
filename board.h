#ifndef __BOARD_INCLUDED__
#define __BOARD_INCLUDED__

#include <stdio.h>
#include <stdbool.h>
#include "column.h"
#include "piece.h"

typedef struct board BOARD;

extern BOARD *newBOARD();
extern void setDims(BOARD *this,int h,int w);
extern COLUMN *getCol(BOARD *this, int col);
extern int getPieces(BOARD *this);
extern void incPieces(BOARD *this);
extern int getHeight(BOARD *this);
extern int getWidth(BOARD *this);
extern void addPiece(BOARD *this, int col, char color);
extern bool checkForWin(BOARD *this, int col);

#endif
