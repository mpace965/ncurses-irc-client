#ifndef CTRL_DRIVER 
#define CTRL_DRIVER 

#include "../model/ModelDriver.h"
#include "../view/ViewDriver.h"

class ControllerDriver {
    private:
        bool * running;
        ModelDriver * modelDriver;
        ViewDriver * viewDriver;

        void inputOn();
        void inputOff();
    public:
        ControllerDriver(bool * run, ModelDriver * md, ViewDriver * vd);
        ~ControllerDriver();
        void getInput();
        void getInputFirstRun();

        void firstRunTextInput();
        void firstRunButtonToggle();
        void addUser();

        void roomButtonToggle();

        void chatScroll(int ch);
        void sideScroll(int ch);
};

#endif

