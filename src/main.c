/*                                      *
 *    PONG 2019                         *
 *    Author: laib3                     *
 *    Date: 2019-08-18 / 2019-08-20     *
 *                                      */

#include <ncurses.h>
#include <unistd.h>
#include "pong.h"
#include "consts.h"

int main(int argc, char **argv){
  
  // Variables
  State state = START_MENU;
  Pong p;
  int input;
  int flag = 0;
  int ball_time = 0;
  Collision collision = HIT;

  // Init screen
  initscr();
  // Different windows, so they can be refreshed separately
  WINDOW *board = newwin(ROWS-2, COLS, BEG_ROW+1, BEG_COL);
  WINDOW *wplayer = newwin(1, COLS, END_ROW, BEG_COL);
  WINDOW *wcom = newwin(1, COLS, BEG_ROW, BEG_COL);
  WINDOW *wup = newwin(1, COLS+2, BEG_ROW-1, BEG_COL-1);
  WINDOW *wdown = newwin(1, COLS+2, BEG_ROW+ROWS, BEG_COL-1);
  WINDOW *wleft = newwin(ROWS, 1, BEG_ROW, BEG_COL-1);
  // WINDOW *wright = newwin(ROWS, 1, BEG_ROW, BEG_COL + COLS);
  WINDOW *wpoints = newwin(ROWS+2, WPOINTS, BEG_ROW-1, BEG_COL+COLS);

  noecho();
  cbreak();
  curs_set(FALSE);
  nodelay(stdscr, TRUE);
  nodelay(board, TRUE);
  keypad(stdscr, TRUE);

  while(state!=QUIT){
    switch (state){
      case QUIT: 
        pong_destroy(&p);
        break;
      case START_MENU: 
        p = pong_init();
        nodelay(board, FALSE);
        werase(board);
        print_start_menu(board);
        wrefresh(board);
        // Display borders
        border_display(wpoints, p);
        wrefresh(wpoints);
        display_border_horizontal(wup);
        display_border_horizontal(wdown);
        display_border_vertical(wleft);
        // display_border_vertical(wright);
        wrefresh(wleft);
        // wrefresh(wright);
        wrefresh(wup);
        wrefresh(wdown);
        input = getch();
        usleep(TIME);
        if(input=='q'||input=='Q') state = QUIT;
        if(input=='s'||input=='S') state = IN_GAME;
        if(input=='p'||input=='P') state = PAUSE;
        break;
      case PAUSE: 
        nodelay(stdscr, FALSE);
        werase(board);
        print_pause_menu(board);
        wrefresh(board);
        input = getch();
        if(input=='q' || input=='Q') state = QUIT;
        if(input=='s'||input=='S') state = IN_GAME;
        break;
      case IN_GAME:
        collision=HIT;
        nodelay(board, TRUE);
        nodelay(stdscr, TRUE);
        // Every 10*TIME, the ball changes position
        // so, meanwhile, the player can move its pad
        if(ball_time==TIME*10){
          collision = update(board, p);
          werase(board);
          ball_display(board, p);
          wrefresh(board);
          werase(wpoints);
          border_display(wpoints, p);
          display_points_and_lives(wpoints, p);
          wrefresh(wpoints);
          ball_time = 0;
        }
        werase(wplayer);
        werase(wcom);
        player_display(wplayer, p);
        com_display(wcom, p);
        wrefresh(wcom);
        wrefresh(wplayer);
        input=getch();
        usleep(TIME);
        ball_time = ball_time+TIME;
        // Manage user's input
        if(input!=ERR){
          switch(input){
            case 'q': 
              state=QUIT; break;    
            case 'Q': 
              state=QUIT; break;
            case 'l':
              move_player_right(wplayer, p); break;
            case 'h': 
              move_player_left(wplayer, p); break;
            case KEY_RIGHT:
              move_player_right(wplayer, p); break;
            case KEY_LEFT:
              move_player_left(wplayer, p); break;
            case '\n':
              state=PAUSE; break;
          }
        }
        flag = 1;
        if(collision==MISS) {
          sleep(1);
          state=IN_GAME;
        }
        if(collision==POINT) {
           sleep(1);
           state=IN_GAME;
         }
        if(collision==GAME_OVER) state=GAME_OVER;
        break;
      case GAME_OVER:
        werase(board);
        print_game_over(board, p);
        wrefresh(board);
        sleep(2);
        state=START_MENU;
        break;
    }
  }
  // Close
  delwin(wcom);
  delwin(wplayer);
  delwin(wup);
  delwin(wdown);
  delwin(wpoints);
  delwin(board);
  endwin();
}
