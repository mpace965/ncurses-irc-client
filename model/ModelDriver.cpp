#include <ncurses.h>

#include "../globals.h"
#include "ModelDriver.h"

ModelDriver::ModelDriver()
{
    selectedWindow = CHATWINDOW;
    userHighlighted = 0;

    for (int i = 0; i < 20; i++)
        addUser("userUser");
}

ModelDriver::~ModelDriver()
{

}

void ModelDriver::update()
{

}

