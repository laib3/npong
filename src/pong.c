#include "pong.h"
#include "ball.h"
#include "pad.h"
#include "consts.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct pong{
  Pad player;
  Pad com;
  Ball ball;
  int points;
  int lives;
} pong;

typedef struct pong *Pong;


// And press enter to begin
void print_start_menu(WINDOW *win){
  int center = getmaxx(win)/2 -1;
  char str[30];
  strcpy(str, "Welcome to PONG");
  int begin = center - (strlen(str) / 2 );
  mvwprintw(win, 5, begin, "Welcome to PONG");
  strcpy(str, "Press S to start");
  begin = center - (strlen(str) / 2 );
  mvwprintw(win, 7, begin, str);
  strcpy(str, "Press Q to quit");
  begin = center - (strlen(str) / 2);
  mvwprintw(win, 8, begin, str);
  strcpy(str, "Press ENTER to pause");
  begin = center - (strlen(str)/2);
  mvwprintw(win, 9, begin, str);
  strcpy(str, "Use arrows to move (or h, l)");
  begin = center - (strlen(str) / 2);
  mvwprintw(win, 10, begin, str);
}

void print_pause_menu(WINDOW *win){
  char str[30];
  strcpy(str, "PAUSE");
  mvwprintw(win, getmaxy(win)/2-3, getmaxx(win)/2-strlen(str)/2, str);
  strcpy(str, "Q to quit");
  mvwprintw(win, getmaxy(win)/2-1, getmaxx(win)/2-strlen(str)/2, str);
  strcpy(str, "S to back to the game");
  mvwprintw(win, getmaxy(win)/2, getmaxx(win)/2-strlen(str)/2, str);
  return;  
}

void print_game_over(WINDOW *win, Pong p){
  char str[30] = "GAME OVER";
  mvwprintw(win, getmaxy(win)/2, (getmaxx(win)/2)-(strlen(str)/2), str);
  return;
}

Pong pong_init(){
  Pong p = malloc(sizeof(pong));
  p->ball = ball_init();
  p->player = pad_init();
  p->com = pad_init();
  p->points = 0;
  p->lives = LIVES;
  return p;
}

void pong_destroy(Pong *p){
  pad_destroy((*p)->player);
  pad_destroy((*p)->com);
  ball_destroy((*p)->ball);
  free((*p));
  return;
}

void move_player_left(WINDOW *win, Pong p){
  if(get_pos(p->player)>0)
    move_left(p->player);
}
  
void move_player_right(WINDOW *win, Pong p){
  if(get_pos(p->player)<getmaxx(win)-get_length(p->player))
    move_right(p->player);
}

void player_display(WINDOW *win, Pong p){
  int x = get_pos(p->player);
  int len = get_length(p->player);
  for(int i=x; i<x+len; i++){
    mvwprintw(win, 0, i, "#");
  }
  return;
}

// Could have used a flag to choose between player and com, 
// but doesn't matter
void com_display(WINDOW *win, Pong p){
  int x = get_pos(p->com);
  int len = get_length(p->com);
  for(int i=x; i<x+len; i++){
    mvwprintw(win, 0, i, "#");
  }
  return;
}

void ball_display(WINDOW *win, Pong p){
  mvwprintw(win, get_y(p->ball), get_x(p->ball), "@");  
}


