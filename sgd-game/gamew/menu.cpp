#include "menu.hpp"

Menu::Menu() {}

Menu::~Menu() {}

Menu::Menu(std::vector<Button> buttons) {
    this->buttons = buttons;
}

void Menu::display_buttons() {
    
}

GameState Menu::click_button(int mouseX, int mouseY) {
    for (auto button : this->buttons) {
        if(mouseX > button.rect.x && mouseX < button.rect.x + button.rect.w && mouseY > button.rect.y && mouseY < button.rect.y + button.rect.y) {
            return button.targetGameState;
        }
    }
}