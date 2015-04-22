#ifndef CTRL_DRIVER 
#define CTRL_DRIVER 

#include "../model/ModelDriver.h"

class ControllerDriver {
    private:
        bool * running;
        ModelDriver * md;
    public:
        ControllerDriver(bool * run, ModelDriver * modDrive);
        ~ControllerDriver();
        void getInput();
};

#endif

