#include "ItemMenu.h"

ItemMenu::ItemMenu(SDL_Renderer* renderer, TTF_Font* font) 
: Menu(renderer, font)
{
}

/**
 * Do not use, just here for consistency
 * Throw a runtime error
 */
void ItemMenu::render(const SDL_Rect& rect) {
    throw std::runtime_error("Error, need an item to render. Use render(const SDL_Rect& rect, Item* item) instead.");
}

void ItemMenu::render(const SDL_Rect& rect, Item* item) {
    // Define rects
    imgRect = {
        rect.x + 10,
        rect.y + 5,
        rect.w - 10 - 10,
        250
    };

    dataRect = {
        rect.x + 5,
        rect.y + 5 + 250 + 10,
        rect.w - 5 - 5,
        rect.h - 250 - 5 - 5
    };

    // Load the image from file
    SDL_Surface* imgSurface = IMG_Load("../res/images/aef.png");
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
    // Render item data
    //==================
    int currentY = dataRect.y;

    // Name
    std::string nameText = LocalizationManager::instance().getText("item_name") + item->getName();
    SDL_Texture* nameTextTexture = Utils::loadTextTexture(renderer, font, nameText, Utils::textColor);

    int textWidth = 0, textHeight = 0;
    if (nameTextTexture) {
        SDL_QueryTexture(nameTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect nameRect = {
            dataRect.x + 5, 
            currentY, 
            textWidth,
            textHeight
        };
        currentY += textHeight + 5;
        SDL_RenderCopy(renderer, nameTextTexture, nullptr, &nameRect);
    }
    SDL_DestroyTexture(nameTextTexture);

    // Type
    std::string typeText = LocalizationManager::instance().getText("item_type") + to_string(item->getType());
    SDL_Texture* typeTextTexture = Utils::loadTextTexture(renderer, font, typeText, Utils::textColor);
    if (typeTextTexture) {
        SDL_QueryTexture(typeTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect typeRect = {
            dataRect.x + 5, 
            currentY, 
            textWidth,
            textHeight
        };
        currentY += textHeight + 5;
        SDL_RenderCopy(renderer, typeTextTexture, nullptr, &typeRect);
    }
    SDL_DestroyTexture(typeTextTexture);

    // Weight
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << item->getWeight();
    std::string weightStr = stream.str();

    std::string weightText = LocalizationManager::instance().getText("item_weight") + weightStr;
    SDL_Texture* weightTextTexture = Utils::loadTextTexture(renderer, font, weightText, Utils::textColor);
    if (weightTextTexture) {
        SDL_QueryTexture(weightTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect weightRect = {
            dataRect.x + 5, 
            currentY, 
            textWidth,
            textHeight
        };
        currentY += textHeight + 5;
        SDL_RenderCopy(renderer, weightTextTexture, nullptr, &weightRect);
    }
    SDL_DestroyTexture(weightTextTexture);

    // Rarity
    std::string rarityLabel = LocalizationManager::instance().getText("item_rarity");
    SDL_Texture* rarityLabelTexture = Utils::loadTextTexture(renderer, font, rarityLabel, Utils::textColor);
    if (rarityLabelTexture) {
        int labelWidth = 0, labelHeight = 0;
        SDL_QueryTexture(rarityLabelTexture, nullptr, nullptr, &labelWidth, &labelHeight);
        SDL_Rect labelRect = {
            dataRect.x + 5, 
            currentY, 
            labelWidth,
            labelHeight
        };
        SDL_RenderCopy(renderer, rarityLabelTexture, nullptr, &labelRect);
        SDL_DestroyTexture(rarityLabelTexture);

        // Render rarity value
        std::string rarityValue = to_string(item->getRarity());
        SDL_Color valueColor = getRarityColor(item->getRarity());
        SDL_Texture* rarityValueTexture = Utils::loadTextTexture(renderer, font, rarityValue, valueColor);

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

        currentY += labelHeight + 5; // Update currentY for the next item to render
    }

    //===========
    // Separator
    //===========

    SDL_Rect separatorRect = {
        dataRect.x + 5,
        currentY,
        dataRect.w - 5 - 5,
        2
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &separatorRect);

    currentY += 2 + 5;

    //=============
    // Description
    //=============

    #pragma region Description

    std::string descriptionText = LocalizationManager::instance().getText("item_description") + item->getDescription();
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

    #pragma endregion

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

    std::array<int, 5> requirements = item->getRequirements();

    if (requirements.at(0) != -1) {
        renderWithoutColor(currentY, LocalizationManager::instance().getText("item_requirements"), "");

        // Strength
        if (requirements.at(0) > 0)
            renderWithoutColor(currentY, LocalizationManager::instance().getText("character_strength"), std::to_string(requirements.at(0)));

        // Dexterity
        if (requirements.at(1) > 0)
            renderWithoutColor(currentY, LocalizationManager::instance().getText("character_dexterity"), std::to_string(requirements.at(1)));

        // Intelligence
        if (requirements.at(2) > 0)
            renderWithoutColor(currentY, LocalizationManager::instance().getText("character_intelligence"), std::to_string(requirements.at(2)));

        // Wisdom
        if (requirements.at(3) > 0)
            renderWithoutColor(currentY, LocalizationManager::instance().getText("character_wisdom"), std::to_string(requirements.at(3)));

        // Constitution
        if (requirements.at(4) > 0)
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

    //=======================
    // Render item specifics
    //=======================

    switch (item->getType()) {
        case ItemType::Weapon:      renderWeapon(item, currentY); break;
        case ItemType::Shield:      renderShield(item, currentY); break;
        case ItemType::Helmet:      renderHelmet(item, currentY); break;
        case ItemType::Gloves:      renderGloves(item, currentY); break;
        case ItemType::ChestArmor:  renderChest(item, currentY); break;
        case ItemType::LegArmor:    renderLegging(item, currentY); break;
        case ItemType::Ring:        renderRing(item, currentY); break;
        case ItemType::Amulet:      renderAmulet(item, currentY); break;
        case ItemType::Consumable:  renderConsumable(item, currentY); break;
        case ItemType::Projectile:  renderProjectile(item, currentY); break;
        case ItemType::Container:   renderContainer(item, currentY); break;
        default:
            break;
    }
}

int ItemMenu::getHeight() const {
    return -1;
}

//===============
// Render Global
//===============

void ItemMenu::renderWithColor(int& currentY, SDL_Color color, std::string label, std::string value) {
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

void ItemMenu::renderWithoutColor(int& currentY, std::string label, std::string value) {
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

//==============
// Render Items
//==============

void ItemMenu::renderWeapon(Item* item, int& currentY) {
    Weapon* weapon = static_cast<Weapon*>(item);

    // Durability
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_durability"), (std::to_string(weapon->getDurability()) + "/" + std::to_string(weapon->getMaxDurability())));

    // Phy. Damage
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_phydamage"), std::to_string(weapon->getPhyDamage()));

    // Mag. Damage
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_magdamage"), std::to_string(weapon->getMagDamage()));

    // Damage Type
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_damagetype"), to_string(weapon->getDamageType()));

    // Two-handed
    weapon->isTwoHanded() ?
        renderWithColor(currentY, {0, 255, 0, 255}, LocalizationManager::instance().getText("item_twohanded"), LocalizationManager::instance().getText("yes"))
        :
        renderWithColor(currentY, {255, 0, 0, 255}, LocalizationManager::instance().getText("item_twohanded"), LocalizationManager::instance().getText("no"));
    
    // Length
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_range"), std::to_string(weapon->getLength()));

    // Magical
    weapon->isMagical() ?
        renderWithColor(currentY, {0, 255, 0, 255}, LocalizationManager::instance().getText("item_magical"), LocalizationManager::instance().getText("yes"))
        :
        renderWithColor(currentY, {255, 0, 0, 255}, LocalizationManager::instance().getText("item_magical"), LocalizationManager::instance().getText("no"));
    
}

void ItemMenu::renderShield(Item* item, int& currentY) {
    Shield* shield = static_cast<Shield*>(item);

    // Durability
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_durability"), (std::to_string(shield->getDurability()) + "/" + std::to_string(shield->getMaxDurability())));

    // Phy. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_phydefense"), std::to_string(shield->getPhyDefense()));

    // Mag. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_magdefense"), std::to_string(shield->getMagDefense()));

    // Parry Chance
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_parrychance"), (std::to_string(shield->getParryChance()) + "%"));
}

void ItemMenu::renderHelmet(Item* item, int& currentY) {
    Helmet* helmet = static_cast<Helmet*>(item);
    
    // Durability
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_durability"), (std::to_string(helmet->getDurability()) + "/" + std::to_string(helmet->getMaxDurability())));

    // Phy. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_phydefense"), std::to_string(helmet->getPhyDefense()));

    // Mag. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_magdefense"), std::to_string(helmet->getMagDefense()));

}

void ItemMenu::renderGloves(Item* item, int& currentY) {
    Gloves* glove = static_cast<Gloves*>(item);
    
    // Durability
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_durability"), (std::to_string(glove->getDurability()) + "/" + std::to_string(glove->getMaxDurability())));

    // Phy. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_phydefense"), std::to_string(glove->getPhyDefense()));

    // Mag. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_magdefense"), std::to_string(glove->getMagDefense()));

}

void ItemMenu::renderChest(Item* item, int& currentY) {
    Chests* chest = static_cast<Chests*>(item);
    
    // Durability
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_durability"), (std::to_string(chest->getDurability()) + "/" + std::to_string(chest->getMaxDurability())));

    // Phy. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_phydefense"), std::to_string(chest->getPhyDefense()));

    // Mag. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_magdefense"), std::to_string(chest->getMagDefense()));

}

void ItemMenu::renderLegging(Item* item, int& currentY) {
    Leggings* legging = static_cast<Leggings*>(item);
    
    // Durability
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_durability"), (std::to_string(legging->getDurability()) + "/" + std::to_string(legging->getMaxDurability())));

    // Phy. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_phydefense"), std::to_string(legging->getPhyDefense()));

    // Mag. Defense
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_magdefense"), std::to_string(legging->getMagDefense()));

}

void ItemMenu::renderRing(Item* item, int& currentY) {
    Ring* ring = static_cast<Ring*>(item);
    std::vector<Effect*> effectsVector = ring->getEffects();

    std::string text = ""; 
    for (const auto& s : effectsVector) {
        text += s->getDescription();
    }
    
    // Durability
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_durability"), (std::to_string(ring->getDurability()) + "/" + std::to_string(ring->getMaxDurability())));

    // Effect
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_effect"), text);
}

void ItemMenu::renderAmulet(Item* item, int& currentY) {
    Amulet* amulet = static_cast<Amulet*>(item);
    std::vector<Effect*> effectsVector = amulet->getEffects();

    std::string text = "";
    for (const auto& s : effectsVector) {
        text += s->getDescription();
    }
    
    // Durability
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_durability"), (std::to_string(amulet->getDurability()) + "/" + std::to_string(amulet->getMaxDurability())));

    // Effect
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_effect"), text);
}

void ItemMenu::renderConsumable(Item* item, int& currentY) {
    Consumable* consumable = static_cast<Consumable*>(item);
    std::vector<Effect*> effectsVector = consumable->getEffects();

    std::string text = "";
    for (const auto& s : effectsVector) {
        text += s->getDescription();
    }
    // Effect
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_effect"), text);
}

void ItemMenu::renderProjectile(Item* item, int& currentY) {
    Projectile* projectile = static_cast<Projectile*>(item);

    // Damage
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_phydamage"), std::to_string(projectile->getDamage()));

    // Damage Type
    renderWithoutColor(currentY, LocalizationManager::instance().getText("item_damagetype"), to_string(projectile->getDamageType()));

}

void ItemMenu::renderContainer(Item* item, int& currentY) {
    Containers* container = static_cast<Containers*>(item);

    std::list<Item*> items = container->getItems();
    std::unordered_map<std::string, int> itemsNumber;

    for (auto& i : items) {
        const auto& it = itemsNumber.find(i->getName());

        if (it == itemsNumber.end()) {
            // Item not in the map
            itemsNumber.emplace(i->getName(), 1);
        } else {
            // Item already in the map
            it->second++;
        }
    }

    for (auto& i : itemsNumber) {
        renderWithoutColor(currentY, i.first + ": ", std::to_string(i.second) + "x");
    }

}

ItemMenu::~ItemMenu() {}