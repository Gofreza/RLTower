#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <iostream>

#include "Menu.h"
#include "../Spell/Spell.h"
#include "../Manager/Localization/LocalizationManager.h"
#include "../Manager/Spell/SpellManager.h"

class SpellMenu : Menu
{
public:
    SpellMenu(SDL_Renderer* renderer, TTF_Font* font);
    void render(const SDL_Rect& rect) override;
    void render(const SDL_Rect& rect, Spell* spell);

    int getHeight() const override;
    ~SpellMenu();

private:
    SDL_Rect imgRect;
    SDL_Rect dataRect;

    void renderWithColor(int& currentY, SDL_Color color, std::string label, std::string value);
    void renderWithoutColor(int& currentY, std::string label, std::string value);
    void renderLongText(int& currentY, std::string label, std::string value);
};