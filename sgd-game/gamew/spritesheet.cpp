#include "spritesheet.hpp"

#include <stdio.h>

Spritesheet::Spritesheet() {}

Spritesheet::Spritesheet(SDL_Renderer * r, const char *path, int row, int column) {
    spritesheetRenderer = r;
    spritesheetSurface = IMG_Load(path);
    if (spritesheetSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    spritesheetTexture = SDL_CreateTextureFromSurface(spritesheetRenderer, spritesheetSurface);
    recolor();
    SDL_FreeSurface(spritesheetSurface);

    spriteClip.w = spritesheetSurface->w / column;
    spriteClip.h = spritesheetSurface->h / row;
}

Spritesheet::~Spritesheet() {
   // SDL_FreeSurface(spritesheetSurface);
}

void Spritesheet::select_sprite(int x, int y) {
    spriteClip.x = x * spriteClip.w;
    spriteClip.y = y * spriteClip.h;
}

void Spritesheet::draw_selected_sprite(SDL_Rect* position) {
    SDL_RenderCopy(spritesheetRenderer, spritesheetTexture, &spriteClip, position);
}

void Spritesheet::recolor() {
    //SDL_SetTextureColorMod(spritesheetTexture, 146, 59, 77);
    //SDL_SetTextureColorMod(spritesheetTexture, 173, 160, 213);
    //TODO: Orginal had changing texture color pallete. Maybe one day..
} 