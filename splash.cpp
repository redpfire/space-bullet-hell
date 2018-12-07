
#include <ncurses.h>
#include <unistd.h>
#include "splash.hpp"

using namespace std;

void splash_screen(WINDOW *w)
{
    mvprintw(6,10, "Hello Gordon, we have a mission for you");
    mvprintw(8,11,  "You'll be given a brand new ship soon" );
    mvprintw(10,12,  "The Cosmic Mass have attacked again"  );
    mvprintw(12,17,       "A trivial task for you..."       );
    mvprintw(14,24,              "Ain't it?"                );

    mvprintw(19,5, "CONTROLS:"          );
    mvprintw(20,9, "Left Arrow  - left" );
    mvprintw(21,9, "Right Arrow - right");
    mvprintw(22,9, "Space       - shoot");
    mvprintw(23,9, "Q           - quit");


    int a = 0;
    bool v = true;

    for(;;)
    {
        if(a >= 20)
        {
            v = !v;
            a = 0;
        }

        if(!v)
            mvprintw(30,20, "                    ");
        else
            mvprintw(30,20, "Press Enter to start");


        if(getch() == '\n')
            break;

        a++;
        refresh();
        usleep(20000);
    }
}

