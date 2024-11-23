#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <functional>

#include "Menu.h"
#include "../Manager/Characters/CharactersManager.h"
#include "../Manager/Controls/InputManager.h"
#include "../Object/Equipment/Weapon.h"
#include "../Object/Equipment/Shield.h"
#include "../Object/Equipment/Helmet.h"
#include "../Object/Equipment/Gloves.h"
#include "../Object/Equipment/Chests.h"
#include "../Object/Equipment/Leggings.h"
#include "../Object/Equipment/Ring.h"
#include "../Object/Equipment/Amulet.h"

class EquipmentMenu : Menu
{
public:
    EquipmentMenu(SDL_Renderer* renderer, TTF_Font* font);
    void render(const SDL_Rect& rect) override;

    int getHeight() const override;
    ~EquipmentMenu();

private:
    std::unordered_map<SDL_Texture*, std::function<Item*(Player*)>> textureToSlotMap;
    void initializeTextureToSlotMap();

    SDL_Texture* headerTextTexture;

    SDL_Texture* lhTextTexture;
    SDL_Texture* rhTextTexture;
    SDL_Texture* headTextTexture;
    SDL_Texture* torsoTextTexture;
    SDL_Texture* handTextTexture;
    SDL_Texture* footTextTexture;
    SDL_Texture* ringTextTexture;
    SDL_Texture* ring2TextTexture;
    SDL_Texture* amuletTextTexture;

    int maxTextTextureWidth;

    Player* player;

    void renderTextTexture(SDL_Texture* textTexture, int& currentY, int padding, int renderTargetX, int renderTargetY, int renderTargetW);
};