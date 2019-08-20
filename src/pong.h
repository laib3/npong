#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>
#include "consts.h"

#ifndef PONG_H
#define PONG_H

typedef struct pong *Pong;

// TODO Display logo
void print_start_menu(WINDOW *w);
void print_pause_menu(WINDOW *w);
Pong pong_init();
void pong_destroy(Pong *p);
void player_display(WINDOW *win, Pong p);
void com_display(WINDOW *win, Pong p);
void ball_display(WINDOW *win, Pong p);
void move_player_right(WINDOW *win, Pong p);
void move_player_left(WINDOW *win, Pong p);
void border_display(WINDOW *win, Pong p);
Collision update(WINDOW *win, Pong p);
void display_border_horizontal(WINDOW *win);
void display_border_vertical(WINDOW *win);
void display_points_and_lives(WINDOW *win, Pong p);
void print_game_over(WINDOW *win, Pong p);

#endif
