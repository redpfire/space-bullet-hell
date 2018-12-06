
#include "assets.hpp"
#include <ncurses.h>

Ship::Ship(int wx, int wy)
{
    x = ix = wx;
    y = iy = wy;
    hp = 100;
}

void Ship::move(int wx, int wy)
{
    x = (wx>=59)?59:((wx<=0)?0:wx);
    y = (wy>=39)?39:((wy<=0)?0:wy);
}

void Ship::shoot()
{
    Scene *s = get_curr_scene();
    s->insert_object(new Bullet(x,y-1, 0, 1, ObjectType::ship));
}

void Ship::draw()
{
    mvprintw(y,x, "^");
}

GameObject *Ship::colided()
{
    Scene *s = get_curr_scene();
    for(GameObject *g : *(s->get_go()))
    {
        if(g->get_type() != ObjectType::ship)
            if(g->getx() == x && g->gety() == y)
                return g;
    }
    return 0;
}

int Ship::getx() { return x; }
int Ship::gety() { return y; }

ObjectType Ship::get_type() { return ObjectType::ship; }

int Ship::getix() { return ix; }
int Ship::getiy() { return iy; }
