#ifndef MODEL_DRIVER 
#define MODEL_DRIVER 

#include <ncurses.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../globals.h"

class ModelDriver {
    private:
        int selectedWindow;

        const char * username;
        const char * password;
        char * host;
        int port;

        std::vector<const char *> users;
        std::vector<const char *> rooms;
        std::vector<const char *> messages;
    public:
        ModelDriver();
        ~ModelDriver();
        void update();
        void updateFirstRun();

        int selectedFirstRunButton;

        void setUsername(char * name) { username = strdup(name); };
        const char * getUsername() { return username; };
        void setPassword(char * pw) { password = strdup(pw); };
        const char * getPassword() { return password; };
        void setHost(char * h) { host = strdup(h); };
        char * getHost() { return host; };
        void setPort(int p) { port = p; };
        int getPort() { return port; };

        int getSelectedWindow() { return selectedWindow; };
        void setSelectedWindow(int i) { selectedWindow = i; };

        int fullPageLength() { return (int) round(CHAT_HEIGHT * LINES) - 2; };
        int halfPageLength() { return (int) round(SIDE_HEIGHT * LINES) - 3; }; //-3 to account for the borders

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

        int getNumMsgs() {return messages.size(); };
        const char * getMsg(int i) { return messages.at(i); };
        void addMsg(const char * msg) { messages.push_back(msg); botMsg = getNumMsgs() - 1; };
        int topMsg;
        int botMsg;

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

