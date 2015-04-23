
#ifndef VIEW_DRIVER
#define VIEW_DRIVER

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

#define CHAT_WIDTH (3.0 / 5.0)
#define CHAT_HEIGHT 1.0
#define SIDE_WIDTH (2.0 / 5.0)
#define SIDE_HEIGHT (1.0 / 2.0)

class ViewDriver {
    private:
        ChatWindow * chat;
        RoomWindow * rooms;
        UserWindow * users;
    public:
        ViewDriver(ModelDriver * md);
        ~ViewDriver();
        void draw();
};

#endif

