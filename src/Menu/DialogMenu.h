#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Menu.h"
#include "../Character/Character.h"

class DialogMenu : Menu
{
public:
    DialogMenu (SDL_Renderer* renderer, TTF_Font* font);
    void render(const SDL_Rect& menuRect) override;
    void render(const SDL_Rect& menuRect, const Item* item);
    void render(const SDL_Rect& menuRect, const Character* character);

    int getHeight() const override;
    ~DialogMenu ();

private:
    SDL_Texture* headerTextTexture;
    int currentY;

};
