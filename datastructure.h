#ifndef __LIST_H
#define __LIST_H
#include<ncurses.h>
typedef struct node {
	char *str;
	struct node *next, *prev;
}node;

typedef struct list {
	node *head, *tail;
	int len;
}list;
void init(list *l);
void insert(list *l, int k, int m, int cc);
void remov(WINDOW* w, list *l, int k, int m);
void reverse(list *l);
void traverse(WINDOW* ww, list *l);
void append(list *l, char *str);
void sort(list *l);
int length(list *l);
void shift(node* p, int x);
void left_shift(node* p, int x);
//void print(WINDOW* w, char* c , FILE* f) ;
void delete_line(WINDOW* w, list *l, int k, int m);
#endif
