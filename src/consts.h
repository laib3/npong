#ifndef CONST
#define CONST

#define BEG_COL 1
#define BEG_ROW 1
#define ROWS    20
#define COLS    60
#define PAD_LEN 10
#define PAD_POS (COLS-BEG_COL)/2-(PAD_LEN)
#define TIME    10000
#define LIVES   3
#define END_ROW BEG_ROW+ROWS-1
#define END_COL BEG_COL+COLS-1
#define WPOINTS 15

typedef enum {
  QUIT, START_MENU, IN_GAME, PAUSE, GAME_OVER
} State;

typedef enum {
  HIT, MISS, POINT
} Collision;

#endif
