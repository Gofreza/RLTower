#include "SpellMenu.h"

//===============
// Render Global
//===============

void SpellMenu::renderWithColor(int& currentY, SDL_Color color, std::string label, std::string value) {
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

void SpellMenu::renderWithoutColor(int& currentY, std::string label, std::string value) {
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

void SpellMenu::renderLongText(int& currentY, std::string label, std::string value) {
    int textWidth, textHeight;
    std::string descriptionText = label + value;
    std::vector<std::string> lines;
    std::string currentLine;
    std::istringstream words(descriptionText);
    std::string word;
    int maxWidth = dataRect.w - 10;  // Adjust for padding
    int spaceWidth;

    // Measure the width of a space character (you can assume spaceWidth as needed)
    TTF_SizeText(font, " ", &spaceWidth, nullptr);

    while (words >> word) {
        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
        TTF_SizeText(font, testLine.c_str(), &textWidth, &textHeight);

        if (textWidth > maxWidth) {
            // Current word does not fit on the current line, push the current line and start a new one
            lines.push_back(currentLine);
            currentLine = word;  // Start the new line with the current word
        } else {
            // Word fits on the current line
            currentLine = testLine;
        }
    }

    // Don't forget to add the last line
    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    // Now render each line
    for (const std::string& line : lines) {
        SDL_Texture* descriptionTextTexture = Utils::loadTextTexture(renderer, font, line, Utils::textColor);
        if (descriptionTextTexture) {
            SDL_QueryTexture(descriptionTextTexture, nullptr, nullptr, &textWidth, &textHeight);
            SDL_Rect descriptionRect = {
                dataRect.x + 5, 
                currentY, 
                textWidth,
                textHeight
            };
            SDL_RenderCopy(renderer, descriptionTextTexture, nullptr, &descriptionRect);
            SDL_DestroyTexture(descriptionTextTexture);

            // Move to the next line
            currentY += textHeight + 5;
        }
    }
}

//===============
// Class
//===============

SpellMenu::SpellMenu(SDL_Renderer* renderer, TTF_Font* font) 
: Menu(renderer, font)
{}

/**
 * Do not use, just here for consistency
 * Throw a runtime error
 */
void SpellMenu::render(const SDL_Rect& rect) {
    (void)rect;
    throw std::runtime_error("Error, need a spell to render. Use render(const SDL_Rect& rect, Spell* spell) instead.");
}

void SpellMenu::render(const SDL_Rect& rect, Spell* spell) {
    // Define rects
    imgRect = {
        rect.x + 10,
        rect.y + 5,
        rect.w - 10 - 10,
        300
    };

    dataRect = {
        rect.x + 5,
        rect.y + 5 + 300 + 10,
        rect.w - 5 - 5,
        rect.h - 300 - 5 - 5
    };

    // Load the image from file
    SDL_Surface* imgSurface = IMG_Load("../res/images/spell.png");
    if (!imgSurface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);
    SDL_FreeSurface(imgSurface); // Free the surface after creating the texture

    if (!imgTexture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }

    if (SDL_RenderCopy(renderer, imgTexture, nullptr, &imgRect) != 0) {
        std::cerr << "Failed to render texture: " << SDL_GetError() << std::endl;
    }

    SDL_DestroyTexture(imgTexture);

    //==================
    // Render spell data
    //==================
    int currentY = dataRect.y;

    // Name
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_name"), spell->getName());

    // Energy Type
    renderWithColor(currentY, getSpellEnergyTypeColor(spell->getSpellEnergyType()), LocalizationManager::instance().getText("spell_energytype"), to_string(spell->getSpellEnergyType()));

    // Type
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_type"), to_string(spell->getType()));

    // Element
    renderWithColor(currentY, getElementColor(spell->getElement()), LocalizationManager::instance().getText("spell_element"), to_string(spell->getElement()));

    // Damage
    renderWithoutColor(currentY, LocalizationManager::instance().getText("spell_damage"), std::to_string(spell->getDamage()));

    // Range
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_range"), std::to_string(spell->getRange()));

    // Radius
    renderWithoutColor(currentY, LocalizationManager::instance().getText("spell_radius"), std::to_string(spell->getRadius()));

    //===========
    // Separator
    //===========

    SDL_Rect separatorRect1 = {
        dataRect.x + 5,
        currentY,
        dataRect.w - 5 - 5,
        2
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &separatorRect1);

    currentY += 2 + 5;

    //=============
    // Description
    //=============

    renderLongText(currentY, LocalizationManager::instance().getText("item_description"), spell->getDescription());
    
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

    //==============
    // Requirements
    //==============

    std::array<int, 5> requirements = spell->getRequirements();

    if (requirements.at(0) != -1) {
        renderWithoutColor(currentY, LocalizationManager::instance().getText("item_requirements"), "");

        // Strength
        if (requirements.at(0) > 0)
            renderWithoutColor(currentY, LocalizationManager::instance().getText("character_strength"), std::to_string(requirements.at(0)));

        // Dexterity
        if (requirements.at(1) > 0)
            renderWithoutColor(currentY, LocalizationManager::instance().getText("character_dexterity"), std::to_string(requirements.at(1)));

        // Intelligence
        if (requirements.at(2))
            renderWithoutColor(currentY, LocalizationManager::instance().getText("character_intelligence"), std::to_string(requirements.at(2)));

        // Wisdom
        if (requirements.at(3))
            renderWithoutColor(currentY, LocalizationManager::instance().getText("character_wisdom"), std::to_string(requirements.at(3)));

        // Constitution
        if (requirements.at(4))
            renderWithoutColor(currentY, LocalizationManager::instance().getText("character_constitution"), std::to_string(requirements.at(4)));

        //===========
        // Separator
        //===========

        SDL_Rect separatorRect3 = {
            dataRect.x + 5,
            currentY,
            dataRect.w - 5 - 5,
            2
        };

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &separatorRect3);

        currentY += 2 + 5;
    }

    // Effect
    std::vector<Effect*> effectsVector = spell->getEffects();
    if (!effectsVector.empty()) {
        std::string text = "";
        for (const auto& s : effectsVector) {
            text += s->getDescription();
        }
        renderWithoutColor(currentY, LocalizationManager::instance().getText("item_effect"), text);
    }
}

int SpellMenu::getHeight() const {
    return -1;
}

SpellMenu::~SpellMenu() {}