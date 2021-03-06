#include <unistd.h>

#include "globals.h"
#include "model/ModelDriver.h"
#include "view/ViewDriver.h"
#include "controller/ControllerDriver.h"

int main(int argc, char ** argv)
{
    bool running = true;

    ModelDriver md(&running);
    ViewDriver vd(&md);
    ControllerDriver cd(&running, &md, &vd);

    if (argc != 5) {
        md.setSelectedWindow(FIRSTWINDOW);

        while (running) {
           md.updateFirstRun();
           cd.getInputFirstRun();
           vd.drawFirstRun();
           usleep(DELAY);
        }

        return 0;
    }

    md.setUsername(argv[1]);
    md.setPassword(argv[2]);
    md.setHost(argv[3]);
    md.setPort(atoi(argv[4]));

    while (running) {
        md.update();
        cd.getInput();
        vd.draw();
        usleep(DELAY);
    }

    if (strcmp(md.selectedRoom, "")) {
        char response[MAX_RESPONSE];
        char leaveRoom[100];
        sprintf(leaveRoom, "%s leaves the room.", md.selectedRoom);
        md.sendCommand("SEND-MESSAGE", leaveRoom, response);

        md.sendCommand("LEAVE-ROOM", md.selectedRoom, response);
    }

    return 0;
}
