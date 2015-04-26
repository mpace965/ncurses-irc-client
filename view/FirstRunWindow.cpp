#include <ncurses.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void FirstRunWindow::draw()
{
    if (modelDriver->getSelectedWindow() == FIRSTWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HIGHLIGHT));
    }
    Window::draw();

    mvwprintw(win, 1, 1, "Welcome to CursesClient for IRCServer.");
    mvwprintw(win, 2, 1, "It looks like this is your first run, please enter a username and password.");
    mvwprintw(win, 3, 1, "You will also have to supply the port of your server.");
    mvwprintw(win, 4, 1, "Use tab to toggle between the fields, and enter to submit.");
    mvwprintw(win, 5, 1, "Then run \'CursesClient <username> <password> <port>\' to connect.");
    mvwprintw(win, 6, 1, "Happy chatting!");

    wrefresh(win);
}

