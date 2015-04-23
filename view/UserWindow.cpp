#include <ncurses.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void UserWindow::draw()
{
    if (modelDriver->getSelectedWindow() == USERWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HIGHLIGHT));
    }

    Window::draw();

    rowHighlight();

    wrefresh(win);
}

void UserWindow::rowHighlight()
{
    int size = modelDriver->getNumUsers();

    for (int i = 0; i < size; i++) {
        if (modelDriver->userHighlighted == i) {
            wattron(win, A_REVERSE);
            mvwprintw(win, i + 1, 1, modelDriver->getUser(i));
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, i + 1, 1, modelDriver->getUser(i));
        }
    }
}

