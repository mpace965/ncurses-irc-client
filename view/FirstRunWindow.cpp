#include <ncurses.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void FirstRunWindow::draw()
{
    drawInfo();
    drawButtons();

    if (modelDriver->getSelectedWindow() == FIRSTWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HIGHLIGHT));
    }
    Window::draw();

    wrefresh(win);
}

void FirstRunWindow::shouldHighlight(int button)
{
    if (modelDriver->selectedFirstRunButton == button)
        wattron(win, A_REVERSE);
}

void FirstRunWindow::drawInfo()
{
    int center = (int) round((1.0/2.0) * COLS);

    const char * msg = "Welcome to the CursesClient for IRCServer.";
    mvwprintw(win, 1, center - (int) round(strlen(msg) / 2.0), msg);

    msg = "It looks like this is your first run, please enter a username and password.";
    mvwprintw(win, 2, center - (int) round(strlen(msg) / 2.0), msg);

    msg = "You will also have to supply the host address and port.";
    mvwprintw(win, 3, center - (int) round(strlen(msg) / 2.0), msg);

    msg = "Use tab to toggle between the fields, and enter to submit.";
    mvwprintw(win, 4, center - (int) round(strlen(msg) / 2.0), msg);

    msg = "Then run \'CursesClient <username> <password> <host> <port>\' to connect.";
    mvwprintw(win, 5, center - (int) round(strlen(msg) / 2.0), msg);

    msg = "Happy chatting!";
    mvwprintw(win, 6, center - (int) round(strlen(msg) / 2.0), msg);
}

void FirstRunWindow::drawButtons()
{
    shouldHighlight(FRUSER);
    const char * msg = "Username:";
    mvwprintw(win, 10, 1, msg);
    wattroff(win, A_REVERSE);

    shouldHighlight(FRPASS);
    msg = "Password:";
    mvwprintw(win, 10, (int) round(COLS / 4.0) - (int) round(strlen(msg) / 2.0), msg);
    wattroff(win, A_REVERSE);

    shouldHighlight(FRHOST);
    msg = "Host:";
    mvwprintw(win, 10, (int) round(COLS / 2.0) - (int) round(strlen(msg) / 2.0), msg);
    wattroff(win, A_REVERSE);

    shouldHighlight(FRPORT);
    msg = "Port:";
    mvwprintw(win, 10, (int) round(COLS * (3.0 / 4.0)) - (int) round(strlen(msg) / 2.0), msg);
    wattroff(win, A_REVERSE);
}

