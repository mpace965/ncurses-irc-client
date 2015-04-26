#include "globals.h"
#include "model/ModelDriver.h"
#include "view/ViewDriver.h"
#include "controller/ControllerDriver.h"

int main(int argc, char ** argv)
{
    bool running = true;

    ModelDriver md;
    ViewDriver vd(&md);
    ControllerDriver cd(&running, &md);

    if (argc != 4) {
        md.setSelectedWindow(FIRSTWINDOW);

        while (running) {
           md.updateFirstRun();
           vd.drawFirstRun();
           cd.getInputFirstRun();
        }

        return 0;
    }

    md.setUsername(argv[1]);
    md.setPassword(argv[2]);
    md.setPort(atoi(argv[3]));

    while (running) {
        md.update();
        vd.draw();
        cd.getInput();
    }

    return 0;
}
