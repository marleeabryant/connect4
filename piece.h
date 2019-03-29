#ifndef __PIECE_INCLUDED__
#define __PIECE_INCLUDED__

#include <stdio.h>

typedef struct piece PIECE;

PIECE *newPIECE();
void setColor(PIECE *this,char color);
char getColor(PIECE *this);
PIECE *getNorth(PIECE *this);
PIECE *getNorthEast(PIECE *this);
PIECE *getEast(PIECE *this);
PIECE *getSouthEast(PIECE *this);
PIECE *getSouth(PIECE *this);
PIECE *getSouthWest(PIECE *this);
PIECE *getWest(PIECE *this);
PIECE *getNorthWest(PIECE *this);
void setNorth(PIECE *this, PIECE *that);
void setNorthEast(PIECE *this, PIECE *that);
void setEast(PIECE *this, PIECE *that);
void setSouthEast(PIECE *this, PIECE *that);
void setSouth(PIECE *this, PIECE *that);
void setSouthWest(PIECE *this, PIECE *that);
void setWest(PIECE *this, PIECE *that);
void setNorthWest(PIECE *this, PIECE *that);


#endif
