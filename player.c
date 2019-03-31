#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "player.h"
#include "board.h"
#include "piece.h"
#include "column.h"

int makePlay(BOARD *this) {
  int col;
  if(getPieces(this)<2)
    col = makeFirstPlay(this);
  else {
    int defense = makeDefensivePlay(this);
    if(defense>=0)
      col=defense;
    else
      col = makeOffensivePlay(this);
  }
  return col;
}

int makeFirstPlay(BOARD *this) {
  int w = getWidth(this);
  int space;
  if(getColor(getSpace(getCol(this,w/2),0))!='R')
    space= w/2;
  else
    space= w/2-1;
  return space;
}

int makeDefensivePlay(BOARD *this) {
  for(int i=0;i<getWidth(this);i++) {
    if(getOpen(getCol(this,i))<getHeight(this)) {
      addPiece(this,i,'R');
      if(checkForSeries(this,i,4))
          return i;
      removePiece(this,i);
    }
  }
  return -1;
}

int makeOffensivePlay(BOARD *this) {
  int *values=malloc(getWidth(this)*sizeof(int));
  for(int i=0;i<getWidth(this);i++) {
    values[i]=0;
  }
  for(int i=0;i<getWidth(this);i++) {
    if(getOpen(getCol(this,i))<getHeight(this)) {
      addPiece(this,i,'B');
      if(checkForSeries(this,i,4))
        return i;
      else if(checkForSeries(this,i,3))
        values[i]=3;
      else if(checkForSeries(this,i,2))
        values[i]=2;
      else
        values[i]=1;
      removePiece(this,i);
    }
  }
  int maxIndex=0;
  for(int i=1;i<getWidth(this);i++) {
    if(values[i]>values[maxIndex])
      maxIndex=i;
  }
  return maxIndex;
}
