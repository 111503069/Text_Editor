#ifndef __FILE_H
#define __FILE_H
#include<ncurses.h>
#include "datastructure.h"
void print(WINDOW* menu, WINDOW* w, list *l, char* c) ;
void open(WINDOW* w, char* c ,list *l);
void save(list *l, char* c);
void paste(list *l, int k, int m, char *str);
char* copy(list *l, int k, int m, int clx, int cly);
void cut(WINDOW* ww, list *l, int k, int m, int clx, int cly);
void stringreplace (WINDOW* menu, WINDOW* ww, list *l, char *orig, char *new);
void no_name(char* file_name, WINDOW* menu);
void print_menu(WINDOW* menu);
void help(char* str);
#endif
