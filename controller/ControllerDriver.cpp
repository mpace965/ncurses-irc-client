#include <ncurses.h>

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
        if (ch == KEY_F(1)) {
            *running = false;
        }
    }
}

