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
  //holds a count of the number of pieces in the board
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
  //gets the index of the next open space in the given column
  int row=getOpen(getCol(this,col));
  //makes sure the column is not full
  if(row<this->height) {
    incPieces(this);
    PIECE *newP = newPIECE();
    setColor(newP,color);
    addPieceToCol(getCol(this,col),row,newP);
    incOpen(getCol(this,col));
    //checks all of the pieces around the new piece to create a graph between
    //this piece and pieces of the same color
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
  int i=0;
  bool winner=false;
  //gets the value of the most recently inserted piece
  PIECE *thisPiece = getSpace(getCol(this,col),getOpen(getCol(this,col))-1);
  //checks below this piece to look for 4 in a row vertically
  while(i<3 && getSouth(thisPiece)!=NULL) {
    i++;
    thisPiece=getSouth(thisPiece);
  }
  if(i>=3)
    winner=true;
  i=0;
  thisPiece = getSpace(getCol(this,col),getOpen(getCol(this,col))-1);
  //checks to the left of the piece
  while(i<3 && getEast(thisPiece)!=NULL) {
    i++;
    thisPiece=getEast(thisPiece);
  }
  thisPiece = getSpace(getCol(this,col),getOpen(getCol(this,col))-1);
  //checks to the right of the piece
  while(i<3 && getWest(thisPiece)!=NULL) {
    i++;
    thisPiece=getWest(thisPiece);
  }
  //if there are enough pieces on the left and right combined, finds a horizontal win
  if(i>=3)
    winner=true;
  i=0;
  thisPiece = getSpace(getCol(this,col),getOpen(getCol(this,col))-1);
  //checks the north east diagonal
  while(i<3 && getNorthEast(thisPiece)!=NULL) {
    i++;
    thisPiece=getNorthEast(thisPiece);
  }
  thisPiece = getSpace(getCol(this,col),getOpen(getCol(this,col))-1);
  //checks the south west diagonal
  while(i<3 && getSouthWest(thisPiece)!=NULL) {
    i++;
    thisPiece=getSouthWest(thisPiece);
  }
  if(i>=3)
    winner=true;
  i=0;
  thisPiece = getSpace(getCol(this,col),getOpen(getCol(this,col))-1);
  //checks the north west diagonal
  while(i<3 && getNorthWest(thisPiece)!=NULL) {
    i++;
    thisPiece=getNorthWest(thisPiece);
  }
  thisPiece = getSpace(getCol(this,col),getOpen(getCol(this,col))-1);
  //checks the south east diagonal
  while(i<3 && getSouthEast(thisPiece)!=NULL) {
    i++;
    thisPiece=getSouthEast(thisPiece);
  }
  //if the north west and south east have enough pieces combined, finds a diagonal win
  if(i>=3)
    winner=true;
  return winner;
}
