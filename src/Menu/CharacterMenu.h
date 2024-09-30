#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Menu.h"
#include "../Manager/Characters/CharactersManager.h"
#include "../Manager/Localization/LocalizationManager.h"

class CharacterMenu : public Menu
{
public:
    CharacterMenu(SDL_Renderer* renderer, TTF_Font* font);
    void render(const SDL_Rect& rect) override;

    int getHeight() const override;
    ~CharacterMenu();
private:
    Player* player;
    SDL_Rect dataRect;

    void renderWithColor(int& currentY, SDL_Color color, std::string label, std::string value);
    void renderWithoutColor(int& currentY, std::string label, std::string value);
    void renderWith2Color(int& currentY, SDL_Color color, SDL_Color color2, std::string label, std::string value);
};

