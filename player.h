#ifndef __PLAYER_INCLUDED__
#define __PLAYER_INCLUDED__

#include <stdio.h>
#include "board.h"

extern int makePlay(BOARD *this);
extern int makeFirstPlay(BOARD *this);
extern int makeDefensivePlay(BOARD *this);
extern int makeWinningPlay(BOARD *this);
extern int makeOffensivePlay(BOARD *this);
extern int makeWinningPlay(BOARD *this);

#endif
