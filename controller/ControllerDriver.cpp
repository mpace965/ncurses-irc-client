#include <ncurses.h>

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
                userScroll(ch);
                break;
            case KEY_DOWN:
                userScroll(ch);
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

void ControllerDriver::userScroll(int ch)
{
    if (modelDriver->getSelectedWindow() != USERWINDOW) {
        return;
    }

    if (ch == KEY_UP) {
        if (modelDriver->userHighlighted > 0)
            modelDriver->userHighlighted--;
    } else if (ch == KEY_DOWN) {
        if (modelDriver->userHighlighted < modelDriver->getNumUsers() - 1)
            modelDriver->userHighlighted++;
    }
}

