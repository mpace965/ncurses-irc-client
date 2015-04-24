#include <ncurses.h>
#include <string.h>

#include "../globals.h"
#include "ModelDriver.h"

ModelDriver::ModelDriver()
{
    selectedWindow = CHATWINDOW;
    userHighlighted = 0;
    userPage = 0;

    roomHighlighted = 0;
    roomPage = 0;

    for (int i = 0; i < 40; i++) {
        char name[20];
        gen_random(name, 20);
        addUser(strdup(name));
    }

    for (int i = 0; i < 40; i++) {
        char name[20];
        gen_random(name, 20);
        addRoom(strdup(name));
    }
}

ModelDriver::~ModelDriver()
{

}

void ModelDriver::update()
{

}

