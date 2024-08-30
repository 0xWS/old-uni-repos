#include "game.hpp"

Game::Game(SDL_Renderer * r) {
    renderer = r;
}

Game::~Game() {
    world.level_unload();
}

void Game::init() {
    world = World(renderer);
    world.load_block_textures();
    world.level_load("resources/levels/1.lvl");
    SDL_Rect pos = world.player_get_position();
    player.x = pos.x;
    player.y = pos.y;
}

void Game::nextLevel(int level) {
    std::string levelName = "resources/levels/" + std::to_string(level) + ".lvl";
    std::cout << "Unloading level" << std::endl;
    world.level_unload();
    std::cout << "Loading level" << std::endl;
    world.level_load(levelName.c_str());
    std::cout << "Level loaded" << std::endl;
    SDL_Rect pos = world.player_get_position();
    player.x = pos.x;
    player.y = pos.y;
}

void Game::update() {
    if(player.moveFreeze <= 0) {
        if (
            state[SDL_SCANCODE_RIGHT] ||
            state[SDL_SCANCODE_LEFT] || 
            state[SDL_SCANCODE_UP] ||
            state[SDL_SCANCODE_DOWN]
            ) {
            BlockStatus nextBlock;
            if (state[SDL_SCANCODE_RIGHT]) {
                nextBlock = world.player_check_next_block(player.x, player.y, RIGHT);
                if(nextBlock != BLOCK) {
                    player.x++;
                    lastMove = RIGHT;
                }
            } else
            if (state[SDL_SCANCODE_LEFT]) {
                nextBlock = world.player_check_next_block(player.x, player.y, LEFT);
                if(nextBlock != BLOCK) {
                    player.x--;\
                    lastMove = LEFT;
                }
            } else
            if (state[SDL_SCANCODE_UP]) {
                nextBlock = world.player_check_next_block(player.x, player.y, UP);
                if(nextBlock != BLOCK) {
                    player.y--;
                    lastMove = UP;
                }
            } else
            if (state[SDL_SCANCODE_DOWN]) {
                nextBlock = world.player_check_next_block(player.x, player.y, DOWN);
                if(nextBlock != BLOCK) {
                    player.y++;
                    lastMove = DOWN;
                }
            }
            if(nextBlock == WIN)  {
                if(level != MAX_LEVEL) {
                    level++;
                    nextLevel(level);
                } else {
                    //no elo wygrałeś
                }
            }
            if(nextBlock != BLOCK)  {
                player.moveFreeze = MOVE_FREEZE;
            }
        }
    }
    player.moveFreeze--;
    if(physicsFreeze <= 0) {
        world.objects_move(player.x, player.y);
        physicsFreeze = PHYSICS_FREEZE;
    }
    physicsFreeze--;
}

void Game::render() {
    world.move_camera_to_player(player.x, player.y);
    world.render_world();
    if(player.moveFreeze <= 0) {
        world.player_render(player.x, player.y, NO);
    } else {
        world.player_render(player.x, player.y, lastMove);
    }
}