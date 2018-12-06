
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include "main.hpp"
#include "assets.hpp"
#include "sound.hpp"
#include <thread>

using namespace std;

static Scene *curr_scene;
static int score = 0;

void game_over_scene();

static bool go = false;

int main(int argc, char **argv)
{
    WINDOW *w = initscr();
    noecho();
    curs_set(FALSE);
    nodelay(w, 1);
    //start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);

    //init_sound();

    //thread song_t1(play_song, "legend.mp3");

    splash_screen(w);

    main_loop(w);

    endwin();
    sound_cleanup();
}

Scene *get_curr_scene() { return curr_scene; }

void game_over()
{
    go = true;
}

void game_over_scene()
{
    clear();
    mvprintw(5,16, "Gordon, your journey is over.");
    mvprintw(7,11, "Your failure was tragic to our empire.");
    mvprintw(10,13,"Your family is as dead as you are.");
    mvprintw(12,25,"EAT  PANT");

    mvprintw(32,16,"SCORE: %d", score);

    int a = 0;
    bool v = true;

    for(;;)
    {
        if(a >= 5000)
        {
            v = !v;
            a = 0;
        }

        if(!v)
            mvprintw(29,19, "                    ");
        else
            mvprintw(29,19, "Press Enter to exit.");


        if(getch() == '\n')
            break;

        a++;
        refresh();
        sleep(0.1);
    }
}

static bool cheats[64] = {false};

void add_score(int i)
{
    score += i;
}

bool *get_cheats()
{ return cheats; }

static bool debug_info = false;

int get_score() { return score; }

void main_loop(WINDOW *w)
{
    int mx = 60;
    int my = 40;

    curr_scene = new Scene1();

    for(;;)
    {
        erase();

        curr_scene->update();

        if(go)
            break;

        curr_scene->draw(w);

        mvprintw(34,46, "SCORE: %d", score);
        mvprintw(2,39, "%s", (cheats[Cheat::noclip]) ? "NOCLIP" : "");
        mvprintw(1,39, "%s", (cheats[Cheat::god]) ? "GOD MODE": "");

        if(debug_info)
            if(curr_scene->get_go())
                mvprintw(0,0,"ENTITIES: %d", curr_scene->get_go()->size());

        mvprintw(35,47,"STAGE %d", curr_scene->get_stage());

        char ch = getch();
        if(ch == 'q')
            break;

        switch(ch)
        {
            case '1':
                debugger(w);
            break;
            case '~':
                debug_info = !debug_info;
            break;
            case '2':
                cheats[Cheat::noclip] = !cheats[Cheat::noclip];
                if(!cheats[Cheat::noclip])
                {
                    Ship *s = curr_scene->get_ship();
                    s->move(s->getx(),s->getiy());
                }
            break;
            case '0':
                cheats[Cheat::god] = !cheats[Cheat::god];
            break;
            case 91:
                ch = getch();
                if(ch == 'B' && cheats[Cheat::noclip])
                    curr_scene->move_ship(0,1);
                else if(ch == 'A' && cheats[Cheat::noclip])
                    curr_scene->move_ship(0,-1);
                else if(ch == 'D')
                    curr_scene->move_ship(-1,0);
                else if (ch == 'C')
                    curr_scene->move_ship(1,0);
            break;
            case ' ':
                Ship *s = curr_scene->get_ship();
                s->shoot();
            break;
        }

        refresh();
        sleep(1/15);
    }
    game_over_scene();
}

