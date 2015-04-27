#include <ncurses.h>
#include <string.h>
#include <math.h>

#include "../globals.h"
#include "ControllerDriver.h"
#include "../model/ModelDriver.h"
#include "../view/ViewDriver.h"

ControllerDriver::ControllerDriver(bool * run, ModelDriver * md, ViewDriver * vd)
{
    running = run;
    modelDriver = md;
    viewDriver = vd;
}

ControllerDriver::~ControllerDriver()
{

}

void ControllerDriver::getInputFirstRun()
{
    int ch = getch();

    if (ch != ERR) {
        switch (ch) {
            case 27: //escape
                *running = false;
                break;
            case 'i':
                firstRunTextInput();
                break;
            case '\t':
                firstRunButtonToggle();
                break;
            case '\n':
                addUser();
                break;
        }
    }
}

void ControllerDriver::firstRunTextInput()
{
    if (modelDriver->getSelectedWindow() != FIRSTWINDOW)
        return;

    switch (modelDriver->selectedFirstRunButton) {
        char input[100];

        case FRUSER:
            inputOn();

            mvwprintw(viewDriver->firstRun->getWindow(), 10, 1 + strlen("Username: "),  SPACES);
            mvwgetnstr(viewDriver->firstRun->getWindow(), 10, 1 + strlen("Username: "), input, 100);
            modelDriver->setUsername(input);

            inputOff();
            break;
        case FRPASS:
            inputOn();

            mvwprintw(viewDriver->firstRun->getWindow(), 11, 1 + strlen("Password: "), SPACES);
            mvwgetnstr(viewDriver->firstRun->getWindow(), 11, 1 + strlen("Password: "), input, 100);
            modelDriver->setPassword(input);

            inputOff();
            break;
        case FRHOST:
            inputOn();

            mvwprintw(viewDriver->firstRun->getWindow(), 12, 1 + strlen("Host: "), SPACES);
            mvwgetnstr(viewDriver->firstRun->getWindow(), 12, 1 + strlen("Host: "), input, 100);
            modelDriver->setHost(input);

            inputOff();
            break;
        case FRPORT:
            inputOn();

            mvwprintw(viewDriver->firstRun->getWindow(), 13, 1 + strlen("Port: "), SPACES);
            mvwgetnstr(viewDriver->firstRun->getWindow(), 13, 1 + strlen("Port: "), input, 100);
            modelDriver->setSPort(input);
            modelDriver->setPort(atoi(input));

            inputOff();
            break;
    }
}

void ControllerDriver::inputOn()
{
    nodelay(stdscr, FALSE);
    echo();
    curs_set(1);
}

void ControllerDriver::inputOff()
{
    curs_set(0);
    noecho();
    nodelay(stdscr, TRUE);
}

void ControllerDriver::firstRunButtonToggle()
{
    if (modelDriver->getSelectedWindow() != FIRSTWINDOW)
        return;

    switch (modelDriver->selectedFirstRunButton) {
        case FRUSER:
            modelDriver->selectedFirstRunButton = FRPASS;
            break;
        case FRPASS:
            modelDriver->selectedFirstRunButton = FRHOST;
            break;
        case FRHOST:
            modelDriver->selectedFirstRunButton = FRPORT;
            break;
        case FRPORT:
            modelDriver->selectedFirstRunButton = FRUSER;
            break;
    }
}

void ControllerDriver::addUser()
{
    char response[MAX_RESPONSE];
    modelDriver->sendCommand("ADD-USER", "", response);

    if (!strcmp(response, DENIEDMSG)) {
        modelDriver->addUserAttempt = USERDENY;
    } else if (!strcmp(response, OKMSG)) {
        modelDriver->addUserAttempt = USERACCEPT;
    }
}

void ControllerDriver::getInput()
{
    int ch = getch();

    if (ch != ERR) {
        switch (ch) {
            case 27: //escape
                *running = false;
                break;
            case '\n':
                roomSelect();
                break;
            case 'i':
                messageTextInput();
                break;
            case KEY_UP:
                chatScroll(ch);
                sideScroll(ch);
                break;
            case KEY_DOWN:
                chatScroll(ch);
                sideScroll(ch);
                break;
            case '\t':
                switchFocus();
                break;
        }
    }
}

void ControllerDriver::switchFocus()
{
    switch (modelDriver->getSelectedWindow()) {
        case CHATWINDOW:
            modelDriver->setSelectedWindow(ROOMWINDOW);
            break;
        case ROOMWINDOW:
            modelDriver->setSelectedWindow(USERWINDOW);
            break;
        case USERWINDOW:
            modelDriver->setSelectedWindow(CHATWINDOW);
            break;
    }
}

