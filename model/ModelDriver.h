#ifndef MODEL_DRIVER 
#define MODEL_DRIVER 

#include <vector>

class ModelDriver {
    private:
        int selectedWindow;
        std::vector<const char *> users;
    public:
        ModelDriver();
        ~ModelDriver();
        void update();

        int getSelectedWindow() { return selectedWindow; };
        void setSelectedWindow(int i) { selectedWindow = i; };

        int getNumUsers() { return users.size(); };
        const char * getUser(int i) { return users.at(i); };
        void addUser(const char * name) { users.push_back(name); };

        int userHighlighted;
};

#endif

