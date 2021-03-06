#ifndef WINDOW_H 
#define WINDOW_H 

#include <ncurses.h>

#include "../model/ModelDriver.h"

class Window
{
    protected:
        WINDOW * win;
        ModelDriver * modelDriver; 
        char * name;
    public:
        Window(int h, int w, int y, int x, const char * n, ModelDriver * md);
        ~Window();
        virtual void draw();
        WINDOW * getWindow() { return win; };
};

class FirstRunWindow : public Window
{
    private:
        void shouldHighlight(int button);
        void drawInfo();
        void drawButtons();
        void drawConnectMessage();
    public:
        FirstRunWindow(int h, int w, int y, int x, const char * n, ModelDriver * md) : Window(h, w, y, x, n, md) { };
        void draw();
};

class ChatWindow : public Window
{
    private:
        void drawMessages();
    public:
        ChatWindow(int h, int w, int y, int x, const char * n, ModelDriver * md) : Window(h, w, y, x, n, md) { };
        void draw();
};

class UserWindow : public Window
{
    private:
        void rowHighlight();
    public:
        UserWindow(int h, int w, int y, int x, const char * n, ModelDriver * md) : Window(h, w, y, x, n, md) { };
        void draw();
};

class RoomWindow : public Window
{
    private:
        void rowHighlight();
    public:
        RoomWindow(int h, int w, int y, int x, const char * n, ModelDriver * md) : Window(h, w, y, x, n, md) { };
        void draw();
};

class CreateRoomWindow : public Window
{
    public:
        CreateRoomWindow(int h, int w, int y, int x, const char * n, ModelDriver * md) : Window(h, w, y, x, n, md) { };
        void draw();
};

#endif

