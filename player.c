#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "player.h"
#include "board.h"
#include "piece.h"
#include "column.h"

int makePlay(BOARD *this) {
  int col;
  //checks if the computer has any pieces to play off of
  if(getPieces(this)<2)
    col = makeFirstPlay(this);
  else {
    //determines if there is a winning play or a necessary defensive play to avoid losing
    int winner = makeWinningPlay(this);
    int defense = makeDefensivePlay(this);
    if(winner>=0)
      col=winner;
    else if(defense>=0)
      col=defense;
    //if neither, then the computer just makes the most advantageous play by looking one step ahead
    else
      col = makeOffensivePlay(this);
  }
  return col;
}

int makeFirstPlay(BOARD *this) {
  //chooses one of the middle columns to begin play in
  int w = getWidth(this);
  int space;
  if(getColor(getSpace(getCol(this,w/2),0))!='R')
    space= w/2;
  else
    space= w/2-1;
  return space;
}

int makeWinningPlay(BOARD *this) {
  int winner=-1;
  //temporarily places a piece in each column of the board to see if it will result in a win
  for(int i=0;i<getWidth(this);i++) {
    if(getOpen(getCol(this,i))<getHeight(this)) {
      addPiece(this,i,'B');
      if(checkForSeries(this,i,4))
        winner=i;
      //the piece is removed so as not to affect further game play
      removePiece(this,i);
    }
  }
  return winner;
}

int makeDefensivePlay(BOARD *this) {
  int block=-1;
  //temporarily places an opponent piece in each column of the board to see if it will result in a win
  //it will be blocked if so
  for(int i=0;i<getWidth(this);i++) {
    if(getOpen(getCol(this,i))<getHeight(this)) {
      addPiece(this,i,'R');
      if(checkForSeries(this,i,4))
          block=i;
      removePiece(this,i);
    }
  }
  return block;
}

int makeOffensivePlay(BOARD *this) {
  //holds the priority of placing a piece in each column
  int *values=malloc(getWidth(this)*sizeof(int));
  //intialized to 0 so unplayable columns will have lowest priority
  for(int i=0;i<getWidth(this);i++) {
    values[i]=0;
  }
  for(int i=0;i<getWidth(this);i++) {
    //checks if the column is full
    if(getOpen(getCol(this,i))<getHeight(this)) {
      //temporarily places a piece in each column of the board to see determine how advantageous this play would be
      addPiece(this,i,'B');
      //if it would result in 3 in a row it is assigned a priority of 3
      if(checkForSeries(this,i,3))
        values[i]=3;
      //if it would result in 2 in a row it is assigned a priority of 2
      else if(checkForSeries(this,i,2))
        values[i]=2;
      //otherwise, it is assigned a priority of 1
      else
        values[i]=1;
      removePiece(this,i);
    }
  }
  int maxIndex=0;
  //determines which column has the greatest priority
  for(int i=1;i<getWidth(this);i++) {
    if(values[i]>values[maxIndex])
      maxIndex=i;
  }
  free(values);
  return maxIndex;
}
