#include <ncurses.h>

#include "../globals.h"
#include "ControllerDriver.h"
#include "../model/ModelDriver.h"

ControllerDriver::ControllerDriver(bool * run, ModelDriver * modDrive)
{
    running = run;
    md = modDrive;
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
            case '1':
                md->setSelectedWindow(CHATWINDOW);
                break;
            case '2':
                md->setSelectedWindow(ROOMWINDOW);
                break;
            case '3':
                md->setSelectedWindow(USERWINDOW);
                break;
        }
    }
}

