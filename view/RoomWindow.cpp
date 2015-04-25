#include <ncurses.h>
#include <string.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void RoomWindow::draw()
{
    rowHighlight();
    drawButtons();

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

void RoomWindow::drawButtons()
{
    int pageLength = modelDriver->halfPageLength();

    wattron(win, A_BOLD);

    if (modelDriver->selectedRoomButton == CREATEROOM)
        wattron(win, A_REVERSE);
    mvwprintw(win, pageLength + 1, 1, "Create Room");
    wattroff(win, A_REVERSE);

    if (modelDriver->selectedRoomButton == ENTERROOM)
        wattron(win, A_REVERSE);
    const char * enterRoom = "Enter Room";
    mvwprintw(win, pageLength + 1, (int) round((1.0/2.0) * SIDE_WIDTH * COLS) - round(strlen(enterRoom) * (1.0/2.0)) - 1, enterRoom);
    wattroff(win, A_REVERSE);

    if (modelDriver->selectedRoomButton == LEAVEROOM)
        wattron(win, A_REVERSE);
    const char * leaveRoom = "Leave Room";
    mvwprintw(win, pageLength + 1, (int) round(SIDE_WIDTH * COLS) - strlen(leaveRoom) - 1, leaveRoom); 
    wattroff(win, A_REVERSE);

    wattroff(win, A_BOLD);
}

