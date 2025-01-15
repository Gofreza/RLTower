#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Menu.h"
#include "../Character/Player.h"

class StatusMenu : Menu
{
public:
    StatusMenu(SDL_Renderer* renderer, TTF_Font* font);
    void render(const SDL_Rect& menuRect) override;

    int getHeight() const override;
    ~StatusMenu();

    void updateHp();
    void updateMana();
    void updateGold();
    void updateSilver();
    void updateCopper();

private:
    int lastHpTextWidth;
    int lastManaTextWidth;
    int lastStaminaTextWidth;

    SDL_Texture* hpTextTexture;
    SDL_Texture* manaTextTexture;
    SDL_Texture* staminaTextTexture;
    SDL_Texture* goldTextTexture;
    SDL_Texture* silverTextTexture;
    SDL_Texture* copperTextTexture;

    Player* player;
    bool hasMana;
};