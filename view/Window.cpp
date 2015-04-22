#include <ncurses.h>
#include <cstring>

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
    wrefresh(win);

    wattroff(win, A_BOLD);
    wattroff(win, COLOR_PAIR(HIGHLIGHT));
}

//ChatWindow
void ChatWindow::draw()
{
    if (modelDriver->getSelectedWindow() == CHATWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HIGHLIGHT));
    }
    Window::draw();
}

//RoomWindow
void RoomWindow::draw()
{
    if (modelDriver->getSelectedWindow() == ROOMWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HIGHLIGHT));
    }
    Window::draw();
}

//UserWindow
void UserWindow::draw()
{
    if (modelDriver->getSelectedWindow() == USERWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HIGHLIGHT));
    }
    Window::draw();
}

