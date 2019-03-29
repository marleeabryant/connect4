#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include "board.h"
#include "column.h"
#include "piece.h"

struct board {
  int height;
  int width;
  int pieces;
  COLUMN **board;
};

BOARD *newBOARD() {
  BOARD *this=malloc(sizeof(BOARD));
  return this;
}

void setDims(BOARD *this, int h, int w) {
  this->board=malloc(w*sizeof(COLUMN *));
  for(int i=0;i<w;i++) {
    this->board[i]=newCOLUMN();
    setHeight(this->board[i],h);
  }
  this->height=h;
  this->width=w;
  this->pieces=0;
}

COLUMN *getCol(BOARD *this, int col) {
  return this->board[col];
}

int getPieces(BOARD *this) {
  return this->pieces;
}

void incPieces(BOARD *this) {
  this->pieces++;
}

int getHeight(BOARD *this) {
  return this->height;
}

int getWidth(BOARD *this) {
  return this->width;
}

void addPiece(BOARD *this, int col, char color) {
  int row=getOpen(getCol(this,col));
  if(row<this->height) {
    incPieces(this);
    PIECE *newP = newPIECE();
    setColor(newP,color);
    addPieceToCol(getCol(this,col),row,newP);
    incOpen(getCol(this,col));
    if(row>0) {
      //check south piece
      if(getColor(getSpace(getCol(this,col),row-1))==getColor(newP)) {
        setSouth(newP,getSpace(getCol(this,col),row-1));
        setNorth(getSpace(getCol(this,col),row-1),newP);
      }
      if(col>0) {
        //check south west piece
        if(getColor(getSpace(getCol(this,col-1),row-1))==getColor(newP)) {
          setSouthWest(newP,getSpace(getCol(this,col-1),row-1));
          setNorthEast(getSpace(getCol(this,col-1),row-1),newP);
        }
      }
      if(col<this->width-1) {
        //check south east piece
        if(getColor(getSpace(getCol(this,col+1),row-1))==getColor(newP)) {
          setSouthEast(newP,getSpace(getCol(this,col+1),row-1));
          setNorthWest(getSpace(getCol(this,col+1),row-1),newP);
        }
      }
    }
    if(col>0) {
      //check west piece
      if(getColor(getSpace(getCol(this,col-1),row))==getColor(newP)) {
        setWest(newP,getSpace(getCol(this,col-1),row));
        setEast(getSpace(getCol(this,col-1),row),newP);
      }
    }
    if(row<this->height-1) {
      //check north west piece
      if(col>0) {
        if(getColor(getSpace(getCol(this,col-1),row+1))==getColor(newP)) {
          setNorthWest(newP,getSpace(getCol(this,col-1),row+1));
          setSouthEast(getSpace(getCol(this,col-1),row+1),newP);
        }
      }
      //check north piece
      if(getColor(getSpace(getCol(this,col),row+1))==getColor(newP)) {
        setNorth(newP,getSpace(getCol(this,col),row+1));
        setSouth(getSpace(getCol(this,col),row+1),newP);
      }
      //check north east piece
      if(col<this->width-1) {
        if(getColor(getSpace(getCol(this,col+1),row+1))==getColor(newP)) {
          setNorthEast(newP,getSpace(getCol(this,col+1),row+1));
          setSouthWest(getSpace(getCol(this,col+1),row+1),newP);
        }
      }
    }
    //check east piece
    if(col<this->width-1) {
      if(getColor(getSpace(getCol(this,col+1),row))==getColor(newP)) {
        setEast(newP,getSpace(getCol(this,col+1),row));
        setWest(getSpace(getCol(this,col+1),row),newP);
      }
    }
  }
}

bool checkForWin(BOARD *this, int col) {
  int i=2;
  int j=1;
  int k=0;
  bool winner=false;
  char thisColor = getColor(getSpace(getCol(this,col),getOpen(getCol(this,col))-1));
  if(getOpen(getCol(this,col))>=4) {
    while(i<5 && thisColor==getColor(getSpace(getCol(this,col),getOpen(getCol(this,col))-i)))
      i++;
    if(i==5)
      winner=true;
  }
  i=1;
  while(!winner && i<4 && col-i>=0 && thisColor==getColor(getSpace(getCol(this,col-i),getOpen(getCol(this,col))-1)))
    i++;
  while(!winner && j<4 && col+j<this->width && thisColor==getColor(getSpace(getCol(this,col+j),getOpen(getCol(this,col))-1)))
    j++;
  if(i+j>4)
    winner=true;
  i=0;
  j=1;
  while(!winner && i<3 && j<4 && getOpen(getCol(this,col))+i<this->height && col+j<this->width && thisColor==getColor(getSpace(getCol(this,col+j),getOpen(getCol(this,col))+i))) {
    k++;
    j++;
    i++;
  }
  i=2;
  j=1;
  while(!winner && i<5 && j<4 && getOpen(getCol(this,col))-i>0 && col-j>0 && thisColor==getColor(getSpace(getCol(this,col-j),getOpen(getCol(this,col))-i))) {
    k++;
    i++;
    j++;
  }
  if(k>1)
    winner=true;
  k=0;
  i=0;
  j=1;
  while(!winner && i<3 && j<4 && getOpen(getCol(this,col))+i<this->height && col-j>0 && thisColor==getColor(getSpace(getCol(this,col-j),getOpen(getCol(this,col))+i))) {
    k++;
    i++;
    j++;
  }
  i=2;
  j=1;
  while(!winner && i<5 && j<4 && getOpen(getCol(this,col))-i>0 && col+j<this->width && thisColor==getColor(getSpace(getCol(this,col+j),getOpen(getCol(this,col))-i))) {
    k++;
    i++;
    j++;
  }
  if(k>1)
    winner=true;
  return winner;
}
