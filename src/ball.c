#include <stdio.h>
#include <stdlib.h>
#include "ball.h"

typedef struct bll{
  int x;
  int y; 
  int dir_x;
  int dir_y;
} ball;

// Note: y calculated from the top of the window

typedef ball *Ball;

Ball ball_init(){
  Ball b = (Ball)malloc(sizeof(ball));
  b -> x = 0;
  b -> y = 0;
  b -> dir_x = 1;
  b -> dir_y = 1;
  return b;
}

void ball_destroy(Ball b){
  if(b!=NULL){
    free(b);
  }
  return;
}

void set_x(Ball b, int val){
  b -> x = val;
}

void set_y(Ball b, int val){
  b -> y = val;
}

void set_xy(Ball b, int x, int y){
  b->x = x;
  b->y = y;
}

void set_dir_x(Ball b, int dir){
  b -> dir_x = dir;
}
 
void set_dir_y(Ball b, int dir){
  b -> dir_y = dir;
}

void get_xy(Ball b, int *x, int *y){
  *x = b->x;
  *y = b->y;
}

int get_x(Ball b){
  return b -> x;
}

int get_y(Ball b){
  return b -> y;
}

int get_dir_x(Ball b){
  return b->dir_x;
}

int get_dir_y(Ball b){
  return b->dir_y;
}
