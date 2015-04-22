#ifndef WINDOW_H 
#define WINDOW_H 

#define CHATWINDOW 0
#define USERWINDOW 1
#define ROOMWINDOW 2
#define HIGHLIGHT 1 

#include <ncurses.h>

class Window
{
    protected:
        WINDOW * win;
        char * name;
    public:
        Window(int h, int w, int y, int x, const char * n);
        ~Window();
        virtual void draw();
};

class ChatWindow : public Window
{
    public:
        ChatWindow(int h, int w, int y, int x, const char * n) : Window(h, w, y, x, n) { };
        void draw();
};

class UserWindow : public Window
{
    public:
        UserWindow(int h, int w, int y, int x, const char * n) : Window(h, w, y, x, n) { };
        void draw();
};

class RoomWindow : public Window
{
    public:
        RoomWindow(int h, int w, int y, int x, const char * n) : Window(h, w, y, x, n) { };
        void draw();
};

#endif