Collision update(WINDOW *win, Pong p){
  // Sometimes it generates a new random seed
  if(get_pos(p->com)%6){
    srand(get_pos(p->player));
  }
  // Update ball's position
  set_x(p->ball, get_x(p->ball) + get_dir_x(p->ball));
  set_y(p->ball, get_y(p->ball) + get_dir_y(p->ball));
  // Update com's pad:
  // If the ball is next to the com's pad, the pad surely moves
  // if the ball is far from the com's pad, maybe the pad won't move
  if(get_x(p->ball) > get_pos(p->com)+(get_length(p->com)/2) && rand()%2 && get_pos(p->com)<getmaxx(win)-get_length(p->com) && get_y(p->ball)>getmaxy(win)/2){
    move_right(p->com);
  }
  else if(get_x(p->ball) > get_pos(p->com)+(get_length(p->com)/2) && get_pos(p->com)<getmaxx(win)-get_length(p->com) && get_y(p->ball)<=(float)getmaxy(win)/2){
    move_right(p->com);
  }
  if(get_x(p->ball) < get_pos(p->com)+(get_length(p->com)/2) && rand()%2 && get_pos(p->com)>0 && get_y(p->ball)>getmaxy(win)/2){
    move_left(p->com);
  }
  else if(get_x(p->ball) < get_pos(p->com)+(get_length(p->com)/2) && get_pos(p->com)>0 && get_y(p->ball)<=(float)getmaxy(win)/2){
    move_left(p->com);
  }
  // Left - Detect player collision
  if(get_y(p->ball)==getmaxy(win)-1){
    if(get_x(p->ball)>=get_pos(p->player)-1 && get_x(p->ball)<get_pos(p->player)+(get_length(p->player))/2+1)
      set_dir_x(p->ball, -1);
    else if(get_x(p->ball)>=get_pos(p->player)+(get_length(p->player)/2) && get_x(p->ball)<=get_pos(p->player)+get_length(p->player))
      set_dir_x(p->ball, 1);
    else {
      set_dir_y(p->ball, -1);
      if(p->lives>0) {
        p->lives--;
        // the ball is respawned in another place
        set_x(p->ball, rand()%getmaxx(win));
        return MISS;
      }
      else{
        p->lives = LIVES;
        return GAME_OVER;
      }
    }
    set_dir_y(p->ball, -1);
  }
  // Up
  if(get_y(p->ball)==0 && get_dir_y(p->ball)==-1){
    set_dir_y(p->ball, 1);
    if(get_x(p->ball)>=get_pos(p->com)-1 && get_x(p->ball)<=get_pos(p->com)+get_length(p->com)+1){
      set_dir_y(p->ball, 1);
    }
    else{
      // If the com has miss
      set_dir_y(p->ball, 1);
      set_x(p->ball, rand()%getmaxx(win));
      p->points++;
      return POINT;
    }
  }
  // Left 
  if(get_x(p->ball)==0 && get_dir_x(p->ball)==-1)
    set_dir_x(p->ball, 1);
  // Right 
  if(get_x(p->ball)==getmaxx(win)-1 && get_dir_x(p->ball)==1)
    set_dir_x(p->ball, -1);

  return HIT;
}

void display_border_horizontal(WINDOW *win){
  for(int i=0; i<COLS+2; i++){
    mvwprintw(win, 0, i, "-");
  }
  mvwprintw(win, 0, 0, "+");
  mvwprintw(win, 0, getmaxx(win)-1, "+");
}

void display_border_vertical(WINDOW *win){
  for(int i=0; i<ROWS; i++){
    mvwprintw(win, i, 0, "|");
  }
}

// This draws a border around the entire window
void border_display(WINDOW *win, Pong p){
  for(int i=0; i<getmaxy(win); i++){
    for(int j=0; j<getmaxx(win); j++){
      if(i==0 || i==getmaxy(win)-1){
        mvwprintw(win, i, j, "-");
      }
      if(j==0 || j==getmaxx(win)-1){
        mvwprintw(win, i, j, "|");
      }
    }
  }
  mvwprintw(win, 0, 0, "+");
  mvwprintw(win, 0, getmaxx(win)-1, "+");
  mvwprintw(win, getmaxy(win)-1, 0, "+");
  mvwprintw(win, getmaxy(win)-1, getmaxx(win)-1, "+");
}

void display_points_and_lives(WINDOW *win, Pong p){
  char str[20];
  strcpy(str, "POINTS:   ");
  mvwprintw(win, getmaxy(win)/2-1, (getmaxx(win)/2)-(strlen(str)/2), "POINTS: %d", p->points);
  mvwprintw(win, getmaxy(win)/2, (getmaxx(win)/2)-(strlen(str)/2), "LIVES: ", p->lives);
  strcpy(str, "LIVES: ");
  for(int i=0; i<p->lives; i++){
    mvwprintw(win, getmaxy(win)/2, (getmaxx(win)/2)+(strlen(str)/2)+i, "@");
  }
}

