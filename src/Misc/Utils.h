#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cmath>

namespace Utils {
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
    bool initSDL_TTF(TTF_Font*& font, const std::string& fontPath, int fontSize);
    SDL_Texture* loadTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color);

    std::string getCWD();
    std::string getImagePath(const std::string& imageName);

    bool isMouseHovering(const SDL_Rect& rect, int renderTargetX, int renderTargetY);

    float distance(int x1, int y1, int x2, int y2);

    // Define colors
    extern SDL_Color borderColor;
    extern SDL_Color textColor;
    extern SDL_Color hoverColor;
    extern SDL_Color hoverBackColor;
    extern SDL_Color hpBarBorderColor;
    extern SDL_Color hpFillColor;
    extern SDL_Color manaBarBorderColor;
    extern SDL_Color manaFillColor;
    extern SDL_Color energyBarBorderColor;
    extern SDL_Color energyFillColor;
    extern SDL_Color staminaBarBorderColor;
    extern SDL_Color staminaFillColor;

    extern SDL_Color phyCombatColor;
    extern SDL_Color magCombatColor;
};
