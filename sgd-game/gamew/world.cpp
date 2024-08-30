#include <SDL.h>

#include "world.hpp"

const int BLOCKSIZE = 48;

int anim = 0;
int panim = 0;

World::World() {
    
}

World::World(SDL_Renderer * renderer) {
    this->renderer = renderer;
    this->renderX = 0;
    this->renderY = 0;
}

void World::render_world() {
    int sizeY = map.size();
    int sizeX = map.at(0).size();
    for(int mapY = 0; mapY < sizeY; mapY++) {
        for(int mapX = 0; mapX < sizeX; mapX++) {
            SDL_Rect blockRect = {mapX * BLOCKSIZE + renderX, mapY * BLOCKSIZE + renderY, BLOCKSIZE, BLOCKSIZE };
            Block blockId = map.at(mapY).at(mapX);
            switch(blockId) {
                case AIR:
                    spritesheet.select_sprite(7, 1);
                    spritesheet.draw_selected_sprite(&blockRect);
                    break;
                case WALL:
                    spritesheet.select_sprite(0, 3);
                    spritesheet.draw_selected_sprite(&blockRect);
                    break;
                case DIRT:
                    spritesheet.select_sprite(4, 3);
                    spritesheet.draw_selected_sprite(&blockRect);
                    break;
                case ROCK:
                    spritesheet.select_sprite(5, 3);
                    spritesheet.draw_selected_sprite(&blockRect);
                    break;
                case LAVA:
                    spritesheet.select_sprite(3, 4);
                    spritesheet.draw_selected_sprite(&blockRect);
                    break;
                case START:
                    spritesheet.select_sprite(7, 1);
                    spritesheet.draw_selected_sprite(&blockRect);
                    break;
                case FINISH:
                    spritesheet.select_sprite(1, 3);
                    spritesheet.draw_selected_sprite(&blockRect);
                    break;
                case DIAMOND:
                    if(anim >=0) spritesheet.select_sprite(0, 4);
                    if(anim >=2*5) spritesheet.select_sprite(0, 5);
                    if(anim >=3*5) spritesheet.select_sprite(0, 6);
                    if(anim >=4*5) spritesheet.select_sprite(0, 7);
                    if(anim >=5*5) spritesheet.select_sprite(1, 4);
                    if(anim >=6*5) spritesheet.select_sprite(1, 5);
                    if(anim >=7*5) spritesheet.select_sprite(1, 6);
                    if(anim >=8*5) spritesheet.select_sprite(1, 7);
                    spritesheet.draw_selected_sprite(&blockRect);
                    break;
            }
        }
    }
    anim++;
    if(anim >= 7*5) anim = 0;
}

void World::level_load(const char *path) {
    std::cout << path << std::endl;
    inFile.open(path);
    if(!inFile) {
        std::cout << "Unable to load level";
        exit(1);
    }
    Block block;
    std::vector<Block> row;
    int blockId;
    std::string line;
    while(getline(inFile, line)) {
        std::istringstream ss(line);
        while(ss >> blockId) {
            if(blockId == 0) row.push_back(AIR);
            if(blockId == 1) row.push_back(WALL);
            if(blockId == 2) row.push_back(DIRT);
            if(blockId == 3) row.push_back(ROCK);
            if(blockId == 4) row.push_back(LAVA);
            if(blockId == 5) row.push_back(START);
            if(blockId == 6) row.push_back(FINISH);
            if(blockId == 7) row.push_back(DIAMOND);
        }
        map.push_back(row);
        row.clear();
    }
    inFile.close();
}

void World::level_unload() {
    map.clear();
}

void World::load_block_textures() {
    spritesheet = Spritesheet(renderer, "resources/sprites.png", 8, 10);
}

SDL_Rect World::player_get_position() {
    int sizeY = map.size();
    int sizeX = map.at(0).size();
    for(int mapY = 0; mapY < sizeY; mapY++) {
        for(int mapX = 0; mapX < sizeX; mapX++) {
            if(map.at(mapY).at(mapX) == START) {
                std::cout << mapX << " " << mapY << std::endl;
                //map.at(mapY).at(mapX) = AIR;
                return { mapX, mapY, 0, 0 };
            }
        }
    }
}

