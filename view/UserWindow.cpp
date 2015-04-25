#include <ncurses.h>
#include <math.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void UserWindow::draw()
{
    rowHighlight();

    if (modelDriver->getSelectedWindow() == USERWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HIGHLIGHT));
    }

    Window::draw();

    wrefresh(win);
}

void UserWindow::rowHighlight()
{
    int pageLength = modelDriver->halfPageLength();
    int end = modelDriver->userPage + pageLength;

    for (int i = modelDriver->userPage; i < end; i++) {
        if ((modelDriver->userHighlighted % pageLength) == i % pageLength) {
            wattron(win, A_REVERSE);
            mvwprintw(win, i % pageLength + 1, 1, modelDriver->getUser(i));
            wattroff(win, A_REVERSE);
        } else if (i >= modelDriver->getNumUsers()) {
            wclrtobot(win);
            break;
        } else {
            mvwprintw(win, i % pageLength + 1, 1, modelDriver->getUser(i));
        }
    }
}

