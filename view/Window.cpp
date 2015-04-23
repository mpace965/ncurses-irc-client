#include <ncurses.h>
#include <string.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

Window::Window(int h, int w, int y, int x, const char * n, ModelDriver * md)
{
    win = newwin(h, w, y, x);
    name = strdup(n);
    init_pair(HIGHLIGHT, COLOR_YELLOW, COLOR_BLACK);
    modelDriver = md;
}

Window::~Window()
{
    delwin(win);
}

void Window::draw()
{
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "%s", name);

    wattroff(win, A_BOLD);
    wattroff(win, COLOR_PAIR(HIGHLIGHT));
}

