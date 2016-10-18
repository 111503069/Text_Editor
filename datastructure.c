#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include<ncurses.h>
void init(list *l){
    l->head = l->tail = NULL;
    l->len = 0;
}
void insert(list *l, int k, int m,int cc){
    node *tmp, *p;
    int n;
    int i;
    if((l->head == NULL )|| cc == '\n' ) {
        tmp = (node *)malloc(sizeof(node));
        tmp->str = (char*)malloc(256);
        for(i = 0; i < 256; i++) {
            (tmp->str)[i] = '\0';
        }
    //strcpy(tmp->str, str);
        tmp->prev = NULL;
        tmp->next = NULL;
    /* handle first node case separately */
        if(l->head == NULL) {
            tmp->next = tmp->prev = NULL;
            l->head = l->tail = tmp;
            l->len++;
            (l->head->str)[k] = cc;
            //(l->head->str)[x+1] = '\0';
            return;
        }
    /* link the new node on the list at appropriate position*/
        p = l->head;
        for(i = 0; i < m-1; i++)
            p = p->next;
        
        if(m == 0) {
            tmp->next = p;
            p->prev = tmp;
            l->head = tmp;
        }
        else if(m == l->len) {
            p->next = tmp;
            tmp->prev = p;
            l->tail = tmp;
        
        }
        else {
            tmp->next = p->next;
            tmp->prev = p;
            p->next->prev = tmp;
            p->next = tmp;
        }
        if(cc == '\n') {
            //p = p->next;
            if((p->str)[k] != '\0')
                shift(p, k);
            (p->str)[k] = cc;
            strcpy(p->next->str, (p->str) + k + 1);
            for(i = k + 1; i < 256; i++) {
                (p->str)[i] = '\0';
            }

        }
        l->len++;
    }
    else {
        p = l->head;
        for(i = 0; i < m; i++)
            p = p->next;
        /*if(k%127 == 0 ) {
            realloc(p->str, 256);
            for(i = k; i < 256; i++) {
                (p->str)[i] = '\0';
            }
        }*/
        if((p->str)[k] != '\0')
            shift(p, k);
        (p->str)[k] = cc;
    }
    //(p->str)[x+1] = '\0';
    /* increase length */
    //l->len++;
}
void remov(WINDOW* w, list *l, int k, int m){
    node* p;
    int i, pos = m;
    if(pos < 0 || pos >= l->len)
        return ;
    p = l->head;
    for(i = 0; i < pos; i++)
        p = p->next;
   // left_shift(p, k);
    if((p->str)[k] == '\n') {
	//pos++;
	(p->str)[k] = '\0';
	strcat(p->str, p->next->str);
	p = p->next;
	pos++;
    	if(pos == 0) {
        	p->next->prev = NULL;
        	l->head = p->next;
        	p->next = NULL;
    	}
    	else if(pos == l->len -1 ) {
        	p->prev->next = NULL;
        	l->tail = p->prev;
        	p->prev = NULL;
    	}
    	else {
       		p->next->prev = p->prev;
        	p->prev->next = p->next;
        	p->next = NULL;
        	p->prev = NULL;
    	}
    	l->len--;
    }
    else
    	left_shift(p, k);
}

void insert_in_line(int pos){
    

}
void traverse(WINDOW* ww, list* l){
    node *p = l->head;
    int i;
    while(p != NULL) {
        for(i = 0;(p->str)[i] != '\0'; i++) {
            wprintw(ww, "%c", (p->str)[i]);
        }
        p = p->next;
    }
}


void shift(node *p, int x) {
    int i;
    int k = strlen(p->str);
    for(i = k;i > x;i--)
            (p->str)[i] = (p->str)[i-1];
    
}

void left_shift(node *p, int x) {
	int i;
	int k = strlen(p->str);
	for(i = x; i < k - 1; i++)
		(p->str)[i] = (p->str)[i+1];
	(p->str)[k-1] = '\0';

}
