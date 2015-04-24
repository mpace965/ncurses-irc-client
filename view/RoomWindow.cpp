#include <ncurses.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void RoomWindow::draw()
{
    rowHighlight();

    if (modelDriver->getSelectedWindow() == ROOMWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HIGHLIGHT));
    }
    Window::draw();

    wrefresh(win);
}

void RoomWindow::rowHighlight()
{
    int pageLength = modelDriver->halfPageLength();
    int end = modelDriver->roomPage + pageLength;

    for (int i = modelDriver->roomPage; i < end; i++) {
        if ((modelDriver->roomHighlighted % pageLength) == i % pageLength) {
            wattron(win, A_REVERSE);
            mvwprintw(win, i % pageLength + 1, 1, modelDriver->getRoom(i));
            wattroff(win, A_REVERSE);
        } else if (i >= modelDriver->getNumRooms()) {
            wmove(win, i % pageLength + 1, 1);
            wclrtoeol(win);
        } else {
            mvwprintw(win, i % pageLength + 1, 1, modelDriver->getRoom(i));
        }
    }
}

