#ifndef CTRL_DRIVER 
#define CTRL_DRIVER 

#include "../model/ModelDriver.h"

class ControllerDriver {
    private:
        bool * running;
        ModelDriver * modelDriver;
    public:
        ControllerDriver(bool * run, ModelDriver * modDrive);
        ~ControllerDriver();
        void getInput();

        void roomButtonToggle();

        void chatScroll(int ch);
        void sideScroll(int ch);
};

#endif

