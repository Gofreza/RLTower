#include "StatusMenu.h"
#include "../Misc/Utils.h"
#include "../Manager/Characters/CharactersManager.h"
#include "../Manager/Localization/LocalizationManager.h"
#include "../Manager/UI/UiManager.h"

StatusMenu::StatusMenu(SDL_Renderer* renderer, TTF_Font* font)
: Menu(renderer, font), 
lastHpTextWidth(0), lastManaTextWidth(0), lastStaminaTextWidth(0),
player(CharactersManager::instance().getPlayer())
{
    int hp = player->getHp();
    int mana = player->getMana();
    int energy = player->getEnergy();
    int stamina = player->getStamina();

    int gold = player->getGold();
    int silver = player->getSilver();
    int copper = player->getCopper();

    // Margin top and bottom
    // + 11 for header of equipment menu
    menuHeight = 30 + 11;

    // Pre-render
    std::string hpText = LocalizationManager::instance().getText("hp_title") + std::to_string(hp);
    hpTextTexture = Utils::loadTextTexture(renderer, font, hpText, Utils::textColor);
    menuHeight += 30;

    if (hasMana) {
        std::string manaText = LocalizationManager::instance().getText("mana_title") + std::to_string(mana);
        manaTextTexture = Utils::loadTextTexture(renderer, font, manaText, Utils::textColor);
    } else {
        std::string energyText = LocalizationManager::instance().getText("energy_title") + std::to_string(energy);
        manaTextTexture = Utils::loadTextTexture(renderer, font, energyText, Utils::textColor);
    }
    menuHeight += 30;

    std::string staminaText = LocalizationManager::instance().getText("stamina_title") + std::to_string(stamina);
    staminaTextTexture = Utils::loadTextTexture(renderer, font, staminaText, Utils::textColor);
    menuHeight += 30;

    std::string goldText = LocalizationManager::instance().getText("gold_title") + std::to_string(gold);
    goldTextTexture = Utils::loadTextTexture(renderer, font, goldText, Utils::textColor);
    int textWidth = 0, textHeight = 0;
    SDL_QueryTexture(goldTextTexture, nullptr, nullptr, &textWidth, &textHeight);
    menuHeight += textHeight;

    std::string silverText = LocalizationManager::instance().getText("silver_title") + std::to_string(silver);
    silverTextTexture = Utils::loadTextTexture(renderer, font, silverText, Utils::textColor);
    //SDL_QueryTexture(silverTextTexture, nullptr, nullptr, &textWidth, &textHeight);
    menuHeight += textHeight;

    std::string copperText = LocalizationManager::instance().getText("copper_title") + std::to_string(copper);
    copperTextTexture = Utils::loadTextTexture(renderer, font, copperText, Utils::textColor);
    //SDL_QueryTexture(copperTextTexture, nullptr, nullptr, &textWidth, &textHeight);
    //menuHeight += textHeight;
}

