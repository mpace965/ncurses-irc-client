
#ifndef VIEW_DRIVER
#define VIEW_DRIVER

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

class ViewDriver {
    public:
        ViewDriver(ModelDriver * md);
        ~ViewDriver();
        void draw();
        void drawFirstRun();

        FirstRunWindow * firstRun;
        ChatWindow * chat;
        RoomWindow * rooms;
        CreateRoomWindow * createRoom;
        UserWindow * users;
};

#endif

