#include <ncurses.h>
#include <string.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void RoomWindow::draw()
{
    rowHighlight();

    if (modelDriver->getSelectedWindow() == ROOMWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HICOLOR));
    }
    Window::draw();

    wrefresh(win);
}

void RoomWindow::rowHighlight()
{
    if (modelDriver->getNumRooms() > 0) {
        int pageLength = modelDriver->halfPageLength() + 1;
        int end = modelDriver->roomPage + pageLength;

        for (int i = modelDriver->roomPage; i < end; i++) {
            if ((modelDriver->roomHighlighted % pageLength) == i % pageLength) {
                wattron(win, A_REVERSE);
                mvwprintw(win, i % pageLength + 1, 1, modelDriver->getRoom(i));

                if (!strcmp(modelDriver->getRoom(i), modelDriver->selectedRoom))
                    wprintw(win, "*");
                wclrtoeol(win);

                wattroff(win, A_REVERSE);
            } else if (i >= modelDriver->getNumRooms()) {
                wclrtobot(win);
                break;
            } else {
                mvwprintw(win, i % pageLength + 1, 1, modelDriver->getRoom(i));
                if (!strcmp(modelDriver->getRoom(i), modelDriver->selectedRoom))
                    wprintw(win, "*");
                wclrtoeol(win);
            }
        }
    }
}

