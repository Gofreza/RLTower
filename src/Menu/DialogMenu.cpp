#include "DialogMenu.h"
#include "../Misc/Utils.h"

#include "../Manager/Localization/LocalizationManager.h"

DialogMenu::DialogMenu (SDL_Renderer* renderer, TTF_Font* font)
: Menu(renderer, font)
{
    std::string headerText = LocalizationManager::instance().getText("dialog_title");
    headerTextTexture = Utils::loadTextTexture(renderer, font, headerText, Utils::textColor);
}

void DialogMenu::render(const SDL_Rect& rect) {

    int textWidth = 0, textHeight = 0;
    if (headerTextTexture) {
        SDL_QueryTexture(headerTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect headerRect = {
            rect.x + (rect.w - textWidth) / 2, 
            rect.y + 5, 
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer, headerTextTexture, nullptr, &headerRect);
    }

    SDL_Rect dialogRect = {
        rect.x,
        rect.y + textHeight + 5 + 5,
        rect.w,
        rect.h - textHeight - 5 - 5
    };
    
    drawBorder(renderer, dialogRect, Utils::borderColor);
}

int DialogMenu::getHeight() const {
    return -1;
} 

DialogMenu::~DialogMenu ()
{
    SDL_DestroyTexture(headerTextTexture);
}