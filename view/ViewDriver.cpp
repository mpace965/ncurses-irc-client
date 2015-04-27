#include <ncurses.h>
#include <math.h>

#include "ViewDriver.h"
#include "Window.h"
#include "../model/ModelDriver.h"

ViewDriver::ViewDriver(ModelDriver * md)
{
    initscr();
    curs_set(0);
    raw();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    start_color();
    noecho();

    //Initialize firstrun window
    int starty, startx, width, height;
    starty = 0;
    startx = 0;
    height = LINES;
    width = COLS;
    firstRun = new FirstRunWindow(height, width, starty, startx, "New User", md);
    
    //Initialize chat window 
    starty = 0;
    startx = 0;
    height = (int) round(CHAT_HEIGHT * LINES);
    width = (int) round(CHAT_WIDTH * COLS);
    chat = new ChatWindow(height, width, starty, startx, "Messages", md);

    //Initialize rooms window
    starty = 0;
    startx = (int) round(CHAT_WIDTH * COLS);
    height = (int) round(SIDE_HEIGHT * LINES); //to make them the same length
    width = (int) round(SIDE_WIDTH * COLS);
    rooms = new RoomWindow(height, width, starty, startx, "Rooms - c to create", md);

    //Initialize createRoom window
    createRoom = new CreateRoomWindow(height, width, starty, startx, "Create Room", md);

    //Initialize user window
    starty = (int) round(SIDE_HEIGHT * LINES);
    startx = (int) round(CHAT_WIDTH * COLS);
    height = (int) round(SIDE_HEIGHT * LINES) - 1;
    width = (int) round(SIDE_WIDTH * COLS);
    users = new UserWindow(height, width, starty, startx, "Users", md);
}

ViewDriver::~ViewDriver()
{
    delete chat;
    delete rooms;
    delete users;
    curs_set(1);
    endwin();
}

void ViewDriver::drawFirstRun()
{
    firstRun->draw();
    refresh();
}

void ViewDriver::draw()
{
    chat->draw();
    rooms->draw();
    users->draw();
    createRoom->draw();
    refresh();
}

