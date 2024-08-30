#include <SDL.h>
#include <vector>
#include <string>

enum GameState {
    MENU, GAME, LEVEL_EDIT
};

struct Button {
    SDL_Rect rect;
    std::string text;
    GameState targetGameState;

    Button(SDL_Rect rect, std::string text, GameState targetGameState) {
        this->rect = rect;
        this->text = text;
        this->targetGameState = targetGameState;
    }
};

class Menu {
    private:
        SDL_Rect rect;
        SDL_Renderer * spritesheetRenderer;
        std::vector<Button> buttons;
    public:
        Menu();
        ~Menu();
        Menu(std::vector<Button> buttons);
        void display_buttons();
        GameState click_button(int mouseX, int mouseY);
};