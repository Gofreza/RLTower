#include "EffectMenu.h"

EffectMenu::EffectMenu(SDL_Renderer* renderer, TTF_Font* font) 
: Menu(renderer, font)
{
}

void EffectMenu::render(const SDL_Rect& rect) {
    int textWidth = 0, textHeight = 0;
    Player* player = CharactersManager::instance().getPlayer();
    std::vector<Effect*> effects = player->getEffects();

    int effectWidth = 48;
    int padding = 1;

    for (int i = 0; i < effects.size(); ++i) {
        Effect* effect = effects.at(i);

        SDL_Rect effectRect = {
            rect.w - ((i+1) * (effectWidth + padding)),
            1,
            effectWidth,
            effectWidth
        };

        // Image
        std::string imagePath = Utils::getImagePath("spell_skill_icons/red_shield.png");
        SDL_Surface* imgSurface = IMG_Load(imagePath.c_str());
        SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);
        SDL_FreeSurface(imgSurface);

        SDL_RenderCopy(renderer, imgTexture, nullptr, &effectRect);
        SDL_DestroyTexture(imgTexture);

        Menu::drawBorder(renderer, effectRect, Utils::borderColor);

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 1, 1, 1, 1);
        SDL_RenderFillRect(renderer, &effectRect);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }
    
}

int EffectMenu::getHeight() const {
    return 50;
}

EffectMenu::~EffectMenu() {
}