#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#include "game.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main( int argc, char* args[] ) {

    const SDL_Rect debugRect = {0, SCREEN_HEIGHT-30, 350, 30};

    bool quit = false;
    int mouseX, mouseY;
    float elapsedMS;

    SDL_Window* gWindow = SDL_CreateWindow( "Boulder Dash (?)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	SDL_Event e;

    SDL_Renderer* renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    SDL_Init( SDL_INIT_VIDEO );

    Game game(renderer);

    game.init();
    TTF_Init();

    SDL_Surface* textSurface;
    SDL_Texture* textTexture;

    while(!quit) {
        Uint64 start = SDL_GetPerformanceCounter();
        SDL_RenderClear(renderer);
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                quit = true;
            }
            if(e.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&mouseX, &mouseY);
            }
        }
        
        game.update();
        game.render();
        SDL_RenderPresent(renderer);


        //Debug
        //TODO: Move to another class
        
        TTF_Font* font = TTF_OpenFont("resources/fonts/Consolas.ttf", 12);
        //https://thenumbat.github.io/cpp-course/sdl2/08/08.html
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        std::string dev = "Yet Another Boulder Dash Clone INDEV\nCurrent FPS: " + std::to_string(1000.0f / (16.666f - elapsedMS));
        textSurface = TTF_RenderText_Blended_Wrapped(font, dev.c_str(), {255, 0, 0, 0}, 350);
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_RenderCopy(renderer, textTexture, NULL, &debugRect);
	    //std::cout << "Current FPS: " << std::to_string(1000.0f / (16.666f - elapsedMS)) << std::endl;
        SDL_RenderPresent(renderer);
        float delay = floor(16.666f - elapsedMS);
        if(delay > 0.0f) SDL_Delay(delay);
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(gWindow);

	SDL_Quit();

	return 0;
}