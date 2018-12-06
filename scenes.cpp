
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include "assets.hpp"
#include "main.hpp"
#include "sound.hpp"
#include <thread>

using namespace std;

void Scene::move_ship(int a, int b)
{
    Ship *s = get_ship();
    s->move(s->getx()+a, s->gety()+b);
}

Scene1::Scene1()
{
    go = new vector<GameObject*>();
    go->push_back(new Ship(29,35));
    //thread song_t2(play_song, "touhou1.mp3");
    //song_t2.detach();
    stage = 1;
}

void Scene1::draw(WINDOW *w)
{
//    get_ship()->draw();
    for(GameObject *o : *(go))
    {
        o->draw();
    }

    // if((b++) >= 20000)
    // {
    //     wbkgd(w, COLOR_PAIR((rand() % 4 + 1)));
    //     b = 0;
    // }
}

void Scene::remove_from_scene(GameObject *o)
{
    vector<GameObject*> *go = get_go();
    go->erase(remove(go->begin(), go->end(), o), go->end());
    delete o;
}

void Scene1::update()
{
    for(GameObject *o : *(go))
    {
        if(o)
            if(o->get_type() == ObjectType::bullet)
            {
                Bullet *b = (Bullet *)o;
                if(!b->advance())
                    remove_from_scene(o);

                GameObject *cl;
                if((cl = b->colided()))
                    switch (cl->get_type())
                    {
                        case ObjectType::enemy:
                            if(b->from() != cl->get_type())
                            {
                                remove_from_scene(cl);
                                remove_from_scene(o);
                                add_score(500);
                            }
                        break;

                        case ObjectType::ship:
                            if(b->from() != cl->get_type())
                                if(!get_cheats()[Cheat::god])
                                    game_over();
                        break;
                    }
            }
            else if(o->get_type() == ObjectType::enemy)
            {
                EnemyShip *es = (EnemyShip *)o;
                es->advance();
                es->shoot();
            }
    }
    
    if((a++) >= 5000)
    {
        if((rand() % 100) >= 80)
            insert_object(new EnemyShip((rand() % 59 + 1), 1));
        a = 0;
    }

    if(get_score() >= 5000 && get_score()<= 10000)
        stage = 2;
    else if(get_score()>= 11000 && get_score()<= 45000)
        stage = 3;
}

std::vector<GameObject*> *Scene1::get_go() { return go; }

int Scene1::get_stage()
{
    return stage;
}

void Scene::insert_object(GameObject *o)
{
    vector<GameObject*> *go = get_go();
    if(go->size() <= 149)
        go->push_back(o);
}

Ship *Scene1::get_ship()
{
    for(GameObject *e : *(go))
    {
        if(e->get_type() == ObjectType::ship)
            return (Ship *)e;
    }
}

void Scene1::event(EventType e)
{
    switch(e)
    {
        case EventType::keyboard:
            
        break;
    }
}

