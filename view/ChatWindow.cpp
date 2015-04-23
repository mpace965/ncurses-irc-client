#include <ncurses.h>

#include "../globals.h"
#include "Window.h"
#include "../model/ModelDriver.h"

void ChatWindow::draw()
{
    if (modelDriver->getSelectedWindow() == CHATWINDOW) {
        wattron(win, A_BOLD);
        wattron(win, COLOR_PAIR(HIGHLIGHT));
    }
    Window::draw();

    wrefresh(win);
}