void ControllerDriver::messageTextInput()
{
    if (modelDriver->getSelectedWindow() != CHATWINDOW || !strcmp(modelDriver->selectedRoom, ""))
        return;

    char input[500];

    inputOn();
    mvwgetnstr(viewDriver->chat->getWindow(), LINES - 2, 1 + strlen("Prompt> "), input, 500);
    inputOff();

    char args[600];
    char response[MAX_RESPONSE];

    sprintf(args, "%s %s", modelDriver->selectedRoom, input);

    modelDriver->sendCommand("SEND-MESSAGE", args, response);
    
    char number[100];
    sprintf(number, "%d %s", modelDriver->getNumMsgs(), modelDriver->selectedRoom);
    modelDriver->sendCommand("GET-MESSAGES", number, response);
    modelDriver->digestMessages(response);
}

void ControllerDriver::roomSelect()
{
    if (modelDriver->getSelectedWindow() != ROOMWINDOW)
        return;

    const char * currentRoom = modelDriver->selectedRoom;

    char response[MAX_RESPONSE];

    char leaveRoom[100];
    sprintf(leaveRoom, "%s leaves the room.", modelDriver->selectedRoom);
    modelDriver->sendCommand("SEND-MESSAGE", leaveRoom, response);

    if (strcmp(currentRoom, "")) 
        modelDriver->sendCommand("LEAVE-ROOM", currentRoom, response);

    if (strcmp(currentRoom, modelDriver->getRoom(modelDriver->roomHighlighted))) {
        modelDriver->sendCommand("ENTER-ROOM", modelDriver->getRoom(modelDriver->roomHighlighted), response);
        modelDriver->selectedRoom = modelDriver->getRoom(modelDriver->roomHighlighted);

        modelDriver->sendCommand("GET-USERS-IN-ROOM", modelDriver->selectedRoom, response);
        modelDriver->digestUsers(response);

        modelDriver->clearMsg();
        wmove(viewDriver->chat->getWindow(), 0,0);
        wclrtobot(viewDriver->chat->getWindow());

        char enteredRoom[100];
        sprintf(enteredRoom, "%s entered the room.", modelDriver->selectedRoom);
        modelDriver->sendCommand("SEND-MESSAGE", enteredRoom, response); 

        char number[100];
        sprintf(number, "%d %s", modelDriver->getNumMsgs(), modelDriver->selectedRoom);
        modelDriver->sendCommand("GET-MESSAGES", number, response);
        modelDriver->digestMessages(response);
    } else {
        modelDriver->selectedRoom = "";
        modelDriver->clearMsg();

        modelDriver->clearUser();
        wmove(viewDriver->users->getWindow(), 0, 0);
        wclrtobot(viewDriver->users->getWindow());

        wmove(viewDriver->chat->getWindow(), 0,0);
        wclrtobot(viewDriver->chat->getWindow());
    }
}


void ControllerDriver::chatScroll(int ch)
{
    if (modelDriver->getSelectedWindow() != CHATWINDOW)
        return;

    if (ch == KEY_UP && modelDriver->topMsg > 0) {
        modelDriver->topMsg -= 1;
    } else if (ch == KEY_DOWN && modelDriver->topMsg != modelDriver->botMsg) {
        modelDriver->topMsg += 1;
    }
}

void ControllerDriver::sideScroll(int ch)
{
    int * highlight = 0;
    int * page = 0;
    int numberOf = 0;
    int pageLength = modelDriver->halfPageLength();

    if (modelDriver->getSelectedWindow() == USERWINDOW) {
        highlight = &modelDriver->userHighlighted;
        page = &modelDriver->userPage;
        numberOf = modelDriver->getNumUsers();
    } else if (modelDriver->getSelectedWindow() == ROOMWINDOW) {
        highlight = &modelDriver->roomHighlighted;
        page = &modelDriver->roomPage;
        numberOf = modelDriver->getNumRooms();
    } else {
        return;
    }

    if (ch == KEY_UP) {
        if (*highlight > 0) {
            *highlight -= 1;

            if (*highlight == *page - 1)
                *page -= pageLength;
        }
    } else if (ch == KEY_DOWN) {
        if (*highlight < numberOf - 1) {
            *highlight += 1;

            if (*highlight == *page + pageLength)
                *page += pageLength;
        }
    }
}

