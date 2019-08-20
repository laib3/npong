#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct pad* Pad;

Pad pad_init();
void pad_destroy(Pad p);
int get_length(Pad p);
int get_end(Pad p);
int get_pos(Pad p);
void set_pos(Pad p, int value);
void set_length(Pad p, int value);
void move_left(Pad p);
void move_right(Pad p);
