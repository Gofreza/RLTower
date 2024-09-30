#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../Misc/Utils.h"

class Menu
{
public:
    Menu(SDL_Renderer* renderer, TTF_Font* font) : renderer(renderer), font(font) {}
    virtual void render(const SDL_Rect& menuRect) = 0;
    virtual int getHeight() const = 0;
    virtual ~Menu() = default;

protected:
    SDL_Renderer* renderer;
    TTF_Font* font;
    int menuHeight;
    int padding;

    void drawBorder(SDL_Renderer* renderer, const SDL_Rect& rect, SDL_Color borderColor, int thickness = 2) const {
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        for (int i = 0; i < thickness; ++i) {
            SDL_Rect borderRect = { rect.x + i, rect.y + i, rect.w - 2 * i, rect.h - 2 * i };
            SDL_RenderDrawRect(renderer, &borderRect);
        }
    }

    bool isMouseHovering(const SDL_Rect& rect, int renderTargetX, int renderTargetY) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Adjust the mouse position relative to the render target
        int adjustedX = mouseX - renderTargetX;
        int adjustedY = mouseY;

        // Check if the adjusted mouse position is within the rect
        return (adjustedX >= rect.x && adjustedX < rect.x + rect.w &&
                adjustedY >= rect.y && adjustedY < rect.y + rect.h);
    }
};