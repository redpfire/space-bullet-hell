
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.hpp"
#include "assets.hpp"

void debugger(WINDOW *w)
{
    curs_set(1);

    int x,y;
    x = y = 0;

    for(;;)
    {
        mvprintw(0,0, "Y:%d,X:%d    ", y, x);
        if(get_curr_scene())
            mvprintw(1,0, "Entities: %d", get_curr_scene()->get_go()->size());
        move(y,x);

        int ch = getch();

        if(ch == 91)
        {
            ch = getch();
            if(ch == 'B')
                y++;
            else if(ch == 'A')
                y--;
            else if(ch == 'D')
                x--;
            else if (ch == 'C')
                x++;

            if(y > 39)
                y = 39;
            else if(y < 0)
                y = 0;

            if(x > 59)
                x = 59;
            else if(x < 0)
                x = 0;

            ch = 0;
        }


        if(ch == '1')
            break;

        refresh();
        sleep(0.1);
    }
    curs_set(0);
}

