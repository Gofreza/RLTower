#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Menu.h"

class ConsoleMenu : Menu
{
public:
    ConsoleMenu (SDL_Renderer* renderer, TTF_Font* font);
    void render(const SDL_Rect& menuRect) override;

    int getHeight() const override;
    ~ConsoleMenu ();

private:
    SDL_Texture* headerTextTexture;

};
