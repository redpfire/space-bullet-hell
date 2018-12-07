
#include <vector>
#include <ncurses.h>

enum ObjectType
{
    invalid,
    ship,
    bullet,
    enemy
};

class GameObject
{
    public:
        virtual int getx() = 0;
        virtual int gety() = 0;
        virtual void draw() = 0;
        virtual ObjectType get_type() = 0;
};

class Bullet : public GameObject
{
    private:
        int x,y,velx,vely;
        int c;
        ObjectType f;
    public:
        int getx();
        int gety();
        void draw();
        bool advance();
        ObjectType from();
        ObjectType get_type();
        GameObject *colided();
        Bullet(int, int, int, int, ObjectType);
};

class Ship : public GameObject
{
    private:
        int x,y,hp;
        int ix,iy;
    public:
        Ship(int,int);
        void move(int, int);
        int getx();
        int gety();
        int getix();
        int getiy();
        void draw();
        void shoot();
        GameObject *colided();
        ObjectType get_type();
};

class EnemyShip : public GameObject
{
    private:
        int x,y;
        int a, b;
    public:
        EnemyShip(int,int);
        void advance();
        int getx();
        int gety();
        void shoot();
        void draw();
        GameObject *colided();
        ObjectType get_type();

};

enum EventType
{
    keyboard
};

class Scene
{
    public:
        virtual Ship *get_ship() = 0;
        virtual void draw(WINDOW *) = 0;
        void move_ship(int, int);
        void insert_object(GameObject *);
        virtual std::vector<GameObject*> *get_go() = 0;
        virtual void update() = 0;
        void remove_from_scene(GameObject *);
        virtual int get_stage() = 0;
        virtual ~Scene() {}
};

class Scene1 : public Scene
{
    private:
        int a,b,stage;
    public:
        std::vector<GameObject*> *go;
        Ship *get_ship();
        void draw(WINDOW *);
        void update();
        int get_stage();
        std::vector<GameObject*> *get_go();
        Scene1();
};

Scene *get_curr_scene();

