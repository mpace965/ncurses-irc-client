#ifndef MODEL_DRIVER 
#define MODEL_DRIVER 

class ModelDriver {
    private:
        int selectedWindow;
    public:
        ModelDriver();
        ~ModelDriver();
        void update();

        int getSelectedWindow() { return selectedWindow; };
        void setSelectedWindow(int i) { selectedWindow = i; };
};

#endif

