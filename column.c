#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
#include "column.h"

struct column {
  int height;
  //holds the index of the next open space in the column
  int open;
  PIECE **column;
};

COLUMN *newCOLUMN() {
  COLUMN *this = malloc(sizeof(COLUMN));
  this->open = 0;
  return this;
}

void setHeight(COLUMN *this,int h) {
  this->height=h;
  this->column = malloc(h*sizeof(PIECE *));
  for(int i=0;i<h;i++)
    this->column[i] = newPIECE();
}

int getOpen(COLUMN *this) {
  return this->open;
}

PIECE *getSpace(COLUMN *this,int row) {
  return this->column[row];
}

void addPieceToCol(COLUMN *this,int row,PIECE *newP) {
  this->column[row]=newP;
}

void removePieceFromCol(COLUMN *this,int row) {
  //inputs a colorless, pointerless piece to take the place of one that was removed
  PIECE *filler=newPIECE();
  this->column[row]=filler;
}

void incOpen(COLUMN *this) {
  this->open++;
}

void decOpen(COLUMN *this) {
  this->open--;
}

void freeCOLUMN(COLUMN *this) {
  for(int i=0;i<this->height;i++)
    freePIECE(this->column[i]);
  free(this->column);
  free(this);
}
