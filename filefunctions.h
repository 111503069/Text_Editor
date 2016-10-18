#ifndef __FILE_H
#define __FILE_H
#include<ncurses.h>
#include "datastructure.h"
void print(WINDOW* w, list *l) ;
void open(WINDOW* w, char* c ,list *l);
void save(list *l, char* c);
#endif
