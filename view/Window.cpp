#include <ncurses.h>
#include <cstring>

#include "../globals.h"
#include "Window.h"

Window::Window(int h, int w, int y, int x, const char * n)
{
    win = newwin(h, w, y, x);
    name = strdup(n);
    init_pair(HIGHLIGHT, COLOR_YELLOW, COLOR_BLACK);
}

Window::~Window()
{
    delwin(win);
}

void Window::draw()
{

}

//ChatWindow
void ChatWindow::draw()
{
    if (Window::selected == CHATWINDOW) {
        attron(A_BOLD);
        attron(COLOR_PAIR(HIGHLIGHT));
    }
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "%s", name);
    wrefresh(win);

    attroff(A_BOLD);
    attroff(COLOR_PAIR(HIGHLIGHT));
}

//
void RoomWindow::draw()
{
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "%s", name);
    wrefresh(win);
}

//UserWindow
void UserWindow::draw()
{
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "%s", name);
    wrefresh(win);
}

