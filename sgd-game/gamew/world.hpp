#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "spritesheet.hpp"

enum Direction {
    UP, LEFT, RIGHT, DOWN, NO
};

enum BlockStatus {
    NONE, BLOCK, SCORE, WIN, DEATH
};

enum Block {
    AIR = 0,
    WALL = 1,
    DIRT = 2,
    ROCK = 3,
    LAVA = 4,
    START = 5,
    FINISH = 6,
    DIAMOND = 7
};

struct MovableBlock {
    Block block;
    int x;
    int y;
};

class World {
    private:
        int sizeX, sizeY; // Size of world
        int renderX, renderY; // World render offset
        SDL_Renderer * renderer;
        Spritesheet spritesheet;
        std::vector<std::vector<Block>> map; 
        //std::vector<MovableBlock> movableBlocks;
        std::ifstream inFile;
    public:
        World();
        World(SDL_Renderer * renderer);
        void render_world();
        void level_load(const char *path);
        void level_unload();
        void load_block_textures();
        SDL_Rect player_get_position();
        void player_render(int x, int y, Direction direction);
        BlockStatus player_check_next_block(int x, int y, Direction direction);
        BlockStatus check_block(int x, int y);
        void move_camera_to_player(int playerX, int playerY);
        void objects_move(int playerX, int playerY); //MVP
};