void World::player_render(int x, int y, Direction direction) {
    SDL_Rect blockRect = { x*BLOCKSIZE + renderX, y*BLOCKSIZE + renderY, BLOCKSIZE, BLOCKSIZE };
    if(direction != NO) panim++;
    if(panim == 0) {
        spritesheet.select_sprite(0, 0);
        spritesheet.draw_selected_sprite(&blockRect);
    } else {
        if(direction == RIGHT) {
            spritesheet.select_sprite(0, 2);
            blockRect.x = blockRect.x + panim;
            spritesheet.draw_selected_sprite(&blockRect);
        } 
        if(direction == LEFT) {
            spritesheet.select_sprite(0, 1);
            blockRect.x = blockRect.x - panim;
            spritesheet.draw_selected_sprite(&blockRect);
        }
        if(direction == UP) {
            spritesheet.select_sprite(2, 0);
            blockRect.y = blockRect.y - panim;
            spritesheet.draw_selected_sprite(&blockRect);
        } 
        if(direction == DOWN) {
            spritesheet.select_sprite(3, 0);
            blockRect.y = blockRect.y + panim;
            spritesheet.draw_selected_sprite(&blockRect);
        }
        panim++;
        if(panim >= 7) panim = 0;
    }
}
//TODO: Return player status, like death, score etc
BlockStatus World::player_check_next_block(int x, int y, Direction direction) {
    if(direction == UP) return check_block(x, y-1);
    if(direction == LEFT) return check_block(x-1, y);
    if(direction == RIGHT) return check_block(x+1, y);
    if(direction == DOWN) return check_block(x, y+1);
};

BlockStatus World::check_block(int x, int y) {
    if(map.at(y).at(x) == AIR) return NONE; //Can move
    if(map.at(y).at(x) == WALL) return BLOCK; //Can't move through wall
    if(map.at(y).at(x) == DIRT) { //Can move, digs dirt
        map.at(y).at(x) = AIR;
        return NONE;
    }
    if(map.at(y).at(x) == ROCK) return BLOCK;
    if(map.at(y).at(x) == LAVA) return DEATH; //Can move into lava, but dies (TODO)
    if(map.at(y).at(x) == START) return NONE; //Start is same as air
    if(map.at(y).at(x) == FINISH) return WIN; //Same as start, also wins the level
    if(map.at(y).at(x) == DIAMOND) { //Can move, picks the diamond (TODO: GETS POINTS)
        map.at(y).at(x) = AIR;
        return SCORE;
    }
}

void World::move_camera_to_player(int playerX, int playerY) {
    if(0 - playerY * BLOCKSIZE + 720/2 > 0) {
        renderY = 0;
    } else 
    if(0 - playerY * BLOCKSIZE + 720/2 < 0 - map.size() * BLOCKSIZE + 720) {
       renderY = 0 - map.size() * BLOCKSIZE + 720; 
    } else {
        renderY = 0 - playerY * BLOCKSIZE + 720/2;
    }
    if(0 - playerX * BLOCKSIZE + 1280/2 > 0) {
        renderX = 0;
    } else
    if(0 - playerX * BLOCKSIZE + 1280/2 < 0 - map.at(0).size() * BLOCKSIZE + 1280) {
        renderX = 0 - map.at(0).size() * BLOCKSIZE + 1280;
    } else {
        renderX = 0 - playerX * BLOCKSIZE + 1240/2;
    }
}

void World::objects_move(int playerX, int playerY) {
    int sizeY = map.size();
    int sizeX = map.at(0).size();
    for(int mapY = 0; mapY < sizeY; mapY++) {
        for(int mapX = 0; mapX < sizeX; mapX++) {
            if(map.at(mapY).at(mapX) == ROCK || map.at(mapY).at(mapX) == DIAMOND) {
                if(map.at(mapY+1).at(mapX) == AIR && !(mapX == playerX && mapY+1 == playerY)) { 
                    map.at(mapY+1).at(mapX) = map.at(mapY).at(mapX);
                    map.at(mapY).at(mapX) = AIR;
                    break;
                } else
                if(
                    map.at(mapY).at(mapX-1) == AIR && 
                    map.at(mapY+1).at(mapX-1) == AIR &&
                    (map.at(mapY+1).at(mapX) == ROCK || map.at(mapY).at(mapX) == DIAMOND) &&
                    (!(mapX-1 == playerX && mapY == playerY) && !(mapX-1 == playerX && mapY+1 == playerY))
                ) {
                    map.at(mapY).at(mapX-1) = map.at(mapY).at(mapX);
                    map.at(mapY).at(mapX) = AIR;
                    break;
                } else
                if(
                    map.at(mapY).at(mapX+1) == AIR &&
                    map.at(mapY+1).at(mapX+1) == AIR &&
                    (map.at(mapY+1).at(mapX) == ROCK || map.at(mapY).at(mapX) == DIAMOND) &&
                    (!(mapX+1 == playerX && mapY == playerY) && !(mapX+1 == playerX && mapY+1 == playerY))
                ) {
                    map.at(mapY).at(mapX+1) = map.at(mapY).at(mapX);
                    map.at(mapY).at(mapX) = AIR;
                    break;
                }
            }
        }
    }
}