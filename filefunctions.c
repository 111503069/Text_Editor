#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include "datastructure.h"
#include "filefunctions.h"
#include <ncurses.h>
void print(WINDOW* menu, WINDOW* w, list *l, char* c) {
    //list l;
    int ch, cm;
    char ce;
    char *orig, *new;
    int modified = 0;
    int down = 1;
    int tab = 0;
    orig = (char*)malloc(sizeof(char)*20);
    new = (char*)malloc(sizeof(char)*20);
    int clx, cly, x1, y1, x2, y2;
    int k = 0;
    int m = 0;
    char str[100];
    start_color();
    init_pair(3, COLOR_BLACK, 111);
    int colour = 0;
    //init(l);
    // ch = (int*)malloc(getmaxx(w));
    int i, y = 0, x = 0;
    wmove(w, y, x);
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
        if(ch == 23) {
            no_name(c, menu);
            save(l, c);
            return;
        }
        if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN || ch == KEY_BACKSPACE || ch == '\n' || ch == 4 || ch == KEY_SLEFT || ch == KEY_SRIGHT || ch  == 2 ||  ch  == 5 || ch == 24 || ch == 18 || ch == 16) {
            switch(ch) {
                case KEY_LEFT :
                    if(k == 0 && m == 0) {
                        colour = 0;
                        wclear(w);
                        traverse(w, l);
                        break;
                    }
                    k--;
                    if(k < 0) {
                        p = p->prev;
                        k = strlen(p->str) - 1;
                        m--;
                        y--;
                     }
                    colour = 0;
                    wclear(w);
                    traverse(w, l);
                    //x--;
                    break;
                case KEY_RIGHT :
                    if(p->next == NULL && k == strlen(p->str)) {
                        m++;
                        insert(l, k, m, '\n');
                        k = 0;
                        wclear(w);
                        wrefresh(w);
                        traverse(w, l);
                        x = 0;
                        y++;
                        colour = 0;
                        wclear(w);
                        traverse(w, l);
                        break;
                        
                    }

                    else if(p->str[k] == '\n') {
                     	k = 0;
                        m++;
                        y++;
                     }
                    else
                        k++;
                    colour = 0;
                    wclear(w);
                    traverse(w, l);
                    break;
                case KEY_UP:
                    if(strlen(p->str) <= getmaxx(w) && m == 0){
                        colour = 0;
                        wclear(w);
                        traverse(w, l);
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
                    colour = 0;
                    wclear(w);
                    traverse(w, l);
                    break;
                case KEY_DOWN :
                    if(p->next == NULL) {
                        if(k < getmaxx(w)) {
                            if(strlen(p->str) > getmaxx(w)) {
                                down = 0;
                                k = k + getmaxx(w);
                            }
                            else
                                m++;
                        }
                        else  {
                            m++;
                            k = k - getmaxx(w);
                        }
                        if(down) {
                        //m++;
                            k = strlen(p->str);
                            insert(l, k, m, '\n');
                            k = 0;
                            wclear(w);
                            wrefresh(w);
                            traverse(w, l);
                            x = 0;
                            y++;
                            colour = 0;
                            break;
                        }
                    }
                        
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
                    colour = 0;
                    wclear(w);
                    traverse(w, l);
                    break;
                case KEY_BACKSPACE :
                    if(k == 0 && m == 0){
                        colour = 0;
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
                     colour = 0;
                     break;
                    
                case '\n' :
                    //k = 0;
                    tab = 0;
                    m++;
                    insert(l, k, m, '\n');
                    k = 0;
                    wclear(w);
                    wrefresh(w);
                    traverse(w, l);
                    x = 0;
                    y++;
                    colour = 0;
                    break;
                case 4 :
                    delete_line(w, l, k, m);
                    m--;
                   // wprintw(w, "%d", m);
                    y--;
                    k = 0;
                    if(y < 0) {
                        m = 0;
                        y = 0;
                    }
                    wrefresh(w);
                    wclear(w);
                    wrefresh(w);
                    traverse(w, l);
                    colour = 0;
                    break;
                case KEY_SLEFT :
                    if(colour == 0){
                        clx = k;
                        cly = m;
                    }
                    colour = 1;
                    mvwchgat(w, m, k-1, 1, A_BOLD, 3, NULL);
                    wrefresh(w);
                    if(k == 0 && m == 0) {
                        x2 = clx;
                        y2 = cly;
                        x1 = k;
                        y1 = m;
                        break;
                    }
                    k--;
                    if(k < 0) {
                        p = p->prev;
                        k = strlen(p->str) - 1;
                        m--;
                        y--;
                    }
                    x2 = clx;
                    y2 = cly;
                    x1 = k;
                    y1 = m;
                    //x--;
                    break;
                case KEY_SRIGHT :
                    if(colour == 0 || colour == 1){
                        clx = k;
                        cly = m;
                    }
                    colour = 2;
                    mvwchgat(w, m, k,1, A_BOLD, 3, NULL);
                    wrefresh(w);
                    if(p->next == NULL && k == strlen(p->str)) {
                        m++;
                        insert(l, k, m, '\n');
                        k = 0;
                        wclear(w);
                        wrefresh(w);
                        traverse(w, l);
                        x = 0;
                        y++;
                        x1 = clx;
                        y1 = cly;
                        x2 = k;
                        y2 = m;
                        break;
                        
                    }
                    
                    else if(p->str[k] == '\n') {
                        k = 0;
                        m++;
                        y++;
                    }
                    else
                        k++;
                    x1 = clx;
                    y1 = cly;
                    x2 = k;
                    y2 = m;
                    break;

                case 2 :
                    //if(colour == 0)
                      //  break;

                    strcpy(str, copy(l, x1, y1, x2, y2));
                    colour = 0;
                    break;
                case 16 :
                    //if(colour == 0)
                      //  break;

                    paste(l, k, m, str);
                    wclear(w);
                    wrefresh(w);
                    traverse(w, l);
                    colour = 0;
                    break;
                case 24 :
                    if(colour == 0)
                        break;
                    wclear(w);
                    strcpy(str, copy(l, x1, y1, x2, y2));
                    cut(w, l, x1, y1, x2, y2);
                    k = x1;
                    y = y1;
                    m = y1;
                    colour = 0;
                    break;
                
                case 18 :
                    wclear(menu);
                    wprintw(menu, "Enter the word to be replaced: ");
                    wrefresh(menu);
                    i = 0;
                    while((cm = wgetch(menu)) != '\n') {
                        wprintw(menu, "%c", cm);
                        orig[i] = cm;
                        i++;
                    }
                    orig[i] = '\0';
                    wprintw(menu, "\nEnter the new word : ");
                    wrefresh(menu);
                    i = 0;
                    while((cm = wgetch(menu)) != '\n') {
                        wprintw(menu, "%c", cm);
                        new[i] = cm;
                        i++;
                    }
                    new[i] = '\0';
                    stringreplace(menu, w, l, orig, new);
                    break;
                    //wclear(w);
                    //traverse(w, l);
                case 5 :
                    if(modified == 1) {
                        wclear(menu);
                        wprintw(menu, "Save the modified changes : y/n");
                        wrefresh(menu);
                        ce = wgetch(menu);
                        wprintw(menu, "%c", ce);
                        wrefresh(menu);
                        if(ce == 'y') {
                            no_name(c, menu);
                            save(l, c);
                        }
                    }
                        
                    endwin();
                    exit(1);
                    
            }
            p = l->head;
            for(i = 0; i < m; i++)
                p = p->next;
            if(p != NULL) {
                if(p->str[k] == '\0') {
                    k = strlen(p->str);
                    if(p->str[k-1] == '\n')
                        k = strlen(p->str) - 1;
                }
            }
            print_menu(menu);
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
           // if(ch != '\t')
            x = k%getmaxx(w) + tab;
            k = x;
            /*wclear(w);
             wrefresh(w);
             traverse(w, &l, f, k);*/
            wmove(w, y, x);
            wrefresh(w);
	    //if(k == 0) {
		
            
        
        }
        
        else {
            modified = 1;
            colour = 0;
            insert(l, k, m, ch);
            if(ch == '\t') {
                
                tab = 7 - x%8;
                x = x + tab;
            }
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
            //x = k%getmaxx(w);
            wrefresh(w);
            wclear(w);
            wrefresh(w);
            traverse(w, l);
            wmove(w, y, x);
            wrefresh(w);
        }
    }while(ch != 23);
}

