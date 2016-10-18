
#include<stdio.h>
#include <stdlib.h>
#include<ncurses.h>
#include <string.h>
#include "filefunctions.h"
#include "datastructure.h"
void curses_init()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
}
int main(int argc, char* argv[]) {
    int parent_x, parent_y;
    FILE* fn;
    fn = fopen(argv[1], "a");
    list l;
    init(&l);
    curses_init();
    getmaxyx(stdscr, parent_y, parent_x);
    WINDOW *win = newwin(parent_y - 4, parent_x,4 , 0);
    WINDOW *menu = newwin(3, parent_x, 1, 0);
    WINDOW *name = newwin(1, parent_x, 0, 0);
    keypad(win, TRUE);
    keypad(name, TRUE);
    //start_color();
    
    //init_pair(1, COLOR_WHITE, COLOR_BLACK);
    //attron( COLOR_PAIR(1));
    //wbkgd(name, COLOR_PAIR(1));
    mvwprintw(name, 0, (parent_x)/2 - 9, "FILE : %s", argv[1]);
    //init_pair(1, COLOR_WHITE, COLOR_BLACK);
    //attroff( COLOR_PAIR(1));
    
    mvwprintw(menu, 0, 0, "SAVE : ^W");
    wgetch(name);
    wgetch(menu);
    curs_set(TRUE);
    open(win, argv[1], &l);
    print(win, &l);
    save(&l, argv[1]);
    wrefresh(win);
    wrefresh(menu);
    wrefresh(name);
    fclose(fn);
    refresh();
    endwin();
}

//void info() {
  //  mvwprintw("")
//}