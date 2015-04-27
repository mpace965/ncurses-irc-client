#include <ncurses.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void ChatWindow::draw()
{
    drawMessages();

    wattron(win, A_BOLD);
    mvwprintw(win, LINES - 2, 1, "Prompt> ");
    wattroff(win, A_BOLD);

    if (modelDriver->getSelectedWindow() == CHATWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HICOLOR));
    }
    Window::draw();

    wrefresh(win);
}

void ChatWindow::drawMessages()
{
    if (modelDriver->getNumMsgs() > 0) {
        int pageLength = modelDriver->fullPageLength();

        for (int i = modelDriver->topMsg; i < modelDriver->topMsg + pageLength; i++) {
            if (i <= modelDriver->botMsg)
                mvwprintw(win, i - modelDriver->topMsg + 1, 1, modelDriver->getMsg(i));
            else {
                wclrtobot(win);
                break;
            }
        }
    }
}

