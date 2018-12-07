
#include <ncurses.h>
#include "assets.hpp"

Bullet::Bullet(int wx, int wy, int wvelx, int wvely, ObjectType fr)
{
    x = (wx < 0) ? 0 : ((wx > 59) ? 59 : wx);
    y = (wy < 0) ? 0 : ((wy > 39) ? 39 : wy);
    velx = wvelx;
    vely = wvely;
    c = 0;
    f = fr;
}

void Bullet::draw()
{
    mvprintw(y,x, "*");
}

ObjectType Bullet::from()
{
    return f;
}

GameObject *Bullet::colided()
{
    Scene *s = get_curr_scene();
    for(GameObject *g : *(s->get_go()))
    {
        if(g->get_type() != ObjectType::bullet)
            if(g->getx() == x && g->gety() == y)
                return g;
    }
    return 0;
}

bool Bullet::advance()
{
    if(c++ >= ((from()==ObjectType::enemy)
                ? 18-(get_curr_scene()->get_stage()-1)
                :4
                ))
    {
        y -= vely;
        x += velx;
        c = 0;
    }
    if(y < 0 || y > 39 || x < 0 || x > 59)
        return false;
    return true;
}

ObjectType Bullet::get_type() { return ObjectType::bullet; }

int Bullet::getx() { return x; }
int Bullet::gety() { return y; }

