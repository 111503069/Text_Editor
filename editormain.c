/*****************************************************************************
 * Copyright (C) Valakonda Anusha valakondaanusha@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
                    /*  TEXT EDITOR  */

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
    if(argc > 2) {
        if(!strcmp(argv[1], "-h")) {
            fn = fopen("-h", "a");
            help("-h");
            fclose(fn);
            exit(1);
            return 0;
        }
    }
        
    
    char* file_name;
    file_name = (char*)malloc(sizeof(char)*20);
    if(argc < 2) {
        strcpy(file_name, "Untitled File");
    }
    else
        strcpy(file_name, argv[1]);
    fn = fopen(file_name, "a");
    list l;
    init(&l);
    curses_init();
    getmaxyx(stdscr, parent_y, parent_x);
    WINDOW *win = newwin(parent_y - 3, parent_x,1 , 0);
    WINDOW *menu = newwin(2, parent_x, parent_y-2, 0);
    WINDOW *name = newwin(1, parent_x, 0, 0);
    keypad(win, TRUE);
    keypad(name, TRUE);
    scrollok(win, TRUE);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    wbkgd(name, COLOR_PAIR(2));
    wbkgd(win, COLOR_PAIR(1));
    wbkgd(menu, COLOR_PAIR(2));
    while(1) {
        wclear(name);
        mvwprintw(name, 0, (parent_x)/2 - 9, "FILE : %s", file_name);
        wrefresh(win);
        wrefresh(menu);
        wrefresh(name);
        print_menu(menu);
        wrefresh(menu);
        wrefresh(name);
        curs_set(TRUE);
        open(win, file_name, &l);
        print(menu, win, &l, file_name);
        wrefresh(win);
        wrefresh(menu);
        wrefresh(name);
    }
    fclose(fn);
    refresh();
    endwin();
}