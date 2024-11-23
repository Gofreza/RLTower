#include "CharacterMenu.h"

CharacterMenu::CharacterMenu(SDL_Renderer* renderer, TTF_Font* font) 
: Menu(renderer, font), player(CharactersManager::instance().getPlayer())
{

}

//===============
// Render Global
//===============

void CharacterMenu::renderWithColor(int& currentY, SDL_Color color, std::string label, std::string value) {
    SDL_Texture* labelTexture = Utils::loadTextTexture(renderer, font, label, Utils::textColor);
    if (labelTexture) {
        int labelWidth = 0, labelHeight = 0;
        SDL_QueryTexture(labelTexture, nullptr, nullptr, &labelWidth, &labelHeight);
        SDL_Rect labelRect = {
            dataRect.x + 5, 
            currentY, 
            labelWidth,
            labelHeight
        };
        SDL_RenderCopy(renderer, labelTexture, nullptr, &labelRect);
        SDL_DestroyTexture(labelTexture);

        // Render rarity value
        SDL_Color valueColor = color;
        SDL_Texture* rarityValueTexture = Utils::loadTextTexture(renderer, font, value, valueColor);

        if (rarityValueTexture) {
            int valueWidth = 0, valueHeight = 0;
            SDL_QueryTexture(rarityValueTexture, nullptr, nullptr, &valueWidth, &valueHeight);
            SDL_Rect valueRect = {
                dataRect.x + labelWidth + 5, 
                currentY, 
                valueWidth,
                valueHeight
            };
            SDL_RenderCopy(renderer, rarityValueTexture, nullptr, &valueRect);
            SDL_DestroyTexture(rarityValueTexture);
        }

        currentY += labelHeight + 5;
    }
}

void CharacterMenu::renderWithoutColor(int& currentY, std::string label, std::string value) {
    int textWidth = 0, textHeight = 0;
    std::string text = label + value;
    SDL_Texture* textTexture = Utils::loadTextTexture(renderer, font, text, Utils::textColor);
    if (textTexture) {
        SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect durabilityRect = {
            dataRect.x + 5, 
            currentY, 
            textWidth,
            textHeight
        };
        currentY += textHeight + 5;
        SDL_RenderCopy(renderer, textTexture, nullptr, &durabilityRect);
    }
    SDL_DestroyTexture(textTexture);
}

void CharacterMenu::renderWith2Color(int& currentY, SDL_Color labelColor, SDL_Color valueColor, std::string label, std::string value) {
    SDL_Texture* labelTexture = Utils::loadTextTexture(renderer, font, label, labelColor);
    if (labelTexture) {
        int labelWidth = 0, labelHeight = 0;
        SDL_QueryTexture(labelTexture, nullptr, nullptr, &labelWidth, &labelHeight);
        SDL_Rect labelRect = {
            dataRect.x + 5, 
            currentY, 
            labelWidth,
            labelHeight
        };
        SDL_RenderCopy(renderer, labelTexture, nullptr, &labelRect);
        SDL_DestroyTexture(labelTexture);

        // Render rarity value
        SDL_Texture* rarityValueTexture = Utils::loadTextTexture(renderer, font, value, valueColor);

        if (rarityValueTexture) {
            int valueWidth = 0, valueHeight = 0;
            SDL_QueryTexture(rarityValueTexture, nullptr, nullptr, &valueWidth, &valueHeight);
            SDL_Rect valueRect = {
                dataRect.x + labelWidth + 5, 
                currentY, 
                valueWidth,
                valueHeight
            };
            SDL_RenderCopy(renderer, rarityValueTexture, nullptr, &valueRect);
            SDL_DestroyTexture(rarityValueTexture);
        }

        currentY += labelHeight + 5;
    }
}

//========
// Render 
//========

void CharacterMenu::render(const SDL_Rect& rect) {
    // Define rect
    dataRect = {
        rect.x + 5,
        rect.y + 5,
        rect.w - 5 - 5,
        rect.h - 5
    };

    int currentY = dataRect.y;

    // Level
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_level"), std::to_string(player->getLevel()));

    // Experience
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_experience"), std::to_string(player->getExperience()) + "/" + std::to_string(player->getLevelRequirement()));

    // Fatigue
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_fatigue"), std::to_string(player->getFatigue()));

    // Phy. Damage
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_phydamage"), std::to_string(player->getPhyDamage()));

    // Mag. Damage
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_magdamage"), std::to_string(player->getMagDamage()));

    // Strength
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_strength"), std::to_string(player->getStrength()));

    // Dexterity
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_dexterity"), std::to_string(player->getDexterity()));

    // Intelligence
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_intelligence"), std::to_string(player->getIntelligence()));

    // Wisdom
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_wisdom"), std::to_string(player->getWisdom()));

    // Constitution 
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_constitution"), std::to_string(player->getConstitution()));

    // Luck
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_luck"), std::to_string(player->getLuck()));

    // Phy. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_phydefense"), std::to_string(player->getPhysicalDefense()));

    // Mag. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_magdefense"), std::to_string(player->getMagicalDefense()));

    // Speed
    renderWithoutColor(currentY, LocalizationManager::instance().getText("character_speed"), std::to_string(player->getSpeed()));

    //===========
    // Separator
    //===========

    SDL_Rect separatorRect2 = {
        dataRect.x + 5,
        currentY,
        dataRect.w - 5 - 5,
        2
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &separatorRect2);

    currentY += 2 + 5;

    //=============
    // Resistances
    //=============

    renderWith2Color(currentY, getElementColor("Fire"), Utils::textColor, LocalizationManager::instance().getText("fire_resistance"), std::to_string(player->getFireResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Water"), Utils::textColor, LocalizationManager::instance().getText("water_resistance"), std::to_string(player->getWaterResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Earth"), Utils::textColor, LocalizationManager::instance().getText("earth_resistance"), std::to_string(player->getEarthResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Lightning"), Utils::textColor, LocalizationManager::instance().getText("lightning_resistance"), std::to_string(player->getLightningResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Ice"), Utils::textColor, LocalizationManager::instance().getText("ice_resistance"), std::to_string(player->getIceResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Nature"), Utils::textColor, LocalizationManager::instance().getText("nature_resistance"), std::to_string(player->getNatureResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Light"), Utils::textColor, LocalizationManager::instance().getText("light_resistance"), std::to_string(player->getLightResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Darkness"), Utils::textColor, LocalizationManager::instance().getText("darkness_resistance"), std::to_string(player->getDarknessResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Arcane"), Utils::textColor, LocalizationManager::instance().getText("arcane_resistance"), std::to_string(player->getArcaneResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Poison"), Utils::textColor, LocalizationManager::instance().getText("poison_resistance"), std::to_string(player->getPoisonResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Metal"), Utils::textColor, LocalizationManager::instance().getText("metal_resistance"), std::to_string(player->getMetalResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Sound"), Utils::textColor, LocalizationManager::instance().getText("sound_resistance"), std::to_string(player->getSoundResistance()) + "%");
    renderWith2Color(currentY, getElementColor("Illusion"), Utils::textColor, LocalizationManager::instance().getText("illusion_resistance"), std::to_string(player->getIllusionResistance()) + "%");
} 

int CharacterMenu::getHeight() const {
    return -1;
}

CharacterMenu::~CharacterMenu() {

}