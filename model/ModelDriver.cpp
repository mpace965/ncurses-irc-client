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
    selectedRoomButton = CREATEROOM;

    topMsg = 0;
    botMsg = 0;

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

    for (int i = 0; i < 100; i++) {
        char msg[50];
        gen_random(msg, 50);
        addMsg(strdup(msg));
    }
}

ModelDriver::~ModelDriver()
{

}

void ModelDriver::updateFirstRun()
{

}

void ModelDriver::update()
{

}

