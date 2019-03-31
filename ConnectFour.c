#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ncurses.h>
#include "piece.h"
#include "column.h"
#include "board.h"
#include "player.h"

const int INT_MAX =2147483647;

int main(void) {
  int row,col;
  int mode,height,width;
  char *str = malloc(sizeof(char *));
  bool win = false;
  bool again = true;
  bool full = false;
  int rScore=0;
  int bScore=0;

  initscr();
  cbreak();
  noecho();
  getmaxyx(stdscr,row,col);

  attron(A_BOLD | A_STANDOUT);
  mvprintw(2,col/2,"Connect Four");
  attroff(A_STANDOUT);
  mvprintw(5,col/2,"Select a Game Mode");
  attroff(A_BOLD);
  mvprintw(7,col/2,"Input 1 for User v User");
  mvprintw(9,col/2,"Input 2 for User v Computer");
  refresh();
  mode=getch();
  while(mode!='1' && mode!='2') {
    mvprintw(11,col/2,"Error: input a 1 or a 2");
    refresh();
    mode=(int)getch();
  }
  while(again) {
    win=false;
    full=false;
    attron(A_BOLD);
    mvprintw(13,col/2,"Input board size");
    attroff(A_BOLD);
    mvprintw(15,col/2,"Height (minimum 4, more than 40 will cause display issues): ");
    refresh();
    getstr(str);
    height=atoi(str);
    while(height<4||height>=INT_MAX){
      mvprintw(16,col/2,"Error: enter an integer greater than 4 for the height: ");
      refresh();
      getstr(str);
      height=atoi(str);
    }
    mvprintw(17,col/2,"Width (minimum 4, more than 80 will cause display issues): ");
    refresh();
    getstr(str);
    width=atoi(str);
    while(width<4||width>=INT_MAX){
      mvprintw(18,col/2,"Error: enter an integer greater than 4 for the width: ");
      refresh();
      getstr(str);
      width=atoi(str);
    }

    BOARD *c4 = newBOARD();
    setDims(c4,height,width);

    WINDOW *board = newwin(height+1,width*2+2,0,0);
    for(int j=0;j<height+1;j++) {
      mvwvline(board,j,1,'|',1);
    }
    for(int i=2;i<width*2+2;i=i+2) {
      for(int j=0;j<height+1;j++){
        mvwhline(board,j,i,'_',1);
        mvwvline(board,j,i+1,'|',1);
      }
    }

    mvwaddch(board,0,2,'*');
    wrefresh(board);
    int cur=2;
    char c=getch();
    char color='R';

    while(c!='x') {
      while(c!='y' && c!='x') {
        if(c=='r') {
          if(cur<=width*2-2) {
            mvwaddch(board,0,cur,'_');
            cur=cur+2;
            mvwaddch(board,0,cur,'*');
            wrefresh(board);
          }
          c=getch();
        }
        else if(c=='l') {
          if(cur>=4) {
            mvwaddch(board,0,cur,'_');
            cur=cur-2;
            mvwaddch(board,0,cur,'*');
            wrefresh(board);
          }
          c=getch();
        }
        while(c!='y' && c!='x' && c!='r' && c!='l')
          c=getch();
      }
      if(c=='y') {
        int open=getOpen(getCol(c4,cur/2-1));
        if(open<height) {
          addPiece(c4,cur/2-1,color);
          mvwaddch(board,width-open,cur,color);
          wrefresh(board);
          win = checkForWin(c4,cur/2-1);
          if(win) {
            if(color=='R')
              rScore++;
            else
              bScore++;
            c='x';
          }
          else if(getPieces(c4)==getHeight(c4)*getWidth(c4)) {
             full=true;
             c='x';
          }
          else if(mode=='1') {
            c=getch();
            if(color=='R')
              color='B';
            else if(color=='B')
              color='R';
          }
          else
            makePlay(c4);
        }
        else
          c=getch();
      }
      while(c!='y' && c!='x' && c!='r' && c!='l')
        c=getch();
    }
    wclear(board);
    wrefresh(board);
    delwin(board);
    if(win) {
      mvprintw(19,col/2,"Player %c won!                   ",color);
      mvprintw(21,col/2,"R has won %d games and B has won %d games",rScore,bScore);
    }
    if(full) {
      mvprintw(19,col/2,"The board is full it's a tie!",color);
      mvprintw(21,col/2,"R has won %d games and B has won %d games",rScore,bScore);
    }
    mvprintw(23,col/2,"Play again(y/n)?");
    refresh();
    while(c!='y'&&c!='n') {
      c=getch();
    }
    if(c=='n')
      again=false;
  }

  endwin();
}
