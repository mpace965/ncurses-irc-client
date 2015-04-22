#ifndef WINDOW_H 
#define WINDOW_H 

#define HIGHLIGHT 1 

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
};

class ChatWindow : public Window
{
    public:
        ChatWindow(int h, int w, int y, int x, const char * n, ModelDriver * md) : Window(h, w, y, x, n, md) { };
        void draw();
};

class UserWindow : public Window
{
    public:
        UserWindow(int h, int w, int y, int x, const char * n, ModelDriver * md) : Window(h, w, y, x, n, md) { };
        void draw();
};

class RoomWindow : public Window
{
    public:
        RoomWindow(int h, int w, int y, int x, const char * n, ModelDriver * md) : Window(h, w, y, x, n, md) { };
        void draw();
};

#endif

