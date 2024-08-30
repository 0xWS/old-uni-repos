#include <SDL.h>
#include <SDL_image.h>

class Spritesheet {
    private:
        SDL_Rect spriteClip;
        SDL_Surface * spritesheetSurface;
        SDL_Texture * spritesheetTexture;
        SDL_Renderer* spritesheetRenderer;

    public:
        Spritesheet();
        Spritesheet(SDL_Renderer * r, const char *path, int row, int column);
        ~Spritesheet();

        void select_sprite(int x, int y);
        void draw_selected_sprite(SDL_Rect* position);
        void recolor();
};