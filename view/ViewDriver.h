
#ifndef VIEW_DRIVER
#define VIEW_DRIVER

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

class ViewDriver {
    private:
        FirstRunWindow * firstRun;
        ChatWindow * chat;
        RoomWindow * rooms;
        UserWindow * users;
    public:
        ViewDriver(ModelDriver * md);
        ~ViewDriver();
        void draw();
        void drawFirstRun();
};

#endif

