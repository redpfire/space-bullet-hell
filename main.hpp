
#include "splash.hpp"

enum Cheat
{
    noclip,
    god
};

void main_loop(WINDOW *);
void debugger(WINDOW *);
void game_over();
void add_score(int);
int get_score();
bool *get_cheats();

