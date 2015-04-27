#include <ncurses.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void CreateRoomWindow::draw()
{
    if (modelDriver->getSelectedWindow() != CREATEROOMWINDOW)
        return;

    mvwprintw(win, 1, 1, "Type the name of the room you wish to create:");

    char input[200];

    nodelay(stdscr, FALSE);
    echo();
    curs_set(1);

    mvwgetnstr(win, 2, 1, input, 200);

    curs_set(0);
    noecho();
    nodelay(stdscr, TRUE);

    char response[MAX_RESPONSE];
    modelDriver->sendCommand("CREATE-ROOM", input, response);
    modelDriver->sendCommand("LIST-ROOMS", "", response);
    modelDriver->setSelectedWindow(ROOMWINDOW);

    if (modelDriver->getSelectedWindow() == CREATEROOMWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HICOLOR));
    }
    Window::draw();

    wrefresh(win);
}

