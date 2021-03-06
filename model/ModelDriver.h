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
        bool * running;

        const char * username;
        const char * password;
        const char * host;
        const char * sport;
        int port;

        std::vector<const char *> users;
        std::vector<const char *> rooms;
        std::vector<const char *> messages;

        int lastUpdated;

        int open_client_socket();
    public:
        ModelDriver(bool * run);
        ~ModelDriver();
        void updateFirstRun();
        void update();
        
        void badUser();
        void digestRooms(char * roomList);
        void digestUsers(char * userList);
        void digestMessages(char * msgList);

        int selectedFirstRunButton;
        int addUserAttempt; 

        void setUsername(const char * name) { username = strdup(name); };
        const char * getUsername() { return username; };
        void setPassword(const char * pw) { password = strdup(pw); };
        const char * getPassword() { return password; };
        void setHost(const char * h) { host = strdup(h); };
        const char * getHost() { return host; };
        void setSPort(const char * p) { sport = strdup(p); };
        const char * getSPort() { return sport; };
        void setPort(int p) { port = p; };
        int getPort() { return port; };

        int getSelectedWindow() { return selectedWindow; };
        void setSelectedWindow(int i) { selectedWindow = i; };

        int fullPageLength() { return (int) round(CHAT_HEIGHT * LINES) - 3; };
        int halfPageLength() { return (int) round(SIDE_HEIGHT * LINES) - 3; }; //-3 to account for the borders

        int getNumUsers() { return users.size(); };
        const char * getUserInRoom(int i) { return users.at(i); };
        void addUser(const char * name) { users.push_back(name); };
        void clearUser() { users.clear(); };
        int userHighlighted;
        int userPage;

        int getNumRooms() { return rooms.size(); };
        const char * getRoom(int i) { return rooms.at(i); };
        void addRoom(const char * name) { rooms.push_back(name); };
        int roomHighlighted;
        int roomPage;
        const char * selectedRoom;

        int getNumMsgs() {return messages.size(); };
        const char * getMsg(int i) { return messages.at(i); };
        void addMsg(const char * msg) { messages.push_back(msg); botMsg = getNumMsgs() - 1; };
        void clearMsg() { messages.clear(); };
        int topMsg;
        int botMsg;

        int sendCommand(const char * command, const char * args, char * response); 
};

#endif

