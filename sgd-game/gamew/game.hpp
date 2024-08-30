#include <SDL.h>
#include <string>
#include <cstring>
#include <iostream>

#include "world.hpp"

struct Player {
    int hp;
    int x, y;
    short moveFreeze = 0;
    Player() {}
};

class Game{
    private:
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        const short MOVE_FREEZE = 8;
        const short PHYSICS_FREEZE = 10;
        const int MAX_LEVEL = 2;
        int level = 1;
        short physicsFreeze = 0;
        Direction lastMove = NO;
        SDL_Renderer * renderer;
        Player player;
        World world;
    public:
        Game(SDL_Renderer * r);
        ~Game();
        void init();
        void nextLevel(int level);
        void update();
        void render();
};