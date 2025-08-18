#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../Menu.h"

class Enemy;

class DebugMenu : public Menu
{
public:
    DebugMenu(SDL_Renderer* renderer, TTF_Font* font);
    void render(const SDL_Rect& rect) override;

    int getHeight() const override;
    ~DebugMenu();
private:
    Enemy* selectedCharacter;
    bool isFovEnabled;

    void renderWithoutColor(const SDL_Rect& rect, int& currentY, std::string label, std::string value);

};

