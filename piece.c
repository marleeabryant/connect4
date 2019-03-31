#include <stdio.h>
#include <stdlib.h>
#include "piece.h"

struct piece {
  char color;
  //pointers to all of the spaces around the piece on the board
  PIECE *north;
  PIECE *northEast;
  PIECE *east;
  PIECE *southEast;
  PIECE *south;
  PIECE *southWest;
  PIECE *west;
  PIECE *northWest;
};

PIECE *newPIECE() {
  PIECE* this=malloc(sizeof(PIECE));
  this->north=NULL;
  this->northEast=NULL;
  this->east=NULL;
  this->southEast=NULL;
  this->south=NULL;
  this->southWest=NULL;
  this->west=NULL;
  this->northWest=NULL;
  this->color='N';
  return this;
}

void setColor(PIECE *this,char color) {
  this->color=color;
}

char getColor(PIECE *this) {
  return this->color;
}

PIECE *getNorth(PIECE *this) {
  return this->north;
}

PIECE *getNorthEast(PIECE *this) {
  return this->northEast;
}

PIECE *getEast(PIECE *this) {
  return this->east;
}

PIECE *getSouthEast(PIECE *this) {
  return this->southEast;
}

PIECE *getSouth(PIECE *this) {
  return this->south;
}

PIECE *getSouthWest(PIECE *this) {
  return this->southWest;
}

PIECE *getWest(PIECE *this) {
  return this->west;
}

PIECE *getNorthWest(PIECE *this) {
  return this->northWest;
}

void setNorth(PIECE *this, PIECE *that) {
  this->north = that;
}

void setNorthEast(PIECE *this, PIECE *that) {
  this->northEast = that;
}

void setEast(PIECE *this, PIECE *that) {
  this->east = that;
}

void setSouthEast(PIECE *this, PIECE *that) {
  this->southEast = that;
}

void setSouth(PIECE *this, PIECE *that) {
  this->south = that;
}

void setSouthWest(PIECE *this, PIECE *that) {
  this->southWest = that;
}

void setWest(PIECE *this, PIECE *that) {
  this->west = that;
}

void setNorthWest(PIECE *this, PIECE *that) {
  this->northWest = that;
}
