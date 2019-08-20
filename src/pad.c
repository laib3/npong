#include "pad.h"
#include "consts.h"

typedef struct pad{
  int pos;
  int length;
} pad;

typedef pad *Pad;

Pad pad_init(){
  Pad p = (Pad)malloc(sizeof(pad));
  p->pos = PAD_POS;
  p->length= PAD_LEN;
  return p;
}

void pad_destroy(Pad p){
  if(p!=NULL){
    free(p);
  }
}

int get_length(Pad p){
  return p -> length;
}

int get_end(Pad p){
  return p -> pos + p -> length;
}

int get_pos(Pad p){
  return p->pos;
}

void set_pos(Pad p, int value){
  p->pos = value;
}

void set_length(Pad p, int value){
  p->length = value;
}

void move_left(Pad p){
  p->pos--;
}

void move_right(Pad p){
  p->pos++;
}


/* note: this functions are not in pad.h, maybe they will be useful
 * later */
void move_left_amt(Pad p, int amt){
  p->pos = p->pos-amt;
}

void move_right_amt(Pad p, int amt){
  p->pos = p->pos+amt;
}
