#ifndef __COLUMN_INCLUDED__
#define __COLUMN_INCLUDED__

#include <stdio.h>
#include "piece.h"

typedef struct column COLUMN;

extern COLUMN *newCOLUMN();
extern void setHeight(COLUMN *,int h);
extern int getOpen(COLUMN *);
extern PIECE *getSpace(COLUMN *this,int row);
extern void addPieceToCol(COLUMN *this,int row,PIECE *newP);
extern void removePieceFromCol(COLUMN *this, int row);
extern void incOpen(COLUMN *this);
extern void decOpen(COLUMN *this);
extern void freeCOLUMN(COLUMN *this);

#endif
