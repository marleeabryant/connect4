#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
#include "column.h"

struct column {
  int height;
  int open;
  PIECE **column;
};

COLUMN *newCOLUMN() {
  COLUMN *this = malloc(sizeof(COLUMN));
  this->open = 0;
  return this;
}

void setHeight(COLUMN *this,int h) {
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

void incOpen(COLUMN *this) {
  this->open++;
}
