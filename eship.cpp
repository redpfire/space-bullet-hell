
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "assets.hpp"

EnemyShip::EnemyShip(int wx, int wy)
{
    x = wx;
    y = wy;
}

void EnemyShip::draw()
{
    mvprintw(y,x,"@");
}

void EnemyShip::advance()
{
    if((b++) >= 6000-(get_curr_scene()->get_stage()-1*600))
    {
        int r = rand() % 100;
        if((y++) >= 39)
        {
            get_curr_scene()->remove_from_scene(this);
            return;
        }

        if(r >= 0 && r <= 35)
            x = (x-1 <= 0) ? 0 : x-1 ;
        else if(r >= 61 && r <= 100)
            x = (x+1 >= 59) ? 59 : x+1 ;

        b = 0;
    }
}

int EnemyShip::getx() { return x; }
int EnemyShip::gety() { return y; }

GameObject *EnemyShip::colided()
{
    Scene *s = get_curr_scene();
    for(GameObject *g : *(s->get_go()))
    {
        if(g->get_type() != ObjectType::enemy)
            if(g->getx() == x && g->gety() == y)
                return g;
    }
    return 0;
}

void EnemyShip::shoot()
{
    if((a++) >= 20000-(get_curr_scene()->get_stage()-1*900))
    {
        Scene *s = get_curr_scene();
        if(s->get_stage() == 1)
            s->insert_object(new Bullet(x,y+2,0,-1, ObjectType::enemy));
        else if(s->get_stage() == 2)
        {
            s->insert_object(new Bullet(x, y+2, 0, -1, ObjectType::enemy));
            s->insert_object(new Bullet(x-2, y+1, 1, -1, ObjectType::enemy));
            s->insert_object(new Bullet(x+2, y+1, -1, -1, ObjectType::enemy));
        }
        else if(s->get_stage() == 3)
        {
            s->insert_object(new Bullet(x, y+2, 0, -1, ObjectType::enemy));
            s->insert_object(new Bullet(x-2, y+1, 1, -1, ObjectType::enemy));
            s->insert_object(new Bullet(x+2, y+1, -1, -1, ObjectType::enemy));
            s->insert_object(new Bullet(x-4, y, 1, -1, ObjectType::enemy));
            s->insert_object(new Bullet(x+4, y, -1, -1, ObjectType::enemy));
            s->insert_object(new Bullet(x+6, y-1, 1, -1, ObjectType::enemy));
            s->insert_object(new Bullet(x-6, y-1, -1, -1, ObjectType::enemy));
        }
        a = 0;
    }
}

ObjectType EnemyShip::get_type() { return ObjectType::enemy; }

