#include <ncurses.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void ChatWindow::draw()
{
    drawMessages();

    if (modelDriver->getSelectedWindow() == CHATWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HIGHLIGHT));
    }
    Window::draw();

    wrefresh(win);
}

void ChatWindow::drawMessages()
{
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

