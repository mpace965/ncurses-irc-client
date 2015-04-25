#include <ncurses.h>
#include <string.h>
#include <math.h>

#include "../globals.h"
#include "ControllerDriver.h"
#include "../model/ModelDriver.h"

ControllerDriver::ControllerDriver(bool * run, ModelDriver * md)
{
    running = run;
    modelDriver = md;
}

ControllerDriver::~ControllerDriver()
{

}

void ControllerDriver::getInput()
{
    int ch = getch();

    if (ch != ERR) {
        switch (ch) {
            case KEY_F(1):
                *running = false;
                break;
            case KEY_UP:
                chatScroll(ch);
                sideScroll(ch);
                break;
            case KEY_DOWN:
                chatScroll(ch);
                sideScroll(ch);
                break;
            case '\t':
                roomButtonToggle();
                break;
            case '1':
                modelDriver->setSelectedWindow(CHATWINDOW);
                break;
            case '2':
                modelDriver->setSelectedWindow(ROOMWINDOW);
                break;
            case '3':
                modelDriver->setSelectedWindow(USERWINDOW);
                break;
        }
    }
}

void ControllerDriver::chatScroll(int ch)
{
    if (modelDriver->getSelectedWindow() != CHATWINDOW)
        return;

    if (ch == KEY_UP && modelDriver->topMsg > 0) {
        modelDriver->topMsg -= 1;
    } else if (ch == KEY_DOWN && modelDriver->topMsg != modelDriver->botMsg) {
        modelDriver->topMsg += 1;
    }
}

void ControllerDriver::sideScroll(int ch)
{
    int * highlight = 0;
    int * page = 0;
    int numberOf = 0;
    int pageLength = modelDriver->halfPageLength();

    if (modelDriver->getSelectedWindow() == USERWINDOW) {
        highlight = &modelDriver->userHighlighted;
        page = &modelDriver->userPage;
        numberOf = modelDriver->getNumUsers();
    } else if (modelDriver->getSelectedWindow() == ROOMWINDOW) {
        highlight = &modelDriver->roomHighlighted;
        page = &modelDriver->roomPage;
        numberOf = modelDriver->getNumRooms();
    } else {
        return;
    }

    if (ch == KEY_UP) {
        if (*highlight > 0) {
            *highlight -= 1;

            if (*highlight == *page - 1)
                *page -= pageLength;
        }
    } else if (ch == KEY_DOWN) {
        if (*highlight < numberOf - 1) {
            *highlight += 1;

            if (*highlight == *page + pageLength)
                *page += pageLength;
        }
    }
}

void ControllerDriver::roomButtonToggle()
{
    if (modelDriver->getSelectedWindow() != ROOMWINDOW)
        return;

    switch (modelDriver->selectedRoomButton) {
        case CREATEROOM:
            modelDriver->selectedRoomButton = ENTERROOM;
            break;
        case ENTERROOM:
            modelDriver->selectedRoomButton = LEAVEROOM;
            break;
        case LEAVEROOM:
            modelDriver->selectedRoomButton = CREATEROOM;
            break;
    }
}


