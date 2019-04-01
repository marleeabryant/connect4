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
  //ncurses initialization
  initscr();
  cbreak();
  noecho();
  getmaxyx(stdscr,row,col);
  //print opening message
  attron(A_BOLD | A_STANDOUT);
  mvprintw(2,col/2,"Connect Four");
  attroff(A_STANDOUT);
  //prompt for game mode
  mvprintw(5,col/2,"Select a Game Mode");
  attroff(A_BOLD);
  mvprintw(7,col/2,"Input 1 for User v User");
  mvprintw(9,col/2,"Input 2 for User v Computer");
  refresh();
  mode=getch();
  //error check input
  while(mode!='1' && mode!='2') {
    mvprintw(11,col/2,"Error: input a 1 or a 2");
    refresh();
    mode=getch();
  }
  //enter a loop that will continue until the user wants to stop playing
  while(again) {
    win=false;
    full=false;
    //prompt for height of board
    attron(A_BOLD);
    mvprintw(13,col/2,"Input board size");
    attroff(A_BOLD);
    mvprintw(15,col/2,"Height (minimum 4, more than 40 will cause display issues): ");
    refresh();
    getstr(str);
    height=atoi(str);
    //error check input
    while(height<4||height>=INT_MAX){
      mvprintw(16,col/2,"Error: enter an integer greater than 4 for the height: ");
      refresh();
      getstr(str);
      height=atoi(str);
    }
    //prompt for width of board
    mvprintw(17,col/2,"Width (minimum 4, more than 80 will cause display issues): ");
    refresh();
    getstr(str);
    width=atoi(str);
    //error check input
    while(width<4||width>=INT_MAX){
      mvprintw(18,col/2,"Error: enter an integer greater than 4 for the width: ");
      refresh();
      getstr(str);
      width=atoi(str);
    }
    //create a new board of these dimensions
    BOARD *c4 = newBOARD();
    setDims(c4,height,width);
    //create a window to represent the board, adding lines between the rows and columns
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
    //asterick to represent column choice
    mvwaddch(board,0,2,'*');
    wrefresh(board);
    int cur=2;
    char c=getch();
    char color='R';
    int compChoice;
    //loops until win, full board, or user terminates
    while(c!='x') {
      //loops until a move is made or user termination
      while(c!='y' && c!='x') {
        //moves the column selector right
        if(c=='r') {
          if(cur<=width*2-2) {
            mvwaddch(board,0,cur,'_');
            cur=cur+2;
            mvwaddch(board,0,cur,'*');
            wrefresh(board);
          }
          c=getch();
        }
        //moves the column selector left
        else if(c=='l') {
          if(cur>=4) {
            mvwaddch(board,0,cur,'_');
            cur=cur-2;
            mvwaddch(board,0,cur,'*');
            wrefresh(board);
          }
          c=getch();
        }
        //error check input
        while(c!='y' && c!='x' && c!='r' && c!='l')
          c=getch();
      }
      //when user chooses a column
      if(c=='y') {
        //gets the next open space in the column
        int open=getOpen(getCol(c4,cur/2-1));
        if(open<height) {
          //adds a piece and the character representation in the window
          addPiece(c4,cur/2-1,color);
          mvwaddch(board,height-open,cur,color);
          wrefresh(board);
          //checks for a win
          win = checkForSeries(c4,cur/2-1,4);
          //increments the winning players score
          if(win) {
            if(color=='R')
              rScore++;
            else
              bScore++;
            c='x';
          }
          //checks if the board is full
          else if(getPieces(c4)==getHeight(c4)*getWidth(c4)) {
             full=true;
             c='x';
          }
          //switches player if in player v player mode
          else if(mode=='1') {
            c=getch();
            if(color=='R')
              color='B';
            else if(color=='B')
              color='R';
          }
          //initiates the computers move if in player v computer mode
          else {
            //computer picks a column
            compChoice=makePlay(c4);
            open=getOpen(getCol(c4,compChoice));
            addPiece(c4,compChoice,'B');
            mvwaddch(board,height-open,(compChoice+1)*2,'B');
            wrefresh(board);
            win = checkForSeries(c4,compChoice,4);
            if(win) {
              bScore++;
              color='B';
              c='x';
            }
            else if(getPieces(c4)==getHeight(c4)*getWidth(c4)) {
               full=true;
               c='x';
            }
            else
              c=getch();
          }
        }
        else
          c=getch();
      }
      while(c!='y' && c!='x' && c!='r' && c!='l')
        c=getch();
    }
    //clears the window and frees the board
    wclear(board);
    wrefresh(board);
    delwin(board);
    freeBOARD(c4);
    //prints winning message
    if(win) {
      mvprintw(19,col/2,"Player %c won!                   ",color);
      mvprintw(21,col/2,"R has won %d games and B has won %d games",rScore,bScore);
    }
    //prints tie message
    if(full) {
      mvprintw(19,col/2,"The board is full it's a tie!");
      mvprintw(21,col/2,"R has won %d games and B has won %d games",rScore,bScore);
    }
    //prompts for playing again
    mvprintw(23,col/2,"Play again(y/n)?");
    refresh();
    //error check
    while(c!='y'&&c!='n') {
      c=getch();
    }
    if(c=='n')
      again=false;
  }
  free(str);
  endwin();
}
