#include "model/ModelDriver.h"
#include "view/ViewDriver.h"
#include "controller/ControllerDriver.h"

int main()
{
    bool running = true;

    ModelDriver md;
    ViewDriver vd(&md);
    ControllerDriver cd(&running, &md);

    while (running)
    {
        md.update();
        vd.draw();
        cd.getInput();
    }

    return 0;
}
