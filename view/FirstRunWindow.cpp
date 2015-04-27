#include <ncurses.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void FirstRunWindow::draw()
{
    drawInfo();
    drawButtons();
    drawConnectMessage();

    if (modelDriver->getSelectedWindow() == FIRSTWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HICOLOR));
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

    msg = "To create a new user, please enter a username and password.";
    mvwprintw(win, 2, center - (int) round(strlen(msg) / 2.0), msg);

    msg = "You will also have to supply the host address and port.";
    mvwprintw(win, 3, center - (int) round(strlen(msg) / 2.0), msg);

    msg = "Use tab to toggle between the fields, i to edit the field, and enter to stop editing.";
    mvwprintw(win, 4, center - (int) round(strlen(msg) / 2.0), msg);

    msg = "Finally, press enter again to send.";
    mvwprintw(win, 5, center - (int) round(strlen(msg) / 2.0), msg);

    msg = "Then run \'CursesClient <username> <password> <host> <port>\' to connect.";
    mvwprintw(win, 6, center - (int) round(strlen(msg) / 2.0), msg);

    msg = "Happy chatting!";
    mvwprintw(win, 7, center - (int) round(strlen(msg) / 2.0), msg);
}

void FirstRunWindow::drawButtons()
{
    shouldHighlight(FRUSER);
    const char * msg = "Username:";
    mvwprintw(win, 10, 1, msg);
    wattroff(win, A_REVERSE);
    wprintw(win, " ");
    wprintw(win, modelDriver->getUsername());
    wclrtoeol(win);

    shouldHighlight(FRPASS);
    msg = "Password:";
    mvwprintw(win, 11, 1, msg);
    wattroff(win, A_REVERSE);
    wprintw(win, " ");
    wprintw(win, modelDriver->getPassword());
    wclrtoeol(win);

    shouldHighlight(FRHOST);
    msg = "Host:";
    mvwprintw(win, 12, 1, msg);
    wattroff(win, A_REVERSE);
    wprintw(win, " ");
    wprintw(win, modelDriver->getHost());
    wclrtoeol(win);

    shouldHighlight(FRPORT);
    msg = "Port:";
    mvwprintw(win, 13, 1, msg);
    wattroff(win, A_REVERSE);
    wprintw(win, " ");
    wprintw(win, modelDriver->getSPort());
    wclrtoeol(win);
}

void FirstRunWindow::drawConnectMessage()
{
    int center = (int) round((1.0/2.0) * COLS);

    if (modelDriver->addUserAttempt == USERDENY) {
        wattron(win, COLOR_PAIR(ERRCOLOR));

        const char * msg = "Error: user already exists.";
        wmove(win, 15, 1);
        wclrtoeol(win);
        mvwprintw(win, 15, center - (int) round(strlen(msg) / 2.0), msg);
        
        wattroff(win, COLOR_PAIR(ERRCOLOR));
    } else if (modelDriver->addUserAttempt == USERACCEPT) {
        wattron(win, COLOR_PAIR(SUCCESSCOLOR));

        const char * msg = "Success! User created. Press escape to exit.";
        wmove(win, 15, 1);
        wclrtoeol(win);
        mvwprintw(win, 15, center - (int) round(strlen(msg) / 2.0), msg);

        wattroff(win, COLOR_PAIR(SUCCESSCOLOR));
    }
}

