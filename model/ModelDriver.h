#ifndef MODEL_DRIVER 
#define MODEL_DRIVER 

#include <ncurses.h>
#include <vector>
#include <math.h>
#include <stdlib.h>

#include "../globals.h"

class ModelDriver {
    private:
        int selectedWindow;
        std::vector<const char *> users;
        std::vector<const char *> rooms;
    public:
        ModelDriver();
        ~ModelDriver();
        void update();

        int getSelectedWindow() { return selectedWindow; };
        void setSelectedWindow(int i) { selectedWindow = i; };

        int halfPageLength() { return (int) round(SIDE_HEIGHT * LINES) - 3; } //-3 to account for the borders

        int getNumUsers() { return users.size(); };
        const char * getUser(int i) { return users.at(i); };
        void addUser(const char * name) { users.push_back(name); };
        int userHighlighted;
        int userPage;

        int getNumRooms() { return rooms.size(); };
        const char * getRoom(int i) { return rooms.at(i); };
        void addRoom(const char * name) { rooms.push_back(name); };
        int roomHighlighted;
        int roomPage;
        int selectedRoomButton;

        void gen_random(char *s, const int len) {
            static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

            for (int i = 0; i < len; ++i) {
                s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
            }

            s[len] = 0;
        }

};

#endif