void StatusMenu::render(const SDL_Rect& rect) {

    //=====================================================================
    // We do not use rect.x to get where we should draw
    // Because we render into a render target and not directly on the window
    // it's like a new window so top left is (0, 0)
    // So rect.x = 0
    // We still use the width and height though
    //=====================================================================

    float hp = player->getHp();
    int mana = player->getMana();
    int energy = player->getEnergy();
    int stamina = player->getStamina();
    float maxhp = player->getMaxHp();
    int maxMana = player->getMaxMana();
    int maxEnergy = player->getMaxEnergy();
    int maxStamina = player->getMaxStamina();

    int gold = player->getGold();
    int silver = player->getSilver();
    int copper = player->getCopper();

    // Check if player has mana or energy
    hasMana = !player->isCharacterAuraUser();

    int currentY = rect.y + 10;

    // Draw the border
    // UiManager::instance().drawBorder(renderer, menuRect, borderColor);

    // Render HP bar
    SDL_Rect hpBarRect = { 0, currentY, rect.w , 30 };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &hpBarRect);

    SDL_SetRenderDrawColor(renderer, Utils::hpFillColor.r, Utils::hpFillColor.g, Utils::hpFillColor.b, Utils::hpFillColor.a);
    SDL_Rect hpFillRect = { hpBarRect.x, hpBarRect.y, static_cast<int>(hpBarRect.w * (hp / maxhp)), hpBarRect.h };
    SDL_RenderFillRect(renderer, &hpFillRect);
    
    // Render HP text inside the bar
    std::stringstream stream;
    stream << std::fixed << std::setprecision(0) << hp;
    std::string hpStr = stream.str();

    std::string hpText = LocalizationManager::instance().getText("hp_title") + hpStr;
    SDL_DestroyTexture(hpTextTexture);
    hpTextTexture = Utils::loadTextTexture(renderer, font, hpText, Utils::textColor);
    if (hpTextTexture) {
        int textWidth = 0, textHeight = 0;
        SDL_QueryTexture(hpTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        if (lastHpTextWidth < textWidth) {
            lastHpTextWidth = textWidth;
        }

        SDL_Rect textRect = {
            hpBarRect.x + (hpBarRect.w - lastHpTextWidth) / 2, 
            hpBarRect.y + (hpBarRect.h - textHeight) / 2, 
            lastHpTextWidth,
            textHeight
        };
        currentY += 30;
        SDL_RenderCopy(renderer, hpTextTexture, nullptr, &textRect);
    }

    // Render Mana bar or Energy bar
    SDL_Rect manaBarRect = { 0, currentY, rect.w, 30 };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &manaBarRect);
    if (hasMana) {
        SDL_SetRenderDrawColor(renderer, Utils::manaFillColor.r, Utils::manaFillColor.g, Utils::manaFillColor.b, Utils::manaFillColor.a);
        float fMana = mana, fMaxMana = maxMana;
        SDL_Rect manaFillRect = { manaBarRect.x, manaBarRect.y, static_cast<int>(manaBarRect.w * (fMana / fMaxMana)), manaBarRect.h };
        SDL_RenderFillRect(renderer, &manaFillRect);
        
        std::string manaText = LocalizationManager::instance().getText("mana_title") + std::to_string(mana);
        SDL_DestroyTexture(manaTextTexture);
        manaTextTexture = Utils::loadTextTexture(renderer, font, manaText, Utils::textColor);
    } else {
        SDL_SetRenderDrawColor(renderer, Utils::energyFillColor.r, Utils::energyFillColor.g, Utils::energyFillColor.b, Utils::energyFillColor.a);
        float fEnergy = energy, fMaxEnergy = maxEnergy;
        SDL_Rect manaFillRect = { manaBarRect.x, manaBarRect.y, static_cast<int>(manaBarRect.w * (fEnergy / fMaxEnergy)), manaBarRect.h };
        SDL_RenderFillRect(renderer, &manaFillRect);

        std::string energyText = LocalizationManager::instance().getText("energy_title") + std::to_string(energy);
        SDL_DestroyTexture(manaTextTexture);
        manaTextTexture = Utils::loadTextTexture(renderer, font, energyText, Utils::textColor);
    }

    // Render Mana text inside the bar
    if (manaTextTexture) {
        int textWidth = 0, textHeight = 0;
        SDL_QueryTexture(manaTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        if (lastManaTextWidth < textWidth) {
            lastManaTextWidth = textWidth;
        }

        SDL_Rect textRect = {
            manaBarRect.x + (manaBarRect.w - lastManaTextWidth) / 2, 
            manaBarRect.y + (manaBarRect.h - textHeight) / 2, 
            lastManaTextWidth,
            textHeight
        };
        currentY += 30;
        SDL_RenderCopy(renderer, manaTextTexture, nullptr, &textRect);
    }

    // Render stamina bar
    SDL_Rect staminaBarRect = { 0, currentY, rect.w , 30 };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &staminaBarRect);

    SDL_SetRenderDrawColor(renderer, Utils::staminaFillColor.r, Utils::staminaFillColor.g, Utils::staminaFillColor.b, Utils::staminaFillColor.a);
    float fStamina = stamina, fMaxStamina = maxStamina;
    SDL_Rect staminaFillRect = { staminaBarRect.x, staminaBarRect.y, static_cast<int>(staminaBarRect.w * (fStamina / fMaxStamina)), staminaBarRect.h };
    SDL_RenderFillRect(renderer, &staminaFillRect);
    
    // Render Stamina text inside the bar
    std::string staminaText = LocalizationManager::instance().getText("stamina_title") + std::to_string(stamina);
    SDL_DestroyTexture(staminaTextTexture);
    staminaTextTexture = Utils::loadTextTexture(renderer, font, staminaText, Utils::textColor);
    if (staminaTextTexture) {
        int textWidth = 0, textHeight = 0;
        SDL_QueryTexture(staminaTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        if (lastStaminaTextWidth < textWidth) {
            lastStaminaTextWidth = textWidth;
        }

        SDL_Rect textRect = {
            staminaBarRect.x + (staminaBarRect.w - lastStaminaTextWidth) / 2, 
            staminaBarRect.y + (staminaBarRect.h - textHeight) / 2, 
            lastStaminaTextWidth,
            textHeight
        };
        currentY += 30;
        SDL_RenderCopy(renderer, staminaTextTexture, nullptr, &textRect);
    }

    int sectionWidth = rect.w / 3;

    // Render Gold
    std::string goldText = LocalizationManager::instance().getText("gold_title") + std::to_string(gold);
    SDL_DestroyTexture(goldTextTexture);
    goldTextTexture = Utils::loadTextTexture(renderer, font, goldText, Utils::textColor);
    if (goldTextTexture) {
        int textWidth = 0, textHeight = 0;
        SDL_QueryTexture(goldTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect textRect = {
            0 + (sectionWidth - textWidth) / 2, 
            currentY + textHeight, 
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer, goldTextTexture, nullptr, &textRect);
    }

    // Render Silver
    std::string silverText = LocalizationManager::instance().getText("silver_title") + std::to_string(silver);
    SDL_DestroyTexture(silverTextTexture);
    silverTextTexture = Utils::loadTextTexture(renderer, font, silverText, Utils::textColor);
    if (silverTextTexture) {
        int textWidth = 0, textHeight = 0;
        SDL_QueryTexture(silverTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect textRect = {
            0 + sectionWidth + (sectionWidth - textWidth) / 2, 
            currentY + textHeight, 
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer, silverTextTexture, nullptr, &textRect);
    }

    // Render Copper
    std::string copperText = LocalizationManager::instance().getText("copper_title") + std::to_string(copper);
    SDL_DestroyTexture(copperTextTexture);
    copperTextTexture = Utils::loadTextTexture(renderer, font, copperText, Utils::textColor);
    if (copperTextTexture) {
        int textWidth = 0, textHeight = 0;
        SDL_QueryTexture(copperTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect textRect = {
            0 + 2 * sectionWidth + (sectionWidth - textWidth) / 2, 
            currentY + textHeight, 
            textWidth,
            textHeight
        };
        // Take textRect rectangle of copperTextTexture and put it inside
        // the current redering target
        SDL_RenderCopy(renderer, copperTextTexture, nullptr, &textRect);
    }

    SDL_Rect hoverRect = {
        0, 
        0,
        rect.w,
        rect.h
    };
    
    // Listeners
    if (isMouseHovering(hoverRect, rect.x)) {
        UiManager::instance().triggerRenderCharacterMenu();
    }
    
}

int StatusMenu::getHeight() const {
    return menuHeight; 
}

//=================
// UPDATES
//=================

void StatusMenu::updateHp() {
    int hp = player->getHp();
    std::string hpText = "HP: " + std::to_string(hp);

    if (hpTextTexture != nullptr) {
        SDL_DestroyTexture(hpTextTexture);
        hpTextTexture = nullptr;
    }

    hpTextTexture = Utils::loadTextTexture(renderer, font, hpText, Utils::textColor);
}

// Update Mana/Energy
void StatusMenu::updateMana() {
    if (manaTextTexture != nullptr) {
        SDL_DestroyTexture(manaTextTexture);
        manaTextTexture = nullptr;
    }

    if (hasMana) {
        int mana = player->getMana();
        std::string manaText = "Mana: " + std::to_string(mana);
        manaTextTexture = Utils::loadTextTexture(renderer, font, manaText, Utils::textColor);
    } else {
        int energy = player->getEnergy();
        std::string energyText = "Energy: " + std::to_string(energy);
        manaTextTexture = Utils::loadTextTexture(renderer, font, energyText, Utils::textColor);
    }
}

void StatusMenu::updateGold() {
    if (goldTextTexture != nullptr) {
        SDL_DestroyTexture(goldTextTexture);
        goldTextTexture = nullptr;
    }

    int gold = player->getGold();
    std::string goldText = "Gold: " + std::to_string(gold);
    goldTextTexture = Utils::loadTextTexture(renderer, font, goldText, Utils::textColor);
}

void StatusMenu::updateSilver() {
    if (silverTextTexture != nullptr) {
        SDL_DestroyTexture(silverTextTexture);
        silverTextTexture = nullptr;
    }
    
    int silver = player->getSilver();
    std::string silverText = "Silver: " + std::to_string(silver);
    silverTextTexture = Utils::loadTextTexture(renderer, font, silverText, Utils::textColor);
}

void StatusMenu::updateCopper() {
    if (copperTextTexture != nullptr) {
        SDL_DestroyTexture(copperTextTexture);
        copperTextTexture = nullptr;
    }
    
    int copper = player->getCopper();
    std::string copperText = "Copper: " + std::to_string(copper);
    copperTextTexture = Utils::loadTextTexture(renderer, font, copperText, Utils::textColor);
}


StatusMenu::~StatusMenu() {
    SDL_DestroyTexture(hpTextTexture);
    SDL_DestroyTexture(manaTextTexture);
    SDL_DestroyTexture(goldTextTexture);
    SDL_DestroyTexture(silverTextTexture);
    SDL_DestroyTexture(copperTextTexture);
}