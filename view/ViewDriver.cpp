#include <ncurses.h>
#include <math.h>

#include "ViewDriver.h"
#include "Window.h"
#include "../model/ModelDriver.h"

ViewDriver::ViewDriver(ModelDriver * modDrive)
{
    initscr();
    curs_set(0);
    raw();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    start_color();
    noecho();

    md = modDrive;

    //Initialize chat window 
    int starty, startx, width, height;
    starty = 0;
    startx = 0;
    height = (int) round(CHAT_HEIGHT * LINES);
    width = (int) round(CHAT_WIDTH * COLS);
    chat = new ChatWindow(height, width, starty, startx, "Messages");

    //Initialize rooms window
    starty = 0;
    startx = (int) round(CHAT_WIDTH * COLS);
    height = (int) round(SIDE_HEIGHT * LINES);
    width = (int) round(SIDE_WIDTH * COLS);
    rooms = new RoomWindow(height, width, starty, startx, "Rooms");

    //Initialize user window
    starty = (int) round(SIDE_HEIGHT * LINES);
    startx = (int) round(CHAT_WIDTH * COLS);
    height = (int) round(SIDE_HEIGHT * LINES);
    width = (int) round(SIDE_WIDTH * COLS);
    users = new UserWindow(height, width, starty, startx, "Users");
}

ViewDriver::~ViewDriver()
{
    delete chat;
    delete rooms;
    delete users;
    curs_set(1);
    endwin();
}

void ViewDriver::draw()
{
    chat->draw();
    rooms->draw();
    users->draw();
}

