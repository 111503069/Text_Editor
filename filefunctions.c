#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include "filefunctions.h"
#include <ncurses.h>
void print(WINDOW* w, list *l) {
    //list l;
    int ch;
    int k = 0;
    int m = 0;
    //init(l);
    // ch = (int*)malloc(getmaxx(w));
    int i, y = 0, x = 0;
    
    //f = fopen(c, "a");
    node *p;
    //ch = wgetch(w);
    do{
        ch = wgetch(w);
        curs_set(TRUE);
        wmove(w, y, x);
        p = l->head;
        for(i = 0; i < m; i++)
            p = p->next;
        //ch = wgetch(w);
        if(ch == 23)
            return;
        if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN || ch == KEY_BACKSPACE || ch == '\n') {
            switch(ch) {
                case KEY_LEFT :
                    if(k == 0 && m == 0)
                        break;
                    k--;
                    if(k < 0) {
                        p = p->prev;
                        k = strlen(p->str) - 1;
                        m--;
                        y--;
                     }
                    //x--;
                    break;
                case KEY_RIGHT :
                    if(p->str[k] == '\n') {
                     	k = 0;
                        m++;
                        y++;
                     }
                    else
                        k++;
                    break;
                case KEY_UP:
                    if(strlen(p->str) <= getmaxx(w) && m == 0){
                        break;
                    }
                    if(k >= getmaxx(w))
                        k = k - getmaxx(w);
                    else if(p->prev != NULL){
                        m--;
                        if(strlen((p->prev)->str) < k ) {
                            k = strlen((p->prev)->str) - 1;
                        }
                        if(strlen((p->prev)->str) > getmaxx(w)) {
                            k = k + getmaxx(w);
                        }
                    }
                    y--;
                    break;
                case KEY_DOWN :
                    if(k < getmaxx(w)) {
                        if(strlen(p->str) > getmaxx(w)) {
                            k = k + getmaxx(w);
                        }
                        else
                            m++;
                    }
                    else  {
                        m++;
                        k = k - getmaxx(w);
                    }
                    y++;
                    break;
                case KEY_BACKSPACE :
                    if(k == 0 && m == 0){
                        break;
                    }
                    x--;
                    k--;
                    if(k < 0) {
                        p = p->prev;
                        k = strlen(p->str) - 1;
                        m--;
                        y--;
                     }
                     remov(w, l, k, m);
                     wrefresh(w);
                     wclear(w);
                     traverse(w, l);
                     break;
                    
                case '\n' :
                    //k = 0;
                    m++;
                    insert(l, k, m, '\n');
                    k = 0;
                    wclear(w);
                    wrefresh(w);
                    traverse(w, l);
                    x = 0;
                    y++;
                    break;
            }

            /*if(k < 0) {
		if(strlen(p->str) >= getmaxx(w)) {
               		x = getmaxx(w);
                	y--;
		}
		//else {
			p = p->prev;
			k = strlen(p->str) - 1;
			m--;
			y--;		
		//}
            }
            else if(x == getmaxx(w)) {
                //insert(w, &l, x, y, '\n');
                x = 0;
                y++;
            }*/
            x = k%getmaxx(w);
		
            /*wclear(w);
             wrefresh(w);
             traverse(w, &l, f, k);*/
            wmove(w, y, x);
            wrefresh(w);
	    //if(k == 0) {
		
            
        
        }
        
        else {
            insert(l, k, m, ch);
            k++;
            x++;
            if(x == getmaxx(w)) {
                x = 0;
                y++;
            }
            if(x < 0) {
                x = getmaxx(w);
                y--;
            }
            wrefresh(w);
            wclear(w);
            wrefresh(w);
            traverse(w, l);
            wmove(w, y, x);
            wrefresh(w);
        }
        //ch[x] = '\0';
        //insert(&l, k, ch);
        
    }while(ch != 23);
}

void open(WINDOW* w, char* c , list *l) {
    FILE* f;
    char ch;
    init(l);
    int i = 0;
    int j = 0;
    f = fopen(c, "r");
    while(fscanf(f, "%c", &ch) != EOF) {
            if(ch == '\n'){
            j++;
            insert(l, i, j, ch);
            i = 0;
        }
        else {
            insert(l, i, j, ch);
            i++;
        }
    }
    traverse(w, l);
    fclose(f);
}

void save(list *l, char* c) {
    FILE* f;
    f = fopen(c, "w");
    node *p = l->head;
    int i;
    while(p != NULL) {
        for(i = 0;(p->str)[i] != '\0'; i++) {
            fprintf(f, "%c", (p->str)[i]);
        }
        p = p->next;
    }
    fclose(f);
}

//void lable(WINDOW *w) {
  //  mvwprintw(w, 0, 0, "SAVE : ^W");
//}
