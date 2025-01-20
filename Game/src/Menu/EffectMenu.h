#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Menu.h"
#include "../Manager/Characters/CharactersManager.h"

class EffectMenu : Menu
{
public:
    EffectMenu(SDL_Renderer* renderer, TTF_Font* font);
    void render(const SDL_Rect& rect) override;

    int getHeight() const override;
    ~EffectMenu();
private:
     
};