void open(WINDOW* w, char* c , list *l) {
    //if(c == NULL)
      //  return;
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
    wclear(w);
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

char* copy(list *l, int k, int m, int clx, int cly) {
    int i = 0, j = 0;
    node *p;
    char *str;
    str = (char*)malloc(sizeof(char)*100);
    p = l->head;
    for(i = 0; i < m; i++)
        p = p->next;
    while(k != clx || m != cly) {
        str[j] = p->str[k];
        if(p->str[k] == '\n') {
            m++;
            k = 0;
            p = p->next;
        }
        else
            k++;
        j++;
    }
    str[j] = '\0';
    return str;
}

void paste(list *l, int k, int m, char *str) {
    int i = 0;
    char ch;
    while(str[i] != '\0') {
        ch = str[i];
        if(ch == '\n'){
            m++;
            insert(l, k, m, ch);
            //j++;
            k = 0;
        }
        else {
            insert(l, k, m, ch);
            k++;
        }
        i++;
    }
}

void cut(WINDOW* ww, list *l, int k, int m, int clx, int cly) {
    int i = 0, j = 0;
    node *p;
    p = l->head;
    for(i = 0; i < cly; i++)
        p = p->next;
    do {
        clx--;
        if(clx < 0) {
            p = p->prev;
            clx = strlen(p->str)-1;
            cly--;
        }
        remov(ww, l, clx, cly);
        j++;
    }while(k != clx || m != cly);
    traverse(ww, l);
}

void stringreplace (WINDOW* menu, WINDOW *ww, list *l, char *orig, char *new) {
    start_color();
    init_pair(4, COLOR_BLACK, COLOR_RED);
    node *pp = l->head;
    char *p = pp->str, *q = orig, *s;
    int t, o, n, c = 0, i;
    int k = 0, m = 0, x, y;
    int replace = 1;
    char ch;
    while(pp != NULL) {
        c = 0;
        p = pp->str;
        t = strlen(pp->str);
        o = strlen(orig);
        n = strlen(new);
        while(*p != '\0') {
        d:
            while(*p != '\0' && *q != '\0') {
                if(*p == *q)  {
                    p++;
                    q++;
                }
                else {
                    if(q == orig)
                        p++;
                    else  {
                        p = p - (q - orig)+ 1;
                        q = orig;
                    }
                }
                k++;
            }
        
            if(*q == '\0') {
                if(replace == 0) {
                    k = p - pp->str - strlen(orig) + c*(o-n);
                    y = m;
                    if(k > getmaxx(ww)) {
                        
                        y++;
                    }
                    x = k%getmaxx(ww);
                    mvwchgat(ww, y, x, strlen(orig), A_BOLD, 4, NULL);
                    wrefresh(ww);
                }
                if(replace == 1) {
                    k = p - pp->str - strlen(orig);
                    y = m;
                    if(k > getmaxx(ww)) {
                        y++;
                    }
                    x = k%getmaxx(ww);

                    
                    mvwchgat(ww, y, x, strlen(orig), A_BOLD, 4, NULL);
                    wrefresh(ww);
                
                    wclear(menu);
                    wprintw(menu, "Do you want to replace ? (y/n/a)" );
                    wrefresh(menu);
                    ch = wgetch(menu);
                    wprintw(menu, "%c", ch);
                    wrefresh(menu);
                    if(ch == 'n'){
                        replace = 1;
                        p++;
                        q = orig;
                        //pp = pp->next;
                        //continue;
                        goto d;
                    }
                    if(ch == 'y')
                        replace = 1;
                    if(ch == 'a')
                        replace = 0;
                }
                s = p;
                if(n >= o) {
                    for(i = t+c*(n-o)  ; i > p - pp->str -1 ; i--) {
                        pp->str[i + n -o] = pp->str[i];
                    }
                    p = p + (n - o);
                }
                else {
                    for(i = s - pp->str - (q - orig); i < t + c*(n-o); i++) {
                        pp->str[i] = pp->str[i - n + o];
                    }
                    p = p + n - o;
                }
                for(i = 0; i < n; i++) {
                    pp->str[s-(q-orig)+i-(pp->str)] = new[i];
                }
                q = orig;
                c++;
            }
            if(replace == 1) {
                wclear(ww);
                traverse(ww, l);
            }
        }
        pp->str[t+c*(n-o)] = '\0';
        pp = pp->next;
        m++;
        
    }
    if(replace == 0) {
        wclear(menu);
        wprintw(menu, "Do you want to replace ? (y/n) : " );
        wrefresh(menu);
        ch = wgetch(menu);
        wprintw(menu, "%c", ch);
        wrefresh(menu);
        if(ch == 'y') {
        	wclear(ww);
        	traverse(ww, l);
        }
        else {
            stringreplace(menu, ww, l, new, orig);
        }
    }

}

void no_name(char* file_name, WINDOW* menu) {
    int i;
    char cf, f[20];
   // if(!strcmp(file_name, "Untitled File")) {
        wclear(menu);
        wprintw(menu, "Enter the file name to save : ");
        wrefresh(menu);
        i = 0;
        while((cf = wgetch(menu)) != '\n') {
            wprintw(menu, "%c", cf);
            wrefresh(menu);
            f[i] = cf;
            i++;
        }
        f[i] = '\0';
        strcpy(file_name, f);
   // }
}

void print_menu(WINDOW* menu) {
    wclear(menu);
    int k = getmaxx(menu)/4;
    mvwprintw(menu, 0, 0, "SAVE : ^W");
    mvwprintw(menu, 0, k, "DELETE LINE : ^D");
    mvwprintw(menu, 0, 2*k, "COPY : ^B");
    mvwprintw(menu, 0, 3*k, "PASTE : ^P");
    mvwprintw(menu, 1, 0, "EXIT : ^E");
    mvwprintw(menu, 1, k, "REPLACE : ^R");
    mvwprintw(menu, 1, 2*k, "CUT : ^X");
    wrefresh(menu);
}

void help(char* str) {
    char ch;
    FILE* f;
    f = fopen(str, "r");
    while(fscanf(f, "%c", &ch) != EOF)
        printf("%c", ch);
    fclose(f);
}
